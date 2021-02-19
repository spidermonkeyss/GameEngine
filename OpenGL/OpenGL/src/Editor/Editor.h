#pragma once

#include "GLCall.h"
#include "Scene.h"
#include "Engine.h"

class Editor
{
private:
	Engine engine;
	bool isPlaying = false;
	Scene* scenePtr;
	GLFWwindow* windowPtr;
public:
	void RunImGuiFrame();
	void LoadEditorScene(Scene* scene);
	
	int StartEditor();
};