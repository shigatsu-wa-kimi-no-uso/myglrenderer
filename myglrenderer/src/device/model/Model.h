#pragma once
#ifndef MODEL_H
#define MODEL_H
#include "common/global.h"
#include "material/Texture.h"
#include "mesh/Mesh.h"


class Model
{
private:
    vector<shared_ptr<Mesh>> meshes;
    bool gammaCorrection;

public:

    const vector<shared_ptr<Mesh>>& getMeshes() const;

    void addMesh(const shared_ptr<Mesh>& mesh);
};

#endif // !MODEL_H

