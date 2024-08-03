#pragma once
#ifndef MESH_LOADER_H
#define MESH_LOADER_H
#include "common/global.h"
#include "device/model/mesh/Mesh.h"


class MeshManager {
    // constructor

    /*
    // render the mesh
    void Draw(Shader& shader)
    {
        // bind appropriate textures
        uint diffuseNr = 1;
        uint specularNr = 1;
        uint normalNr = 1;
        uint heightNr = 1;
        for (uint i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); // transfer uint to string
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); // transfer uint to string
            else if (name == "texture_height")
                number = std::to_string(heightNr++); // transfer uint to string

            // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

        // draw mesh
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, static_cast<uint>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }
    */
private:
    // render data 
    MeshBuffer* _pCurrMeshBuffer;
public:

    MeshManager();

    ~MeshManager();

    MeshBuffer generateMeshBuffer();

    void freeMeshBuffer(MeshBuffer& buffer);


    void bind(MeshBuffer* buffer);

    void detach();

    // initializes all the buffer objects/arrays
    void loadIn(shared_ptr<Mesh> pMesh);

};

#endif // !MESH_LOADER_H
