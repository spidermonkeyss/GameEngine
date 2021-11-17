#pragma once

#include "Scene.h"
class Editor;

class Engine
{
public:
	bool runEngine = false;
	int Run(Scene* scene, GLFWwindow * window, Editor* editor);
};