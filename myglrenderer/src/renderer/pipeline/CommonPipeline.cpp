#include "CommonPipeline.h"

#include "../Renderer.h"


void CommonPipeline::render(const hashmap<uint, shared_ptr<RenderContext>>& contexts, Renderer& renderer) const
{
	renderer.cameraController.refreshFrameTime();
	sortedmap<float,shared_ptr<RenderContext>,std::greater<float>> transparentContexts;
	while (!renderer.window.isTerminated()) {
		uint fps = uint(1 / renderer.cameraController.getFrameDeltaTime());
		printf("FPS: %d, FoV: %.3f, pos:(%.3f,%.3f,%.3f), front:(%.3f,%.3f,%.3f), up:(%.3f,%.3f,%.3f)\r", fps, RenderContext::camera.getFoV(),
			RenderContext::camera.config.cameraPos.x,
			RenderContext::camera.config.cameraPos.y,
			RenderContext::camera.config.cameraPos.z,
			RenderContext::camera.config.front.x,
			RenderContext::camera.config.front.y,
			RenderContext::camera.config.front.z,
			RenderContext::camera.config.cameraUp.x,
			RenderContext::camera.config.cameraUp.y,
			RenderContext::camera.config.cameraUp.z
		);

		renderer.canvasMgr.clearCanvas(vec4(0.2f, 0.3f, 0.3f, 1.0f));
		renderer.cameraController.refreshFrameTime();
		renderer.cameraController.refreshCamera();
		for (const pair<uint, shared_ptr<RenderContext>>& elem : contexts) {
			const shared_ptr<RenderContext>& c = elem.second;
			/*
			if (c->textureHasAlpha()) {
				
				continue;
			}*/
			//printf("rendering context %u\n", elem.first);
			/*
			mat4 modeling = mat4(1);
			modeling = translate(modeling, cubePositions[i]);
			float angle = 20 * i;
			modeling = rotate(modeling, radians(angle), vec3(1, 0.3, 0.5));
			c->pModeling = modeling;*/
			renderer.bindContext(c);
			glDrawElements(GL_TRIANGLES, c->meshBuffer.vertexCnt, GL_UNSIGNED_INT, 0);
			
		}



		renderer.window.update();
	}

}
