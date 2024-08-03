#include "CameraController.h"


CameraController::CameraController(Camera* pCamera,InputBuffer* pInputBuffer)
	:pCamera(pCamera), pInputBuffer(pInputBuffer),deltaTime(0),lastFrameTime(0)
{}


CameraController::CameraController()
	:pCamera(nullptr), pInputBuffer(nullptr), deltaTime(0), lastFrameTime(0)
{}

void CameraController::setCamera(Camera & camera)
{
	pCamera = &camera;
}

void CameraController::setInputBuffer(InputBuffer& inputBuffer)
{
	pInputBuffer = &inputBuffer;
}

void CameraController::setWindow(Window& window) {
	pWindow = &window;
}

void CameraController::refreshFrameTime()
{
	double currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrameTime;
	lastFrameTime = currentFrame;
}

double CameraController::getFrameDeltaTime()
{
	return deltaTime;
}

void CameraController::refreshCamera()
{
	moveCamera();
	updateView();
	updateFoV();
}

void CameraController::moveCamera()
{
	float movementSpeed = deltaTime * 2.5f;
	uint movement = 0;

	if (pInputBuffer->keyStatus[GLFW_KEY_W] != GLFW_RELEASE) {
		movement |= uint(CameraMovement::FORWARD);
	}
	if (pInputBuffer->keyStatus[GLFW_KEY_S] != GLFW_RELEASE) {
		movement |= uint(CameraMovement::BACKWORD);
	}
	if (pInputBuffer->keyStatus[GLFW_KEY_A] != GLFW_RELEASE) {
		movement |= uint(CameraMovement::LEFT);
	}
	if (pInputBuffer->keyStatus[GLFW_KEY_D] != GLFW_RELEASE) {
		movement |= uint(CameraMovement::RIGHT);
	}
	if (pInputBuffer->keyStatus[GLFW_KEY_SPACE] != GLFW_RELEASE) {
		movement |= uint(CameraMovement::UP);
	}
	if (pInputBuffer->keyStatus[GLFW_KEY_LEFT_CONTROL] != GLFW_RELEASE) {
		movement |= uint(CameraMovement::DOWN);
	}

	pCamera->updateCameraPos(movement, movementSpeed);
}

void CameraController::updateView()
{
	float offsetX = cursorSensitivity * pInputBuffer->cursorDeltaX;
	float offsetY = -cursorSensitivity * pInputBuffer->cursorDeltaY;
	pInputBuffer->cursorDeltaX = 0;
	pInputBuffer->cursorDeltaY = 0;
	pCamera->updateCameraView(offsetX, offsetY);
}

void CameraController::updateFoV()
{
	pCamera->updateCameraZoom(pInputBuffer->scrollDeltaY * zoomSensitivity);
	pInputBuffer->scrollDeltaY = 0;
}
