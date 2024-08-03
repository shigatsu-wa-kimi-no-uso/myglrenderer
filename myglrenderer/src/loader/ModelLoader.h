#pragma once
#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include "common/global.h"
#include "common/image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "device/model/mesh/mesh.h"
#include "device/model/mesh/CommonMeshEx.h"
#include "device/model/Model.h"

#include <iostream>
#include <map>
#include <vector>
using namespace std;

class ModelLoader
{
private:
    // model data 
    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.

    // constructor, expects a filepath to a 3D model.
    string currentDirectory;

    const aiScene* scene;

    hashmap<string, shared_ptr<Texture>> textureCache; //已被加载,则能找到,若图像已经释放,则找不到
    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode* node, Model& model, shared_ptr<Mesh> meshObjPrototype);

    shared_ptr<Mesh> processMesh(aiMesh* mesh, shared_ptr<Mesh> meshObjPrototype);

    void loadMaterialTextures(shared_ptr<Mesh> meshObj, aiMaterial* material, aiTextureType type);




public:
    ModelLoader();

    void loadImageFromFile(const char* path, Image& image);

    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(const char* szModelPath, Model& model, shared_ptr<Mesh> meshObjPrototype);

    void freeTextureImage(const shared_ptr<Texture>& pTexture);


};
#endif // !MODEL_LOADER_H

