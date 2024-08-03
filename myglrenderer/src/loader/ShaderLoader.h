#pragma once
#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H
#include "common/global.h"

class ShaderLoader
{
public:
	
	static char* loadCode(const char* szFilePath);

	static void freeCode(char* pCodeBuf);
};

#endif // !SHADER_LOADER_H
