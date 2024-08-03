#include "Renderer.h"



Renderer::Renderer() :pipeline(make_shared<CommonPipeline>()) {
	window.setInputBuffer(inputBuffer);
	cameraController.setCamera(RenderContext::camera);
	cameraController.setInputBuffer(inputBuffer);
	cameraController.setWindow(window);

}

void Renderer::createWindow(const WindowConfig& config) {
	window.setWindowConfig(config);
	if (!window.create()) {
		std::cout << "fail: " << glGetError() << "/n";
	}
	window.bindCallbacks();
	canvasMgr.enableDepthTesting();
	canvasMgr.enableCullFace(GL_BACK);
}

void Renderer::loadModel(uint contextId,const Model& model)
{
	MeshBuffer buf = meshMgr.generateMeshBuffer();
	meshMgr.bind(&buf);
	for (const shared_ptr<Mesh>& mesh : model.getMeshes()) {
		meshMgr.loadIn(mesh);
	}
	contexts[contextId]->meshBuffer = buf;
}

//将mesh结构体中的mesh和texture加载到GL
void Renderer::loadMesh(uint contextId, const shared_ptr<Mesh>& mesh)
{
	MeshBuffer buf = meshMgr.generateMeshBuffer();
	meshMgr.bind(&buf);
	meshMgr.loadIn(mesh);
	contexts[contextId]->meshBuffer = buf;
	uint unit = 0; //自动分配unit
	for (shared_ptr<Texture>& t : mesh->getTextures()) {
		loadTexture(contextId, t,unit);
		unit++;
	}
}

void Renderer::bindShaderUniforms(uint contextId) {
	contexts[contextId]->bindShaderUniforms();
}

void Renderer::loadShader(uint contextId, const char* szVertSrcCode, const char* szFragSrcCode)
{
	Shader shader;
	if (!shaderMgr.compile(szVertSrcCode, szFragSrcCode, shader)) {
		abort();
	}
	contexts[contextId]->shader = shader;
}

void Renderer::loadShader(uint contextId, const Shader& shader)
{
	contexts[contextId]->shader = shader;
}

void Renderer::loadShader(uint contextId, uint refContextId)
{
	contexts[contextId]->shader = contexts[refContextId]->shader;
}


Shader Renderer::loadShader(const char* szVertSrcCode, const char* szFragSrcCode)
{
	Shader shader;
	if (!shaderMgr.compile(szVertSrcCode, szFragSrcCode, shader)) {
		abort();
	}
	return shader;
}


/*
void Renderer::loadTexture(uint contextId, const Image& image)
{
	uint unit = contexts[contextId]->textures.size();
	GLenum dataFmt = image.componentCnt == 3 ? GL_RGB : GL_RGBA;
	Texture t = texMgr.create2DTexture(image, dataFmt, unit);
	texMgr.bind(&t);
	texMgr.applyTextureConfig(texture2DConfig);
	texMgr.detach();
	contexts[contextId]->textures.push_back(t);
}
*/

//加载贴图图像到GL，加载后，图像可以free
void Renderer::loadTexture(uint contextId,shared_ptr<Texture>& pTexture, uint unit)
{
	texMgr.create2DTexture(pTexture, unit);
	texMgr.bind(pTexture);
	texMgr.applyTextureConfig(texture2DConfig);
	texMgr.detach();
	contexts[contextId]->textures.push_back(pTexture);
}


shared_ptr<Texture> Renderer::loadTexture(const Image& image,uint unit)
{
	GLenum dataFmt = image.componentCnt == 3 ? GL_RGB : GL_RGBA;
	Texture t = texMgr.create2DTexture(image, dataFmt, unit);
	shared_ptr<Texture> pTex = make_shared<Texture>(t);
	texMgr.bind(pTex);
	texMgr.applyTextureConfig(texture2DConfig);
	texMgr.detach();
	return pTex;
}


void Renderer::bindContext(const shared_ptr<RenderContext>& pContext)
{
	meshMgr.bind(&pContext->meshBuffer);
	for (const shared_ptr<Texture> t : pContext->textures) {
		texMgr.bind(t);
	}
	shaderMgr.useShader(&pContext->shader);
	shaderMgr.loadUniforms();
}


void Renderer::render()
{
	pipeline->render(contexts, *this);
}
