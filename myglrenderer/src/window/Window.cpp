#include "Window.h"
#include "Window.h"
#include "Window.h"
#include "common/utility.h"

Window::~Window(){
}

Window::Window():_pGLFWwindow(nullptr)
{
}

void Window::setWindowConfig(const WindowConfig& config) {
	this->config = config;
}


void Window::bindCallbacks() {
	glfwSetWindowUserPointer(_pGLFWwindow, this);
	glfwSetErrorCallback(errorCallback);
	glfwSetWindowSizeCallback(_pGLFWwindow, windowResizeCallback);
	glfwSetKeyCallback(_pGLFWwindow, keyCallback);
	glfwSetMouseButtonCallback(_pGLFWwindow, mouseButtonCallback);
	glfwSetCursorPosCallback(_pGLFWwindow, cursorPositionCallback);
	glfwSetScrollCallback(_pGLFWwindow, scrollCallback);
}

bool Window::create()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, config.msaaSampleCnt);
	if ((_pGLFWwindow = glfwCreateWindow(config.width, config.height, config.szTitle, NULL, NULL)) != nullptr) {
		glfwMakeContextCurrent(_pGLFWwindow);
		if (!initGLAD()) {
			return false;
		}
		if (config.hideCursor ) {
			glfwSetInputMode(_pGLFWwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	
		glfwSwapInterval(config.vsync == true ? 1 : 0);
		glViewport(config.vpx, config.vpy, config.vpWidth, config.vpHeight);
		return true;
	}
	return false;
}

void Window::update() const
{
	glfwSwapBuffers(_pGLFWwindow);
	glfwPollEvents();
}



void Window::terminate() const
{
	glfwTerminate();
}

bool Window::isTerminated() const
{
	return glfwWindowShouldClose(_pGLFWwindow);
}


void Window::setInputBuffer(InputBuffer& inputBuffer)
{
	pInputBuffer = &inputBuffer;
}

void Window::setCursorPos(float xpos, float ypos) {
	glfwSetCursorPos(_pGLFWwindow, xpos, ypos);
	pInputBuffer->cursorDeltaX = 0;
	pInputBuffer->cursorDeltaY = 0;
}

void Window::setCursorPosCenter() {
	setCursorPos(config.width / 2, config.height / 2);
}

void Window::errorCallback(int error, const char* description)
{
	printf("Error: %s\n", description);
}

void Window::windowResizeCallback(GLFWwindow* pGLFWwindow, int width, int height)
{
	Window* w = (Window*)glfwGetWindowUserPointer(pGLFWwindow);
	w->config.width = width;
	w->config.height = height;

	glViewport(0, 0, width, height);
}

void Window::keyCallback(GLFWwindow* pGLFWwindow, int key, int scancode, int action, int mods)
{
	Window* w = (Window*)glfwGetWindowUserPointer(pGLFWwindow);
	w->pInputBuffer->keyStatus[key] = action;

	if (key == GLFW_KEY_H && action == GLFW_RELEASE)
	{
		w->config.hideCursor = !w->config.hideCursor;
		GLenum cursorOption = w->config.hideCursor ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
		glfwSetInputMode(pGLFWwindow, GLFW_CURSOR, cursorOption);
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
		glfwSetWindowShouldClose(pGLFWwindow, true);
	}
}



void Window::mouseButtonCallback(GLFWwindow* pGLFWwindow, int button, int action, int mods)
{
	Window* w = (Window*)glfwGetWindowUserPointer(pGLFWwindow);
	w->pInputBuffer->mouseButtonStatus[button] = action;
}

void Window::cursorPositionCallback(GLFWwindow* pGLFWwindow, double xpos, double ypos)
{
	Window* w = (Window*)glfwGetWindowUserPointer(pGLFWwindow);
	
	w->pInputBuffer->cursorDeltaX = xpos - w->pInputBuffer->cursorX;
	w->pInputBuffer->cursorDeltaY = ypos - w->pInputBuffer->cursorY;
	w->pInputBuffer->cursorX = xpos;
	w->pInputBuffer->cursorY = ypos;
	//printf("dx = %lf, dy = %lf\n", w->pInputBuffer->cursorDeltaX, w->pInputBuffer->cursorDeltaY);
}

void Window::scrollCallback(GLFWwindow* pGLFWwindow, double deltaX, double deltaY)
{
	Window* w = (Window*)glfwGetWindowUserPointer(pGLFWwindow);
	w->pInputBuffer->scrollDeltaX = deltaX;
	w->pInputBuffer->scrollDeltaY = deltaY;
}
