#pragma once
#ifndef SHADER_H
#define SHADER_H
#include "common/global.h"


struct UniformMeta
{
	string name;
	GLSLType type;
	const void* pValue;
};

class Shader
{
private:
	
	hashmap<string,UniformMeta> uniformMetas;
//	vector<void*> uniformValuePtrs;

public:
	uint programId;

	Shader();

	void clearUniformBinds();

	void deleteUniform(const string& name);

	void setUniform(const string& name, GLSLType type, const void* pValue);

	void getUniformMetas(hashmap<string, UniformMeta>& metas) const;

};

#endif // !SHADER_H

