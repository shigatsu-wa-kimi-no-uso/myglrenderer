#pragma once
#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include "common/global.h"
#include "device/shader/Shader.h"

class ShaderManager
{
public:

    ShaderManager();

    bool compile(const char* szVertSrcCode, const char* szFragSrcCode, Shader& shader);
	bool compile(const char* szVertSrcCode, const char* szFragSrcCode, shared_ptr<Shader>& pShader);

	[[deprecated]]
    void useShader(const Shader* pShader);

	void useShader(const shared_ptr<Shader>& pShader);
	void detachShader() const;

	//在set变量值前，先use
	void loadUniforms();
	void setUniform(const char* name, float value) const;
	void setUniform(const char* name, int value) const;
	void setUniform(const char* name, const glm::vec2& vector) const;
	void setUniform(const char* name, const glm::ivec2& vector) const;
	void setUniform(const char* name, const glm::vec3& vector) const;
	void setUniform(const char* name, const glm::ivec3& vector) const;
	void setUniform(const char* name, const glm::vec4& vector) const;
	void setUniform(const char* name, const glm::ivec4& vector) const;
	void setUniform(const char* name, const glm::mat3& matrix) const;
	void setUniform(const char* name, const glm::mat4& matrix) const;


private:
    const Shader* _pCurrShader;
    bool _createShader(const char* szFilePath, GLenum type, uint& shaderId);
	bool checkShaderCompileErrors(uint shaderId);
	bool checkShaderLinkErrors(uint shaderId);

};



#endif