#include "MeshManager.h"

MeshManager::MeshManager()
{
}


MeshManager::~MeshManager()
{

}

MeshBuffer MeshManager::generateMeshBuffer()
{
    MeshBuffer buffer;
    glGenVertexArrays(1, &buffer.vao);
    glGenBuffers(1, &buffer.vbo);
    glGenBuffers(1, &buffer.ebo);
    return buffer;
}

void MeshManager::freeMeshBuffer(MeshBuffer& buffer)
{
    glDeleteVertexArrays(1, &buffer.vao);
    glDeleteBuffers(1, &buffer.vbo);
    glDeleteBuffers(1, &buffer.ebo);
}

void MeshManager::bind(MeshBuffer* pBuffer)
{
    _pCurrMeshBuffer = pBuffer;
    glBindVertexArray(pBuffer->vao);
}

void MeshManager::detach()
{
    glBindVertexArray(0);
}

// initializes all the buffer objects/arrays

void MeshManager::loadIn(shared_ptr<Mesh> pMesh)
{
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, _pCurrMeshBuffer->vbo);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    VertexAttributeBuffer attribBuf;
    vector<VertexAttributeMeta> attribMetas;
    vector<uint> indices;

    pMesh->getVertexAttributeBuffer(attribBuf);
    pMesh->getVertexAttributeMetas(attribMetas);
    pMesh->getTriangleIndices(indices);
    glBufferData(GL_ARRAY_BUFFER, attribBuf.elemCnt * attribBuf.elemSize, attribBuf.pVertexAttributeBuffer, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _pCurrMeshBuffer->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    size_t attribCnt = attribMetas.size();
    for (int i = 0; i < attribCnt; i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, attribMetas[i].elemCnt, attribMetas[i].elemType, attribMetas[i].normalized, attribBuf.elemSize, (void*)attribMetas[i].offset);
    }
    _pCurrMeshBuffer->vertexCnt = attribBuf.elemCnt;
}
