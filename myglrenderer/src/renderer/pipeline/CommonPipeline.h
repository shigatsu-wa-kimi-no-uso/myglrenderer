#pragma once
#ifndef COMMON_PIPELINE_H
#define COMMON_PIPELINE_H
#include "RenderPipeline.h"


class CommonPipeline : public RenderPipeline
{
public:
	CommonPipeline(){}
	vec3 cubePositions[10] = {
		vec3(0.0f,  0.0f,  0.0f),
		vec3(2.0f,  5.0f, -15.0f),
		vec3(-1.5f, -2.2f, -2.5f),
		vec3(-3.8f, -2.0f, -12.3f),
		vec3(2.4f, -0.4f, -3.5f),
		vec3(-1.7f,  3.0f, -7.5f),
		vec3(1.3f, -2.0f, -2.5f),
		vec3(1.5f,  2.0f, -2.5f),
		vec3(1.5f,  0.2f, -1.5f),
		vec3(-1.3f,  1.0f, -1.5f)
	};

	void render(const hashmap<uint, shared_ptr<RenderContext>>& contexts, Renderer& renderer) const override;
};

	

#endif // !COMMON_PIPELINE_H

