#include "Input.h"

#include "Window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

bool Input::previousFrameKeysPressed[];

bool Input::GetKey(KeyCode keyCode)
{
	switch (keyCode)
	{
	case Q:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_Q) == GLFW_PRESS)
			return true;
		break;
	case W:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_W) == GLFW_PRESS)
		{
			previousFrameKeysPressed[W] = true;
			return true;
		}
		break;
	case E:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_E) == GLFW_PRESS)
			return true;
		break;
	case R:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_R) == GLFW_PRESS)
			return true;
		break;
	case T:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_T) == GLFW_PRESS)
			return true;
		break;
	case Y:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_Y) == GLFW_PRESS)
			return true;
		break;
	case U:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_U) == GLFW_PRESS)
			return true;
		break;
	case I:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_I) == GLFW_PRESS)
			return true;
		break;
	case O:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_O) == GLFW_PRESS)
			return true;
		break;
	case P:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_P) == GLFW_PRESS)
			return true;
		break;
	case A:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS)
			return true;
		break;
	case S:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_S) == GLFW_PRESS)
			return true;
		break;
	case D:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_D) == GLFW_PRESS)
			return true;
		break;
	case F:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_F) == GLFW_PRESS)
			return true;
		break;
	case G:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_G) == GLFW_PRESS)
			return true;
		break;
	case H:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_H) == GLFW_PRESS)
			return true;
		break;
	case J:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_J) == GLFW_PRESS)
			return true;
		break;
	case K:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_K) == GLFW_PRESS)
			return true;
		break;
	case L:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_L) == GLFW_PRESS)
			return true;
		break;
	case Z:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_Z) == GLFW_PRESS)
			return true;
		break;
	case X:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_X) == GLFW_PRESS)
			return true;
		break;
	case C:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_C) == GLFW_PRESS)
			return true;
		break;
	case V:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_V) == GLFW_PRESS)
			return true;
		break;
	case B:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_B) == GLFW_PRESS)
			return true;
		break;
	case N:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_N) == GLFW_PRESS)
			return true;
		break;
	case M:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_M) == GLFW_PRESS)
			return true;
		break;
	case SPACE:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
			return true;
		break;
	default:
		return false;
		break;
	}
	return false;
}

bool Input::GetKeyDown(KeyCode keyCode)
{
	switch (keyCode)
	{
	case W:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_W) == GLFW_PRESS && !previousFrameKeysPressed[W])
		{
			previousFrameKeysPressed[W] = true;
			return true;
		}
		break;
	case G:
		if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_G) == GLFW_PRESS && !previousFrameKeysPressed[G])
		{
			previousFrameKeysPressed[G] = true;
			return true;
		}
		break;

	default:
		return false;
		break;
	}
	return false;
}

void Input::OnUpdate()
{
	if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_W) == GLFW_RELEASE)
		previousFrameKeysPressed[W] = false;
	if (glfwGetKey(Window::GetGLFWWindow(), GLFW_KEY_G) == GLFW_RELEASE)
		previousFrameKeysPressed[G] = false;
}
