#include "Editor.h"

#include "EditorSaveLoad.h"

#include "Engine.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "Camera.h"
#include "GameObject.h"
#include "Material.h"
#include "Mesh.h"
#include "DynamicObject.h"
#include "Time.h"
#include "TimeManager.h"
#include "Vector3.h"
#include "Window.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Physics.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

//Scripts TODO: make something that includes all scripts automatic
#include "scripts/ScreenSaverScript.h"
#include "scripts//MovementController.h"

void Editor::RunImGuiFrame()
{
	ImGui_ImplGlfwGL3_NewFrame();
	
	if (ImGui::Button("Play"))
	{
		if (!isPlaying)
		{
			isPlaying = true;
			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
			std::cout << "Play" << std::endl;
			engine.runEngine = true;
			engine.Run(scenePtr, windowPtr, this);

		}
		else
		{
			isPlaying = false;
			std::cout << "Stop" << std::endl;
			engine.runEngine = false;
			LoadEditorScene(scenePtr);
		}
	}
	else
	{
		if (ImGui::Button("Save"))
		{
			if (!isPlaying)
				EditorSaveLoad::SaveScene(scenePtr);
		}
		// 1. Show a simple window.
		// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
		static ImVec4 clear_color = ImVec4(scenePtr->renderer->backgroundColor.r, scenePtr->renderer->backgroundColor.g, scenePtr->renderer->backgroundColor.b, scenePtr->renderer->backgroundColor.a);

		static bool demo = false;
		ImGui::ShowDemoWindow(&demo);

		ImGui::Text("Scene");// Display some text (you can use a format string too)
		for (int i = 0; i < scenePtr->topGameObjects.size(); i++)
			if (ImGui::CollapsingHeader(scenePtr->topGameObjects[i]->name.c_str()))
				if (ImGui::InputFloat3("Position", &scenePtr->topGameObjects[i]->GetTransfrom()->GetPosition()->x))
					scenePtr->topGameObjects[i]->GetTransfrom()->SetPosition(*scenePtr->topGameObjects[i]->GetTransfrom()->GetPosition());

		ImGui::Spacing();

		ImGui::ColorEdit3("Background color", (float*)&clear_color);// Edit 3 floats representing a color
		scenePtr->renderer->backgroundColor.SetColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
	
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::LoadEditorScene(Scene* scene)
{
	scene->UnloadCurrentScene();
	scene->currentScene = scene;

	//Assets
	//Shaders
	std::unique_ptr<Shader> defaultShader(new Shader("res/shaders/NoTexture.shader"));
	defaultShader->Bind();
	defaultShader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	std::unique_ptr<Shader> shader(new Shader("res/shaders/Basic.shader"));
	shader->Bind();
	std::unique_ptr<Texture> texture(new Texture("res/textures/Antikythera.png"));
	int slot = 0;
	texture->Bind(slot);
	shader->SetUniform1i("u_Texture", slot);

	std::unique_ptr<Shader> playerShader(new Shader("res/shaders/Basic.shader"));
	playerShader->Bind();
	std::unique_ptr<Texture> playerTexture(new Texture("res/textures/Antikythera.png"));
	slot = 0;
	playerTexture->Bind(slot);
	playerShader->SetUniform1i("u_Texture", slot);

	std::unique_ptr<Shader> floorShader(new Shader("res/shaders/NoTexture.shader"));
	floorShader->Bind();
	floorShader->SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);

	std::unique_ptr<Shader> wallShader(new Shader("res/shaders/NoTexture.shader"));
	wallShader->Bind();
	wallShader->SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);
	//End Shaders

	//Materials
	std::unique_ptr<Material> defaultMaterial(new Material(std::move(defaultShader)));
	std::unique_ptr<Material> material(new Material(std::move(shader), std::move(texture)));
	std::unique_ptr<Material> playerMaterial(new Material(std::move(playerShader), std::move(playerTexture)));
	std::unique_ptr<Material> floorMaterial(new Material(std::move(floorShader)));
	std::unique_ptr<Material> wallMaterial(new Material(std::move(wallShader)));
	//End Materials

	//Mesh
	//create then save mesh
	std::unique_ptr<Mesh> defaultMesh(new Mesh());
	defaultMesh->ImportModelFromTxtFile("res/models/Square.txt");
	defaultMesh->SetMaterial(std::move(defaultMaterial));

	std::unique_ptr<Mesh> mesh(new Mesh());
	mesh->ImportModelFromTxtFile("res/models/Square.txt");
	mesh->SetMaterial(std::move(material));

	std::unique_ptr<Mesh> playerMesh(new Mesh());
	playerMesh->ImportModelFromTxtFile("res/models/Square.txt");
	playerMesh->SetMaterial(std::move(playerMaterial));

	std::unique_ptr<Mesh> floorMesh(new Mesh());
	floorMesh->ImportModelFromTxtFile("res/models/Square.txt");
	floorMesh->SetMaterial(std::move(floorMaterial));

	std::unique_ptr<Mesh> wallMesh(new Mesh());
	wallMesh->ImportModelFromTxtFile("res/models/Square.txt");
	wallMesh->SetMaterial(std::move(wallMaterial));
	//End Mesh
	//End Assets



	//Start - Custom to scene
	int windowWidth = 0;
	int windowHeight = 0;
	glfwGetWindowSize(windowPtr, &windowWidth, &windowHeight);
	float viewWidth = 5.0f;
	float aspectRatio = (float)windowWidth / (float)windowHeight;
	std::unique_ptr<Camera> camera(new Camera(aspectRatio, viewWidth, "camera"));
	scene->camera = std::move(camera);

	std::unique_ptr<Renderer> renderer(new Renderer(scene->camera.get()));
	renderer->backgroundColor.SetColor(0.14f, 0.5f, 0.85f, 1.0f);
	scene->renderer = std::move(renderer);

	std::unique_ptr<Physics> physics;
	physics->gravtity = -9.81f;
	physics->doGravtity = true;
	scene->physics = std::move(physics);

	//GameObject gameObject
	std::unique_ptr<GameObject> movingPic(new GameObject("Moving pic"));
	movingPic->SetMesh(std::move(mesh));

	std::unique_ptr<ScreenSaverScript> script(new ScreenSaverScript());
	script->camera = scene->camera.get();
	movingPic->AddScript(std::move(script));

	scene->AddGameObjectToScene(std::move(movingPic));
	//End gameObject

	//GameObject player
	std::unique_ptr<GameObject> player(new GameObject("Player"));
	player->SetMesh(std::move(playerMesh));
	player->GetTransfrom()->SetScale(2, 1, 0);
	player->SetTransformPosition(0, 1.5f, 0);

	std::unique_ptr<Rigidbody> playerRigidbody(new Rigidbody(scene->physics.get()));
	playerRigidbody->doGravity = true;
	player->SetRigidbody(std::move(playerRigidbody));

	std::unique_ptr<BoxCollider> playerBoxCollider(new BoxCollider(1.0f, 1.0f, Vector3()));
	player->SetCollider(std::move(playerBoxCollider));

	std::unique_ptr<MovementController> mc(new MovementController());
	mc->camera = scene->camera.get();
	player->AddScript(std::move(mc));

	scene->camera->GetGameObject()->GetTransfrom()->SetParent(player->GetTransfrom());

	scene->AddGameObjectToScene(std::move(player));
	//End player

	//GameObject pickupObject
	std::unique_ptr<GameObject> pickupObject(new GameObject("pickup Object"));
	pickupObject->SetMesh(std::move(defaultMesh));
	pickupObject->SetTransformPosition(2.0f, 1.0f, 0);

	std::unique_ptr<BoxCollider> staticBoxCollider(new BoxCollider(1.0f, 1.0f, Vector3()));
	staticBoxCollider->isTrigger = true;
	pickupObject->SetCollider(std::move(staticBoxCollider));

	scene->AddGameObjectToScene(std::move(pickupObject));
	//End pickupObject

	//GameObject floor
	std::unique_ptr<GameObject> floor(new GameObject("floor"));
	floor->GetTransfrom()->SetScale(5, 1, 1);

	floor->SetMesh(std::move(floorMesh));
	floor->SetTransformPosition(0, 0, 0);

	std::unique_ptr<BoxCollider> floorBoxCollider(new BoxCollider(1.0f, 1.0f, Vector3()));
	floor->SetCollider(std::move(floorBoxCollider));

	scene->AddGameObjectToScene(std::move(floor));
	//End floor

	//GameObject wall
	std::unique_ptr<GameObject> wall(new GameObject("wall"));
	wall->SetMesh(std::move(wallMesh));

	std::unique_ptr<BoxCollider> wallCollider(new BoxCollider(1.0f, 1.0f, Vector3()));
	wall->SetCollider(std::move(wallCollider));

	std::unique_ptr<Rigidbody> wallRigidbody(new Rigidbody(scene->physics.get()));
	wallRigidbody->doGravity = false;
	wall->SetRigidbody(std::move(wallRigidbody));
	wall->SetTransformPosition(1.0f, 2.5f, 0.0f);

	scene->AddGameObjectToScene(std::move(wall));
	//End wall

	scene->SetSceneHierarchy();
	//End - Custom to scene
}

