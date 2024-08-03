#include "Texture.h"



Texture::Texture()
{

}

Texture::~Texture()
{

}

bool Texture::hasAlpha() {
	return image.componentCnt == 4;
}

const char* textureTypeString(aiTextureType textureType) {
	switch (textureType)
	{
	case aiTextureType_NONE:
		return "none";
	case aiTextureType_DIFFUSE:
		return "diffuse";
	case aiTextureType_SPECULAR:
		return "specular";
	case aiTextureType_AMBIENT:
		return "ambient";
	case aiTextureType_EMISSIVE:
		return "emissive";
	case aiTextureType_HEIGHT:
		return "height";
	case aiTextureType_NORMALS:
		return "normal";
	case aiTextureType_SHININESS:
		return "shininess";
	case aiTextureType_OPACITY:
		return "opacity";
	case aiTextureType_DISPLACEMENT:
		return "displacement";
	case aiTextureType_LIGHTMAP:
		return "light";
	case aiTextureType_REFLECTION:
		return "reflection";
	case aiTextureType_BASE_COLOR:
		return "baseColor";
	case aiTextureType_NORMAL_CAMERA:
		return "normalCamera";
	case aiTextureType_EMISSION_COLOR:
		return "emissionColor";
	case aiTextureType_METALNESS:
		return "metalness";
	case aiTextureType_DIFFUSE_ROUGHNESS:
		return "diffuseRoughness";
	case aiTextureType_AMBIENT_OCCLUSION:
		return "ambientOcclusion";
	case aiTextureType_SHEEN:
		return "sheen";
	case aiTextureType_CLEARCOAT:
		return "clearcoat";
	case aiTextureType_TRANSMISSION:
		return "transmission";
	case aiTextureType_UNKNOWN:
		return nullptr;
	case _aiTextureType_Force32Bit:
		return "force32bit";
	default:
		return nullptr;
	}
}
