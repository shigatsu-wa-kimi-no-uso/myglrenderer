#pragma once
#ifndef UTILITY_H
#define UTILITY_H
#include "defs.h"


bool initGLFW();

bool initGLAD();

bool openFileAndRead(const char* szFilePath, void* pBuf, size_t& length);

// 示例：使用 MultiByteToWideChar 和 WideCharToMultiByte 进行编码转换


void convertUTF8ToGB2312(const char* utf8Str, char* gb2312Str, size_t gb2312Size);



#endif // !UTILITY_H

