#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include "common/global.h"
#include "common/image.h"
#include "assimp/material.h"

using TextureType = aiTextureType;

const char* textureTypeString(aiTextureType textureType);

class Texture
{
public:
	uint textureId;
	uint unit;
	GLenum textureTarget;
	TextureType textureType;
	Image image;
	char name[64];
	string filePath;
	uint status = 0;
	bool hasAlpha();
	Texture();
	~Texture();
};



#endif // !TEXTURE_H

