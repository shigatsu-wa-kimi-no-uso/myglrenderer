#pragma once
#ifndef RENDER_PIPELINE_H
#define RENDER_PIPELINE_H
#include "common/global.h"
#include "../RenderContext.h"

class Renderer;

class RenderPipeline
{
public:
	virtual void render(const hashmap<uint, shared_ptr<RenderContext>>& contexts, Renderer& renderer) const = 0;
};

#endif // !RENDER_PIPELINE_H

