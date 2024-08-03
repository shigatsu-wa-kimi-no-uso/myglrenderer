#pragma once
#ifndef COMMON_MESH_EX_H
#define COMMON_MESH_EX_H
#include "Mesh.h"
#include "../material/Texture.h"

class CommonMeshEx : public Mesh
{
public:
    struct Vertex {
        vec3 position;
        vec3 normal;
        vec2 texCoords;
    };
private:

    vector<Vertex> vertices;
    vector<shared_ptr<Texture>> textures;

public:
    CommonMeshEx();

    void addVertexAttribute(const ::Vertex& vertex) override;

    void addTexture(const shared_ptr<Texture>& texture) override;

    void addTriangleIndex(uint index) override;

    vector<shared_ptr<Texture>> getTextures() const override;

    void getVertexAttributeBuffer(VertexAttributeBuffer& buf) const override;

    void getVertexAttributeMetas(vector<VertexAttributeMeta>& metas) const override;

    shared_ptr<Mesh> prototype() const override;
};

#endif // !COMMON_MESH_EX_H

