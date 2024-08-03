#include "ShaderLoader.h"

char* ShaderLoader::loadCode(const char* szFilePath)
{
    FILE* hFile = fopen(szFilePath, "rb");
    if (hFile == nullptr) {
        return nullptr;
    }
    fseek(hFile, 0, SEEK_END);
    long length = ftell(hFile);
    fseek(hFile, 0, SEEK_SET);
    char* pBuf = new char[length + 1];
    size_t successCnt = fread(pBuf, 1, length, hFile);
    fclose(hFile);
    if (successCnt == length) {
        pBuf[length] = '\0';
        return pBuf;
    } else {
        return nullptr;
    }
}

void ShaderLoader::freeCode(char* pCodeBuf)
{
    delete pCodeBuf;
}
