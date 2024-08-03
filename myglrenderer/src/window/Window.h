#pragma once
#ifndef WINDOW_H
#define WINDOW_H
#include "common/global.h"
#include "manager/CanvasManager.h"

struct WindowConfig
{
	int glVerMajor, glVerMinor;
	const char* szTitle;
	int width, height;
	bool hideCursor, vsync;
	int msaaSampleCnt;
	int vpx, vpy, vpWidth, vpHeight;
};

struct InputBuffer 
{
	uint keyStatus[GLFW_KEY_LAST] = { 0 };
	uint mouseButtonStatus[32] = { 0 }; //0 == GLFW_RELEASE
	double cursorX = 0, cursorY = 0;
	double cursorDeltaX = 0, cursorDeltaY = 0;
	double scrollDeltaX= 0, scrollDeltaY = 0;
};

class Window
{
private:
	GLFWwindow* _pGLFWwindow;

	static void errorCallback(int error, const char* description);
	static void windowResizeCallback(GLFWwindow* pGLFWwindow, int width, int height);
	static void keyCallback(GLFWwindow* pGLFWwindow, int key, int scancode, int action, int mods);
	static void mouseButtonCallback(GLFWwindow* pGLFWwindow, int button, int action, int mods);
	static void cursorPositionCallback(GLFWwindow* pGLFWwindow, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* pGLFWwindow, double xoffset, double yoffset);

public:
	WindowConfig config;
	InputBuffer* pInputBuffer;
	~Window();
	Window();
	void setInputBuffer(InputBuffer& inputBuffer);
	void setWindowConfig(const WindowConfig& config);
	void setCursorPos(float xpos, float ypos);
	void setCursorPosCenter();
	void bindCallbacks();
	bool create();
	void update() const;
	void terminate() const;
	bool isTerminated() const;


};




#endif // !WINDOW_H

