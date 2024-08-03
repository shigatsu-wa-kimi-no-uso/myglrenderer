#include "utility.h"
#include "global.h"
#include <stdio.h>
#include <windows.h>

bool initGLFW() {
    return glfwInit() == GLFW_TRUE;
}

bool initGLAD() {
    return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) != 0;
}

bool openFileAndRead(const char* szFilePath, void* pBuf, size_t &length) {
    FILE* hFile = fopen(szFilePath, "rb");
    if (hFile == nullptr) {
        return false;
    }
    if (pBuf == nullptr) {
        fseek(hFile, 0, SEEK_END);
        length = ftell(hFile);
        fclose(hFile);
        return true;
    }else{
        size_t successCnt = fread(pBuf, 1, length, hFile);
        fclose(hFile);
        if (successCnt == length) {
            return true;
        } else {
            length = successCnt;
            return false;
        }
    }
}
#include <specstrings.h>

void convertUTF8ToGB2312(const char* utf8Str, char* gb2312Str, size_t gb2312Size) {
    // Convert UTF-8 to wide char
    int wstrLen = MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, NULL, 0);
    wchar_t* wstr = (wchar_t*)malloc(wstrLen * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, wstr, wstrLen);

    // Convert wide char to GB2312
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, gb2312Str, gb2312Size, NULL, NULL);

    free(wstr);
}

