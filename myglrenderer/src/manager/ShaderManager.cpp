#include "common/utility.h"
#include "ShaderManager.h"
#include "device/shader/Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

ShaderManager::ShaderManager()
{
}

bool ShaderManager::compile(const char* szVertSrcCode, const char* szFragSrcCode, Shader& shader)
{
    uint vertShaderId = glCreateShader(GL_VERTEX_SHADER);
    uint fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    bool status = false;
    glShaderSource(vertShaderId, 1, &szVertSrcCode, NULL);
    glShaderSource(fragShaderId, 1, &szFragSrcCode, NULL);
    glCompileShader(vertShaderId);
    glCompileShader(fragShaderId);
    if (checkShaderCompileErrors(vertShaderId) && checkShaderCompileErrors(fragShaderId)) {
        uint programId = glCreateProgram();
        glAttachShader(programId, vertShaderId);
        glAttachShader(programId, fragShaderId);
        glLinkProgram(programId);
        if (checkShaderLinkErrors(programId)) {
            shader.programId = programId;
            status = true;
        }
    }
    glDeleteShader(vertShaderId);
    glDeleteShader(fragShaderId);
    return status;
}


bool ShaderManager::compile(const char* szVertSrcCode, const char* szFragSrcCode, shared_ptr<Shader>& pShader)
{
    pShader = make_shared<Shader>();
    return compile(szVertSrcCode, szFragSrcCode, *pShader);
}


void ShaderManager::useShader(const Shader* pShader)
{
    _pCurrShader = pShader;
    glUseProgram(_pCurrShader->programId);
}

void ShaderManager::detachShader()const
{
    glUseProgram(0);
}

//在set变量值前，先use
void ShaderManager::loadUniforms()
{
	hashmap<string,UniformMeta> metas;
	//vector<void*> valuePtrs;
	_pCurrShader->getUniformMetas(metas);
	//_pCurrShader->getUniformValuePtrs(valuePtrs);
	for (const pair<string,UniformMeta>& elem : metas) {
        const UniformMeta& meta = elem.second;
		GLSLType type = meta.type;
		const char* szName = meta.name.c_str();
		const void* ptr = meta.pValue;
		switch (type)
		{
		case GLSLType::INT:
			setUniform(szName, *(int*)ptr);
			break;
		case GLSLType::FLOAT:
			setUniform(szName, *(float*)ptr);
			break;
		case GLSLType::VEC2:
			setUniform(szName, *(vec2*)ptr);
			break;
		case GLSLType::IVEC2:
			setUniform(szName, *(ivec2*)ptr);
			break;
		case GLSLType::VEC3:
			setUniform(szName, *(vec3*)ptr);
			break;
		case GLSLType::IVEC3:
			setUniform(szName, *(ivec3*)ptr);
			break;
		case GLSLType::VEC4:
			setUniform(szName, *(vec4*)ptr);
			break;
		case GLSLType::IVEC4:
			setUniform(szName, *(ivec4*)ptr);
			break;
		case GLSLType::MAT3:
			setUniform(szName, *(mat3*)ptr);
			break;
		case GLSLType::MAT4:
			setUniform(szName, *(mat4*)ptr);
			break;
		default:
			break;
		}
	}
}

void ShaderManager::setUniform(const char* name, float value)const
{
    glUniform1f(glGetUniformLocation(_pCurrShader->programId, name), value);
}

void ShaderManager::setUniform(const char* name, int value)const
{
    glUniform1i(glGetUniformLocation(_pCurrShader->programId, name), value);
}

void ShaderManager::setUniform(const char* name, const vec2& vector)const
{
    glUniform2f(glGetUniformLocation(_pCurrShader->programId, name), vector.x, vector.y);
}

void ShaderManager::setUniform(const char* name, const ivec2& vector)const
{
    glUniform2i(glGetUniformLocation(_pCurrShader->programId, name), vector.x, vector.y);
}

void ShaderManager::setUniform(const char* name, const vec3& vector)const
{
    glUniform3f(glGetUniformLocation(_pCurrShader->programId, name), vector.x, vector.y, vector.z);
}

void ShaderManager::setUniform(const char* name, const ivec3& vector)const
{
    glUniform3i(glGetUniformLocation(_pCurrShader->programId, name), vector.x, vector.y, vector.z);
}

void ShaderManager::setUniform(const char* name, const vec4& vector)const
{
    glUniform4f(glGetUniformLocation(_pCurrShader->programId, name), vector.x, vector.y, vector.z, vector.w);
}

void ShaderManager::setUniform(const char* name, const ivec4& vector)const
{
    glUniform4i(glGetUniformLocation(_pCurrShader->programId, name), vector.x, vector.y, vector.z, vector.w);
}

void ShaderManager::setUniform(const char* name, const mat3& matrix)const
{
    glUniformMatrix3fv(glGetUniformLocation(_pCurrShader->programId, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderManager::setUniform(const char* name, const mat4& matrix)const
{
    glUniformMatrix4fv(glGetUniformLocation(_pCurrShader->programId, name), 1, GL_FALSE, glm::value_ptr(matrix));
}


bool ShaderManager::_createShader(const char* szFilePath, GLenum type, uint& shaderId)
{
    size_t len;
    if (openFileAndRead(szFilePath, nullptr, len)) {
        char* codeBuf[1];
        codeBuf[0] = new char[len + 1];
        if (openFileAndRead(szFilePath, codeBuf[0], len)) {
            codeBuf[0][len] = '\0';
            shaderId = glCreateShader(type);
            glShaderSource(shaderId, 1, codeBuf, NULL);
            delete codeBuf[0];
            return true;
        }
    }
    return false;
}


bool ShaderManager::checkShaderCompileErrors(uint shaderId)
{
    int success;
    char infoLog[1024];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderId, 1024, NULL, infoLog);
        printf("ERROR::SHADER_COMPILATION_ERROR of id %u\n%s", shaderId, infoLog);
        printf("\n-- -------------------------------------------------- - --\n");
        return false;
    }
    return true;
}


bool ShaderManager::checkShaderLinkErrors(uint shaderId)
{
    int success;
    char infoLog[1024];
    glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderId, 1024, NULL, infoLog);
        printf("ERROR::PROGRAM_LINKING_ERROR of id %u\n%s", shaderId, infoLog);
        printf("\n-- -------------------------------------------------- - --\n");
        return false;
    }
    return true;
}