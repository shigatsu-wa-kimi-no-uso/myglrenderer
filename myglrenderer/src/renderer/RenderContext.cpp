#include "RenderContext.h"
#include "RenderContext.h"
#include "RenderContext.h"

Camera RenderContext::camera;

bool RenderContext::textureHasAlpha() const {
	bool hasAlpha = false;
	for (const shared_ptr<Texture>& t : textures) {
		hasAlpha |= t->hasAlpha();
	}
	return hasAlpha;
}

void RenderContext::clearButShader()
{
	textures.clear();
	pModeling = make_shared<mat4>();
	meshBuffer = MeshBuffer();
}

shared_ptr<RenderContext> RenderContext::clone() const
{
	shared_ptr<RenderContext> rc = make_shared<RenderContext>(*this);
	rc->bindShaderUniforms();
	return rc;
}

shared_ptr<RenderContext> RenderContext::prototype() const {
	return make_shared<RenderContext>();
}


void RenderContext::bindShaderUniforms()
{
	shader.clearUniformBinds();
	uint index = 0;
	for (shared_ptr<Texture> t : textures) {
		string varName = textureVarNamePolicy(t->textureType, index);
		shader.setUniform(varName.c_str(), GLSLType::INT, &t->unit);
		index++;
	}

	shader.setUniform("uRatio", GLSLType::FLOAT, &texMixRatio);
	shader.setUniform("uModeling", GLSLType::MAT4, glm::value_ptr(*pModeling));
	shader.setUniform("uView", GLSLType::MAT4, camera.getViewPtr());
	shader.setUniform("uProjection", GLSLType::MAT4, camera.getProjectionPtr());
}



