#include "Shader.h"


Shader::Shader():programId(0) {

}

void Shader::clearUniformBinds()
{
	uniformMetas.clear();
}

void Shader::deleteUniform(const string& name) {
	uniformMetas.erase(name); //键不存在时,不会报错
}

void Shader::setUniform(const string& name, GLSLType type, const void* pValue)
{
	uniformMetas[name] = { name,type,pValue };
}

void Shader::getUniformMetas(hashmap<string, UniformMeta>& metas) const
{
	metas = uniformMetas;
}
