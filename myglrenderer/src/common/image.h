#pragma once
#ifndef IMAGE_H
#define IMAGE_H
#include "stb_image.h"


struct Image
{
	int width;
	int height;
	int componentCnt;
	void* pData;
};

#endif
