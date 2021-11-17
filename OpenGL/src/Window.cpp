#include "Window.h"

GLFWwindow *Window::glfwWindow;

Window::Window(GLFWwindow* window)
{
	glfwWindow = window;
}

Window::~Window()
{
	delete(glfwWindow);
}

void Window::SetWindow(GLFWwindow * window)
{
	glfwWindow = window;
}