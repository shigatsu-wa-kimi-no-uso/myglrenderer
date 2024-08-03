#pragma once
#ifndef COMMON_MESH_H
#define COMMON_MESH_h
#include "common/global.h"
#include "Mesh.h"

class CommonMesh : public Mesh
{
public:
    struct Vertex {
        vec3 position;
        vec3 normal;
        vec2 texCoords;
    };

private:

    vector<Vertex> vertices;

public:
    CommonMesh();

    void addVertexAttribute(const ::Vertex& vertex) override;

    void addTriangleIndex(uint index);

    void getVertexAttributeBuffer(VertexAttributeBuffer& buf) const override;

    void getVertexAttributeMetas(vector<VertexAttributeMeta>& metas) const override;
  
    shared_ptr<Mesh> prototype() const override;
};

#endif // !COMMON_MESH_H