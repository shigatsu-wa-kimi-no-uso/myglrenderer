#pragma once
#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H
#include "common/global.h"
#include "device/shader/Shader.h"
#include "device/model/material/Texture.h"
#include "device/model/mesh/Mesh.h"
#include "device/camera/Camera.h"




//���ֲ�ͬ���͵�RenderContextֻ��shader��shader������Ҫ�õ���Щ����
//�ж��ٸ�MeshBuffer���ж��ٸ�RenderContext, ÿ��context��shaderҪ�󶨵�ָ�붼��ͬ,��ÿ��context����һ��shader����
class RenderContext
{
public:

	static Camera camera; //camera��ȫ�ֵ�

	//��mesh���,һ��mesh��Ӧһ��buffer
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
