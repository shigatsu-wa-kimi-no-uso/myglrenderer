#include "ModelLoader.h"
#include "common/utility.h"

ModelLoader::ModelLoader()
{
}

// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.

void ModelLoader::loadModel(const char* szModelPath, Model& model,shared_ptr<Mesh> meshObjPrototype)
{
    // read file via ASSIMP
    Assimp::Importer importer;
    scene = importer.ReadFile(szModelPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    // if is Not Zero
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }
    currentDirectory = szModelPath;
    size_t lastSlashOffset = currentDirectory.find_last_of('/');
    if (lastSlashOffset == string::npos) {
        lastSlashOffset = currentDirectory.find_last_of('\\');
    }
    currentDirectory = currentDirectory.substr(0, lastSlashOffset);

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, model, meshObjPrototype);
}

// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).

void ModelLoader::processNode(aiNode* node, Model& model, shared_ptr<Mesh> meshObjPrototype)
{
    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        model.addMesh(processMesh(mesh,meshObjPrototype));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], model, meshObjPrototype);
    }

}

shared_ptr<Mesh> ModelLoader::processMesh(aiMesh* mesh, shared_ptr<Mesh> meshObjPrototype)
{
    // data to fill
    shared_ptr<Mesh> meshObj = meshObjPrototype->prototype();
    if (mesh->mName.length > 0) {
        convertUTF8ToGB2312(mesh->mName.C_Str(), meshObj->name, sizeof(meshObj->name));
    } else {
        strcpy(meshObj->name, "noname");
    }
    printf("Loading mesh:%s\n", meshObj->name);
    vector<Vertex> vertices;
    vector<uint> indices;
    vector<Texture> textures;
    // walk through each of the mesh's vertices
    for (uint i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        // positions
        vertex.position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        // normals
        if (mesh->HasNormals()) {
            vertex.normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        }
        // texture coordinates
        // does the mesh contain texture coordinates?
        if (mesh->mTextureCoords[0]) {
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vertex.texCoords = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            // tangent
            vertex.tangent = vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
            // bitangent
            vertex.bitangent = vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
        } else {
            vertex.texCoords = vec2(0.0f, 0.0f);
        }
        meshObj->addVertexAttribute(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (uint i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (uint j = 0; j < face.mNumIndices; j++) {
            meshObj->addTriangleIndex(face.mIndices[j]);
        }
    }


    
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    //
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    loadMaterialTextures(meshObj,material, aiTextureType_DIFFUSE);
    // 2. specular maps
    loadMaterialTextures(meshObj, material, aiTextureType_SPECULAR);

    // 3. normal maps
    loadMaterialTextures(meshObj, material, aiTextureType_HEIGHT);
    // 4. height maps
    loadMaterialTextures(meshObj, material, aiTextureType_AMBIENT);

    // return a mesh object created from the extracted mesh data
    return meshObj;
}


void ModelLoader::loadMaterialTextures(shared_ptr<Mesh> meshObj,aiMaterial* material, aiTextureType type)
{
    uint cnt = material->GetTextureCount(type);
    if (cnt <= 0) {
        printf("No textures found for mesh %s type %d\n", meshObj->name,type);
    }
    for (unsigned int i = 0; i < cnt; i++)
    {
        aiString fileName;
        string filePath;
        char szFileName[128], szMaterialName[128];
        material->GetTexture(type, i, &fileName);
        convertUTF8ToGB2312(fileName.C_Str(), szFileName, sizeof(szFileName));
        convertUTF8ToGB2312(material->GetName().C_Str(), szMaterialName, sizeof(szMaterialName));
        
    
        
        if (fileName.length > 0) {
            filePath = currentDirectory + "/" + szFileName; //系统自动处理 '\' '/' 不统一问题
        } else {
            printf("Cannot resolve material texture bind info for type %d.\n",  type);
        }

        bool skip = false;
        shared_ptr<Texture> pTex;
        hashmap<string, shared_ptr<Texture>>::iterator it;
        if ((it = textureCache.find(filePath)) != textureCache.end()) {
            skip = true;
        }
        if (skip) {
            pTex = it->second;
            printf("Loaded texture %s for mesh %s type %d. From cache.\n", szMaterialName, meshObj->name, type);
        } else {
            pTex = make_shared<Texture>();
            strcpy(pTex->name, szMaterialName);
            loadImageFromFile(filePath.c_str(), pTex->image);
            if (pTex->image.pData != nullptr) {
                pTex->textureType = type;
                pTex->filePath = filePath;
                textureCache[filePath] = pTex;
                printf("Loaded texture %s for mesh %s type %d. From file %s.\n", szMaterialName, meshObj->name, type, szFileName);
            } else {
                printf("Load texture %s for mesh %s type %d failed.\n", szMaterialName, meshObj->name, type);
            }
           
        }
        meshObj->addTexture(pTex);
    }
}

void ModelLoader::loadImageFromFile(const char* path, Image& image)
{
    image.pData = stbi_load(path, &image.width, &image.height, &image.componentCnt, 0);
}

void ModelLoader::freeTextureImage(const shared_ptr<Texture>& pTexture)
{
    if (pTexture->image.pData != nullptr) {
        stbi_image_free(pTexture->image.pData);
        pTexture->image.pData = nullptr;
        textureCache.erase(pTexture->filePath);
    }
}
