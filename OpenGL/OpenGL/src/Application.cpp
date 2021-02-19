#include "Editor/Editor.h"
#include "Engine.h"

#include <time.h>

int main(void)
{
	srand(time(NULL));
	bool runEditor = true;
	if (runEditor)
	{
		Editor editor;
		int returnInt = editor.StartEditor();

		return returnInt;
	}
	else
	{
		Engine engine;
		Scene scene;
		int returnInt = engine.Run(&scene, nullptr, nullptr);
		glfwTerminate();

		return returnInt;
	}
}