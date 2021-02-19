#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static class Window
{
private:
	static GLFWwindow* glfwWindow;
public:
	Window(GLFWwindow* window);
	~Window();

	static void SetWindow(GLFWwindow* window);
	static GLFWwindow* GetGLFWWindow() { return glfwWindow; }
};