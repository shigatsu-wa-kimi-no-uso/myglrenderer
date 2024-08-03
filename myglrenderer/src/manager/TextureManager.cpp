#include "TextureManager.h"
#include "common/image.h"
#include <glm/gtc/type_ptr.hpp>

TextureManager::TextureManager()
{
}


void TextureManager::create2DTexture(shared_ptr<Texture>& pTexture, uint unit, GLenum textureFmt, GLenum pixelDataType)
{
	create2DTexture(*pTexture, unit, textureFmt, pixelDataType);
}


void TextureManager::create2DTexture(Texture& texture, uint unit, GLenum textureFmt, GLenum pixelDataType)
{
	//textureFmt和dataFmt不一致时(通道数相同), 会发生转换(sRGB -> RGB / RGB -> sRGB)
	if (texture.status == 1) {
		return;
	}
	texture.textureTarget = GL_TEXTURE_2D;
	texture.unit = unit;
	//textureFmt==GL_NONE时，将默认采用dataFmt的格式
	GLenum dataFmt = texture.image.componentCnt == 3 ? GL_RGB : GL_RGBA;
	if (textureFmt == GL_NONE) {
		textureFmt = dataFmt;
	}

	// generate texture and setup basics
	glGenTextures(1, &texture.textureId);
	glBindTexture(texture.textureTarget, texture.textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, textureFmt, texture.image.width, texture.image.height, 0, dataFmt, pixelDataType, texture.image.pData);
	glBindTexture(texture.textureTarget, 0);
	texture.status = 1;
}


Texture TextureManager::create2DTexture(const Image& image, GLenum dataFmt,uint unit, GLenum textureFmt, GLenum pixelDataType)
{
	//textureFmt和dataFmt不一致时(通道数相同), 会发生转换(sRGB -> RGB / RGB -> sRGB)
	Texture texture;
	texture.textureTarget = GL_TEXTURE_2D;
	texture.unit = unit;
	//textureFmt==GL_NONE时，将默认采用dataFmt的格式

	if (textureFmt == GL_NONE) {
		textureFmt = dataFmt;
	}

	// generate texture and setup basics
	glGenTextures(1, &texture.textureId);
	glBindTexture(texture.textureTarget, texture.textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, textureFmt, image.width, image.height, 0, dataFmt, pixelDataType, image.pData);
	glBindTexture(texture.textureTarget, 0);
	return texture;
}

void TextureManager::applyTextureConfig(const Texture2DConfig& cfg)
{
	// Texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, cfg.textureWrapSMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, cfg.textureWrapTMode);
	if (cfg.hasBorder)
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(cfg.borderColor));


	// Texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, cfg.textureMinificationFilterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, cfg.textureMagnificationFilterMode);

	// Mipmapping
	if (cfg.hasMips)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, cfg.mipBias);
	}
}

void TextureManager::bind(const shared_ptr<Texture>& pTexture)
{
	glActiveTexture(GL_TEXTURE0 + pTexture->unit);
	glBindTexture(pTexture->textureTarget, pTexture->textureId);
	_pCurrTexture = pTexture;
}

void TextureManager::detach()
{
	glBindTexture(_pCurrTexture->textureTarget, 0);
}

void TextureManager::deleteTexture(const Texture& texture)
{
	if (texture.textureId != 0) {
		glDeleteTextures(1, &texture.textureId);
	}
}
