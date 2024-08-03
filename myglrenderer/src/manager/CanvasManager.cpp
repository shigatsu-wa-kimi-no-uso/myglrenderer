#include "CanvasManager.h"
#include "CanvasManager.h"
#include "CanvasManager.h"
#include "CanvasManager.h"
#include "CanvasManager.h"

void CanvasManager::enableDepthTesting()
{
	glEnable(GL_DEPTH_TEST);
}

void CanvasManager::disableDepthTesting()
{
	glDisable(GL_DEPTH_TEST);
}

void CanvasManager::clearCanvas(const vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void CanvasManager::drawTriangleElements(uint elemCnt) {
	glDrawElements(GL_TRIANGLES, elemCnt, GL_UNSIGNED_INT, nullptr);
}

void CanvasManager::enableBlend()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CanvasManager::enableCullFace(GLenum mode) {
	glEnable(GL_CULL_FACE);
	glCullFace(mode);
}
