#include "CommonMeshEx.h"


CommonMeshEx::CommonMeshEx()
{
}

void CommonMeshEx::addVertexAttribute(const ::Vertex& vertex)
{
    Vertex commonVert = { vertex.position,vertex.normal,vertex.texCoords };
    vertices.push_back(commonVert);
}

void CommonMeshEx::addTexture(const shared_ptr<Texture>& texture) 
{
    textures.push_back(texture);
}

void CommonMeshEx::addTriangleIndex(uint index)
{
    triangleIndices.push_back(index);
}

vector<shared_ptr<Texture>> CommonMeshEx::getTextures() const 
{
    return textures;
}

void CommonMeshEx::getVertexAttributeBuffer(VertexAttributeBuffer& buf) const
{
    buf.elemCnt = vertices.size();
    buf.elemSize = sizeof(Vertex);
    buf.pVertexAttributeBuffer = &vertices[0];
}

void CommonMeshEx::getVertexAttributeMetas(vector<VertexAttributeMeta>& metas) const
{
    metas.push_back({
        "aPosition",
        3,
        GL_FLOAT,
        false,
        offsetof(Vertex,position)
        });
    metas.push_back({
        "aNormal",
        3,
        GL_FLOAT,
        false,
        offsetof(Vertex,normal)
        });
    metas.push_back({
        "aTexCoords",
        2,
        GL_FLOAT,
        false,
        offsetof(Vertex,texCoords)
        });
}

shared_ptr<Mesh> CommonMeshEx::prototype() const {
    return make_shared<CommonMeshEx>();
}

