#pragma once
#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H
#include "common/global.h"
#include "device/shader/Shader.h"
#include "device/model/material/Texture.h"
#include "device/model/mesh/Mesh.h"
#include "device/camera/Camera.h"




//区分不同类型的RenderContext只看shader，shader决定需要用到哪些数据
//有多少个MeshBuffer就有多少个RenderContext, 每个context中shader要绑定的指针都不同,故每个context都有一个shader对象
class RenderContext
{
public:

	static Camera camera; //camera是全局的

	//与mesh相关,一个mesh对应一个buffer
	MeshBuffer meshBuffer;

	Shader shader;

	vector<shared_ptr<Texture>> textures;

	shared_ptr<mat4> pModeling;

	float texMixRatio;


	virtual bool textureHasAlpha() const;

	virtual void clearButShader();

	string (*textureVarNamePolicy)(TextureType type, uint index);

	virtual shared_ptr<RenderContext> clone() const;

	virtual shared_ptr<RenderContext> prototype() const;

	virtual void bindShaderUniforms();
};


#endif // !RENDER_CONTEXT_H
