#pragma
#ifndef TEXTURE2D_H
#define TEXTURE2D_H
#include "common/global.h"
#include "common/image.h"
#include "device/model/material/Texture.h"


struct Texture2DConfig
{	
	// Texture wrapping options
	GLenum textureWrapSMode = GL_REPEAT;
	GLenum textureWrapTMode = GL_REPEAT;
	bool hasBorder = false;
	vec4 borderColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Texture filtering options
	GLenum textureMinificationFilterMode = GL_LINEAR_MIPMAP_LINEAR; // Filtering mode when the texture moves further away and multiple texels map to one pixel (trilinear for best quality)
	GLenum textureMagnificationFilterMode = GL_LINEAR; // Filtering mode when the texture gets closer and multiple pixels map to a single texel (Never needs to be more than bilinear because that is as accurate as it gets in this sitation)


	// Mip options
	bool hasMips = true;
	int mipBias = 0; // positive means blurrier texture selected, negative means sharper texture which can show texture aliasing
};


class TextureManager
{
private:
	shared_ptr<const Texture> _pCurrTexture;
	
public:
	TextureManager();

	void create2DTexture(shared_ptr<Texture>& pTexture, uint unit = 0, GLenum textureFmt = GL_NONE, GLenum pixelDataType = GL_UNSIGNED_BYTE);

	void create2DTexture(Texture& texture, uint unit = 0, GLenum textureFmt = GL_NONE, GLenum pixelDataType = GL_UNSIGNED_BYTE);
	
	Texture create2DTexture(const Image& image ,GLenum dataFmt, uint unit = 0,GLenum textureFmt = GL_NONE, GLenum pixelDataType = GL_UNSIGNED_BYTE);

	void applyTextureConfig(const Texture2DConfig& cfg);

	void bind(const shared_ptr<Texture>& pTexture);

	void detach();

	void deleteTexture(const Texture& texture);

};

#endif // !TEXTURE2D_H
