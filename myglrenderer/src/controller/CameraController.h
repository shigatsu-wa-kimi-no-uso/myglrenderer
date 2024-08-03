#pragma once
#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H
#include "common/global.h"
#include "device/camera/Camera.h"
#include "window/Window.h"

class CameraController
{
private:
	Camera* pCamera;
	InputBuffer* pInputBuffer;
	Window* pWindow;
	double deltaTime;
	double lastFrameTime;
public:
	float cursorSensitivity = 0.05f;
	float zoomSensitivity = 2;
	CameraController(Camera* pCamera, InputBuffer* pInputBuffer);

	CameraController();

	double getFrameDeltaTime();

	void setCamera(Camera& camera);

	void setInputBuffer(InputBuffer& inputBuffer);

	void setWindow(Window& window);

	void refreshFrameTime();

	void refreshCamera();

	void moveCamera();

	void updateView();

	void updateFoV();


};


#endif // !CAMERA_CONTROLLER_H

