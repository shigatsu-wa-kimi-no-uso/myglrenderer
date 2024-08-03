#include "Model.h"

const vector<shared_ptr<Mesh>>& Model::getMeshes() const
{
    return meshes;
}

void Model::addMesh(const shared_ptr<Mesh>& mesh)
{
    meshes.push_back(mesh);
}