int Editor::StartEditor()
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int windowWidth = 1600;
	int windowHeight = 900;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(windowWidth, windowHeight, "Antikythera", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "ERROR" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
	
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	
	{	
		Scene scene;
		scene.currentScene = &scene;
		scenePtr = &scene;

		windowPtr = window;

		LoadEditorScene(&scene);
		/*{
			//Shaders
			std::unique_ptr<Shader> defaultShader(new Shader("res/shaders/NoTexture.shader"));
			defaultShader->Bind();
			defaultShader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

			std::unique_ptr<Shader> shader(new Shader("res/shaders/Basic.shader"));
			shader->Bind();
			std::unique_ptr<Texture> texture(new Texture("res/textures/Antikythera.png"));
			int slot = 0;
			texture->Bind(slot);
			shader->SetUniform1i("u_Texture", slot);

			std::unique_ptr<Shader> playerShader(new Shader("res/shaders/Basic.shader"));
			playerShader->Bind();
			std::unique_ptr<Texture> playerTexture(new Texture("res/textures/Antikythera.png"));
			slot = 0;
			playerTexture->Bind(slot);
			playerShader->SetUniform1i("u_Texture", slot);

			std::unique_ptr<Shader> floorShader(new Shader("res/shaders/NoTexture.shader"));
			floorShader->Bind();
			floorShader->SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);

			std::unique_ptr<Shader> wallShader(new Shader("res/shaders/NoTexture.shader"));
			wallShader->Bind();
			wallShader->SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);
			//End Shaders

			//Materials
			std::unique_ptr<Material> defaultMaterial(new Material(std::move(defaultShader)));
			std::unique_ptr<Material> material(new Material(std::move(shader), std::move(texture)));
			std::unique_ptr<Material> playerMaterial(new Material(std::move(playerShader), std::move(playerTexture)));
			std::unique_ptr<Material> floorMaterial(new Material(std::move(floorShader)));
			std::unique_ptr<Material> wallMaterial(new Material(std::move(wallShader)));
			//End Materials

			//Mesh
			std::unique_ptr<Mesh> defaultMesh(new Mesh());
			defaultMesh->ImportModelFromTxtFile("res/models/Square.txt");
			defaultMesh->SetMaterial(std::move(defaultMaterial));

			std::unique_ptr<Mesh> mesh(new Mesh());
			mesh->ImportModelFromTxtFile("res/models/Square.txt");
			mesh->SetMaterial(std::move(material));

			std::unique_ptr<Mesh> playerMesh(new Mesh());
			playerMesh->ImportModelFromTxtFile("res/models/Square.txt");
			playerMesh->SetMaterial(std::move(playerMaterial));

			std::unique_ptr<Mesh> floorMesh(new Mesh());
			floorMesh->ImportModelFromTxtFile("res/models/Square.txt");
			floorMesh->SetMaterial(std::move(floorMaterial));

			std::unique_ptr<Mesh> wallMesh(new Mesh());
			wallMesh->ImportModelFromTxtFile("res/models/Square.txt");
			wallMesh->SetMaterial(std::move(wallMaterial));
			//End Mesh

			//Start - Custom to scene
			//GameObject gameObject
			std::unique_ptr<GameObject> movingPic(new GameObject("Moving pic"));
			movingPic->SetMesh(std::move(mesh));

			std::unique_ptr<ScreenSaverScript> script(new ScreenSaverScript());
			script->camera = &camera;
			movingPic->AddScript(std::move(script));

			scene.AddGameObjectToScene(std::move(movingPic));
			//End gameObject

			//GameObject player
			std::unique_ptr<GameObject> player(new GameObject("Player"));
			player->SetMesh(std::move(playerMesh));
			player->GetTransfrom()->SetScale(2, 1, 0);
			player->SetTransformPosition(0, 1.5f, 0);

			std::unique_ptr<Rigidbody> playerRigidbody(new Rigidbody(&physics));
			playerRigidbody->doGravity = true;
			player->SetRigidbody(std::move(playerRigidbody));

			std::unique_ptr<BoxCollider> playerBoxCollider(new BoxCollider(1.0f, 1.0f, Vector3()));
			player->SetCollider(std::move(playerBoxCollider));

			std::unique_ptr<MovementController> mc(new MovementController());
			mc->camera = &camera;
			player->AddScript(std::move(mc));

			camera.GetGameObject()->GetTransfrom()->SetParent(player->GetTransfrom());

			scene.AddGameObjectToScene(std::move(player));
			//End player

			//GameObject pickupObject
			std::unique_ptr<GameObject> pickupObject(new GameObject("pickup Object"));
			pickupObject->SetMesh(std::move(defaultMesh));
			pickupObject->SetTransformPosition(2.0f, 1.0f, 0);

			std::unique_ptr<BoxCollider> staticBoxCollider(new BoxCollider(1.0f, 1.0f, Vector3()));
			staticBoxCollider->isTrigger = true;
			pickupObject->SetCollider(std::move(staticBoxCollider));

			scene.AddGameObjectToScene(std::move(pickupObject));
			//End pickupObject

			//GameObject floor
			std::unique_ptr<GameObject> floor(new GameObject("floor"));
			floor->GetTransfrom()->SetScale(5, 1, 1);

			floor->SetMesh(std::move(floorMesh));
			floor->SetTransformPosition(0, 0, 0);

			std::unique_ptr<BoxCollider> floorBoxCollider(new BoxCollider(1.0f, 1.0f, Vector3()));
			floor->SetCollider(std::move(floorBoxCollider));

			scene.AddGameObjectToScene(std::move(floor));
			//End floor

			//GameObject wall
			std::unique_ptr<GameObject> wall(new GameObject("wall"));
			wall->SetMesh(std::move(wallMesh));

			std::unique_ptr<BoxCollider> wallCollider(new BoxCollider(1.0f, 1.0f, Vector3()));
			wall->SetCollider(std::move(wallCollider));

			std::unique_ptr<Rigidbody> wallRigidbody(new Rigidbody(&physics));
			wallRigidbody->doGravity = false;
			wall->SetRigidbody(std::move(wallRigidbody));
			wall->SetTransformPosition(1.0f, 2.5f, 0.0f);

			scene.AddGameObjectToScene(std::move(wall));
			//End wall
			//End - Custom to scene
		}*/

		while (!glfwWindowShouldClose(window))
		{
			scene.renderer->Clear();
			scene.RenderScene();

			RunImGuiFrame();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

	return 0;
}