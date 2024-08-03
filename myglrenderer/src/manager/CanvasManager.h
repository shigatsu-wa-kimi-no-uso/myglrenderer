#pragma once
#ifndef CANVAS_MANAGER_H
#define CANVAS_MANAGER_H
#include "common/global.h"

class CanvasManager
{
public:
	static void enableDepthTesting();

	static void disableDepthTesting();

	static void clearCanvas(const vec4& color);

	static void drawTriangleElements(uint elemCnt);

	static void enableBlend();

	static void enableCullFace(GLenum mode);
};


#endif // !CANVAS_MANAGER_H
