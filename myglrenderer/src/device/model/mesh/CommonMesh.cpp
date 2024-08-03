#include "CommonMesh.h"

CommonMesh::CommonMesh()
{

}

void CommonMesh::addVertexAttribute(const ::Vertex& vertex)
{
    Vertex commonVert = { vertex.position,vertex.normal,vertex.texCoords };
    vertices.push_back(commonVert);
}

void CommonMesh::addTriangleIndex(uint index)
{
    triangleIndices.push_back(index);
}

void CommonMesh::getVertexAttributeBuffer(VertexAttributeBuffer& buf) const
{
    buf.elemCnt = vertices.size();
    buf.elemSize = sizeof(Vertex);
    buf.pVertexAttributeBuffer = &vertices[0];
}

void CommonMesh::getVertexAttributeMetas(vector<VertexAttributeMeta>& metas) const
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

shared_ptr<Mesh> CommonMesh::prototype() const {
    return make_shared<CommonMesh>();
}
