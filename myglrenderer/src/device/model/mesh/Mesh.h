#pragma once
#ifndef MESH_H
#define MESH_H
#include "common/global.h"
#include  "../material/Texture.h"

struct VertexAttributeMeta
{
    const char* szAttributeName;
    size_t elemCnt;
    GLenum elemType;
    GLboolean normalized;
    size_t offset;
};

struct VertexAttributeBuffer
{
    const void* pVertexAttributeBuffer;
    size_t elemSize;
    size_t elemCnt;
};

struct MeshBuffer
{
    uint vao, vbo, ebo;
    uint vertexCnt;
};

struct Vertex {
    vec3 position;
    vec3 normal;
    vec2 texCoords;
    vec3 tangent;
    vec3 bitangent;
};

class Mesh
{
public:
    Mesh();

    virtual void getVertexAttributeBuffer(VertexAttributeBuffer& buf) const = 0;

    virtual void getVertexAttributeMetas(vector<VertexAttributeMeta>& metas) const = 0;

    virtual void getTriangleIndices(vector<uint>& indices) const ;

    virtual void addTriangleIndex(uint index) = 0;

    virtual void addTexture(const shared_ptr<Texture>& texture);

    virtual vector<shared_ptr<Texture>> getTextures() const;

    virtual void addVertexAttribute(const Vertex& vertex) = 0;

    virtual shared_ptr<Mesh> prototype() const = 0;


    char name[64];

protected:
    vector<uint> triangleIndices;
};
#endif