#include "Mesh.h"

Mesh::Mesh() 
{

}

void Mesh::getTriangleIndices(vector<uint>& indices) const
{
    indices = triangleIndices;
}

void Mesh::addTexture(const shared_ptr<Texture>& texture) {

}

vector<shared_ptr<Texture>> Mesh::getTextures() const {
    return {};
}




