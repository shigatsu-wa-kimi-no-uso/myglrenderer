#pragma once
#ifndef RENDERER_H
#define RENDERER_H
#include "common/global.h"
#include "RenderContext.h"
#include "device/model/Model.h"
#include "window/Window.h"
#include "device/shader/Shader.h"
#include "loader/ShaderLoader.h"
#include "device/model/mesh/CommonMesh.h"
#include "device/model/mesh/Mesh.h"
#include "manager/ShaderManager.h"
#include "manager/MeshManager.h"
#include "manager/TextureManager.h"
#include "loader/ModelLoader.h"
#include "manager/CanvasManager.h"
#include "pipeline/RenderPipeline.h"
#include "pipeline/CommonPipeline.h"
#include "controller/CameraController.h"

class Renderer
{
	hashmap<uint,shared_ptr<RenderContext>> contexts;
	shared_ptr<RenderPipeline> pipeline;
	
	Texture2DConfig texture2DConfig;


	ShaderManager shaderMgr;
    TextureManager texMgr;
    ModelLoader modelLoader;
    MeshManager meshMgr;
	uint counter = 0;

	
	InputBuffer inputBuffer;
public:
	CanvasManager canvasMgr;
	Window window;
	CameraController cameraController;
	Renderer();

	void createWindow(const WindowConfig& config);

	template<class ContextT>
	uint createContext()
	{
		static_assert(std::is_base_of<RenderContext, ContextT>::value, "上下文类必须为RenderContext及其子类");
		contexts[counter] = make_shared<ContextT>();
		return counter++;
	}

	template<class ContextT>
	uint createContext(const ContextT& context)
	{
		static_assert(std::is_base_of<RenderContext, ContextT>::value, "上下文类必须为RenderContext及其子类");
		contexts[counter] = context.clone();
		return counter++;
	}

	template<class ContextT>
	shared_ptr<ContextT> getContext(uint contextId)
	{
		return contexts[contextId];
	}

	void loadMesh(uint contextId, const shared_ptr<Mesh>& mesh);

	void bindShaderUniforms(uint contextId);

	void loadModel(const Model& model);

	void loadModel(uint contextId, const Model& model);

	void loadShader(uint contextId,const char* szVertSrcCode,const char* szFragSrcCode);

	void loadShader(uint contextId, const Shader& shader);

	void loadShader(uint contextId, uint refContextId);

	Shader loadShader(const char* szVertSrcCode, const char* szFragSrcCode);

	void loadTexture(uint contextId, shared_ptr<Texture>& pTexture, uint unit);

	void loadTexture(uint contextId,const Image& image);

	shared_ptr<Texture> loadTexture(const Image& image,uint unit = 0);


	void render();

	void bindContext(const shared_ptr<RenderContext>& pContext);


};

#endif // !RENDERER_H

