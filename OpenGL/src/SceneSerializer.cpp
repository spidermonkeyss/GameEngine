#include "SceneSerializer.h"

#include <filesystem>

#include "Mesh.h"
#include "BoxCollider.h"

#include "yaml-cpp/yaml.h"

#include <fstream>

SceneSerializer::SceneSerializer()
{
}

void SceneSerializer::SerializeYAML(Scene * scene, const std::string& filePath)
{
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "Scene Name" << YAML::Value << "scene";
	out << YAML::Key << "GameObjects" << YAML::Value << YAML::BeginSeq;
	for (int i = 0; i < scene->gameObjects.size(); i++)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "FileID" << YAML::Value << scene->gameObjects[i]->GetFileID();
		out << YAML::Key << "Name" << YAML::Value << scene->gameObjects[i]->name;
		//Mesh
		out << YAML::Key << "Mesh" << YAML::Value << scene->gameObjects[i]->GetMesh()->GetFileID();
		//Trasform
		out << YAML::Key << "Transform" << YAML::BeginMap;
		out << YAML::Key << "Position" << YAML::BeginMap;
		out << YAML::Key << "X" << YAML::Value << scene->gameObjects[i]->GetTransfrom()->GetPosition()->x;
		out << YAML::Key << "Y" << YAML::Value << scene->gameObjects[i]->GetTransfrom()->GetPosition()->y;
		out << YAML::Key << "Z" << YAML::Value << scene->gameObjects[i]->GetTransfrom()->GetPosition()->z;
		out << YAML::EndMap;//position
		out << YAML::Key << "Scale" << YAML::BeginMap;
		out << YAML::Key << "X" << YAML::Value << scene->gameObjects[i]->GetTransfrom()->GetScale().x;
		out << YAML::Key << "Y" << YAML::Value << scene->gameObjects[i]->GetTransfrom()->GetScale().y;
		out << YAML::Key << "Z" << YAML::Value << scene->gameObjects[i]->GetTransfrom()->GetScale().z;
		out << YAML::EndMap;//scale
		if (scene->gameObjects[i]->GetTransfrom()->GetParent() != nullptr)
			out << YAML::Key << "ParentID" << YAML::Value << scene->gameObjects[i]->GetTransfrom()->GetParent()->gameObject->GetFileID();
		out << YAML::EndMap;//transform
		//collider
		if (scene->gameObjects[i]->GetCollider() != nullptr)
		{
			out << YAML::Key << "Collider" << YAML::BeginMap;
			out << YAML::Key << "Width" << YAML::Value << dynamic_cast<BoxCollider*>(scene->gameObjects[i]->GetCollider())->width;
			out << YAML::Key << "Height" << YAML::Value << dynamic_cast<BoxCollider*>(scene->gameObjects[i]->GetCollider())->height;
			out << YAML::Key << "Offset" << YAML::BeginMap;
			out << YAML::Key << "X" << YAML::Value << scene->gameObjects[i]->GetCollider()->colliderOffset.x;
			out << YAML::Key << "Y" << YAML::Value << scene->gameObjects[i]->GetCollider()->colliderOffset.y;
			out << YAML::Key << "Z" << YAML::Value << scene->gameObjects[i]->GetCollider()->colliderOffset.z;
			out << YAML::EndMap;//Offset
			out << YAML::Key << "Enabled" << YAML::Value << scene->gameObjects[i]->GetCollider()->enabled;
			out << YAML::Key << "isTrigger" << YAML::Value << scene->gameObjects[i]->GetCollider()->enabled;
			out << YAML::EndMap;//Collider
		}
		//rigidbody
		if (scene->gameObjects[i]->GetRigidbody() != nullptr)
		{
			out << YAML::Key << "RigidBody" << YAML::BeginMap;
			out << YAML::Key << "Enabled" << YAML::Value << scene->gameObjects[i]->GetRigidbody()->enabled;
			out << YAML::Key << "doGravity" << YAML::Value << scene->gameObjects[i]->GetRigidbody()->doGravity;
			out << YAML::EndMap;//RigidBody			
		}
		//scripts these will be save as fileIDs as well
		if (scene->gameObjects[i]->dynamicObjectScripts.size() > 0)
		{
			
		}

		out << YAML::EndMap;
	}
	out << YAML::EndSeq;
	out << YAML::EndMap;
	
	std::ofstream fout(filePath);
	fout << out.c_str();
}

void SceneSerializer::DeserializeYAML(Scene * scene, const std::string& filePath)
{
	scene->UnloadCurrentScene();
	scene->currentScene = scene;

	//std::cout << std::filesystem::current_path();
	
	std::ifstream stream(filePath);
	std::stringstream strStream;
	strStream << stream.rdbuf();
	YAML::Node data = YAML::Load(strStream.str());
	if (!data["Scene Name"])
		return;

	std::ifstream idStream("fileIDs/" + data["Scene Name"].as<std::string>() + ".paths");
	std::stringstream idStrStream;
	idStrStream << idStream.rdbuf();

	YAML::Node idFilePaths = YAML::Load(idStrStream.str());

	auto gameObjects = data["GameObjects"];
	for (int i = 0; i < gameObjects.size(); i++)
	{
		std::string name = "";
		if (gameObjects[i]["Name"])
			name = gameObjects[i]["Name"].as<std::string>();
		std::unique_ptr<GameObject> gameObject(new GameObject(name));

		//Load Mesh
		if (gameObjects[i]["Mesh"])
		{
			unsigned int meshID = gameObjects[i]["Mesh"].as<unsigned int>();
			gameObject->SetMesh(std::move(DeSerializeMesh(meshID, idFilePaths)));
		}

		float x = gameObjects[i]["Transform"]["Position"]["X"].as<float>();
		float y = gameObjects[i]["Transform"]["Position"]["Y"].as<float>();
		float z = gameObjects[i]["Transform"]["Position"]["Z"].as<float>();
		gameObject->SetTransformPosition(x, y, z);
		
		float scaleX = gameObjects[i]["Transform"]["Scale"]["X"].as<float>();
		float scaleY = gameObjects[i]["Transform"]["Scale"]["Y"].as<float>();
		float scaleZ = gameObjects[i]["Transform"]["Scale"]["Z"].as<float>();
		gameObject->GetTransfrom()->SetScale(scaleX, scaleY, scaleZ);
		gameObject->SetFileID(gameObjects[i]["FileID"].as<unsigned int>());

		if (gameObjects[i]["Transform"]["ParentID"])
			gameObject->GetTransfrom()->SetParentID(gameObjects[i]["Transform"]["ParentID"].as<unsigned int>());

		//colliders
		if (gameObjects[i]["Collider"])
		{
			float width = gameObjects[i]["Collider"]["Width"].as<float>();
			float height = gameObjects[i]["Collider"]["Width"].as<float>();
			Vector3 offset(gameObjects[i]["Collider"]["Offset"]["X"].as<float>(), gameObjects[i]["Collider"]["Offset"]["Y"].as<float>(), gameObjects[i]["Collider"]["Offset"]["Z"].as<float>());
			std::unique_ptr<BoxCollider> collider(new BoxCollider(width, height, offset));
			collider->enabled = gameObjects[i]["Collider"]["Enabled"].as<bool>();
			collider->enabled = gameObjects[i]["Collider"]["isTrigger"].as<bool>();
			gameObject->SetCollider(std::move(collider));
		}
		//rigidbody
		if (gameObjects[i]["RigidBody"])
		{
			std::unique_ptr<Rigidbody> rigidBody(new Rigidbody(scene->physics.get()));
			rigidBody->enabled = gameObjects[i]["RigidBody"]["Enabled"].as<bool>();
			rigidBody->doGravity = gameObjects[i]["RigidBody"]["doGravity"].as<bool>();
			gameObject->SetRigidbody(std::move(rigidBody));
		}
		//scripts
		if (gameObjects[i]["Scripts"])
		{
			for (int i = 0; i < gameObject->dynamicObjectScripts.size(); i++)
			{
				unsigned int scriptFileID = gameObjects[i]["Scripts"][std::to_string(i).c_str()].as<unsigned int>();
				idFilePaths[scriptFileID];

				//gameObject->dynamicObjectScripts[i];
				//std::unique_ptr<MovementController> script(new MovementController());
				//script->camera = scene->camera.get();
				//gameObject->AddScript(std::move(script));
			}
		}

		scene->AddGameObjectToScene(std::move(gameObject));
	}

	//Set parents after loading all objects first
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (scene->gameObjects[i]->GetTransfrom()->GetParentID() != 0)
		{
			for (int j = 0; j < scene->gameObjects.size(); j++)
			{
				if (scene->gameObjects[i]->GetTransfrom()->GetParentID() == scene->gameObjects[j]->GetFileID())
					scene->gameObjects[i]->GetTransfrom()->SetParent(scene->gameObjects[j]->GetTransfrom());
			}
		}
	}

	scene->SetSceneHierarchy();
}

void SceneSerializer::SerializeMesh(const std::string & filePath, Mesh* mesh)
{
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "FileID" << YAML::Value << mesh->GetFileID();
	out << YAML::Key << "MaterialID" << YAML::Value << mesh->GetMaterial()->GetFileID();
	out << YAML::EndMap;

	std::ofstream fout(filePath);
	fout << out.c_str();
	
	UpdateFilePathIDs(filePath, mesh->GetFileID());
}

void SceneSerializer::SerializeMaterial(const std::string & filePath, Material * material)
{
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "FileID" << YAML::Value << material->GetFileID();
	out << YAML::Key << "ShaderFilePath" << YAML::Value << material->GetShader()->GetFilePath();
	if (material->GetTexture() != nullptr)
		out << YAML::Key << "TextureFilePath" << YAML::Value << material->GetTexture()->GetFilePath();
	out << YAML::Key << "ShaderColor" << YAML::Value << YAML::BeginMap;
	out << YAML::Key << "r" << YAML::Value << material->shader_color.r;
	out << YAML::Key << "g" << YAML::Value << material->shader_color.g;
	out << YAML::Key << "b" << YAML::Value << material->shader_color.b;
	out << YAML::Key << "a" << YAML::Value << material->shader_color.a;
	out << YAML::EndMap;

	std::ofstream fout(filePath);
	fout << out.c_str();

	UpdateFilePathIDs(filePath, material->GetFileID());
}

//ONLY USED FOR DEBUGGING
void SceneSerializer::UpdateFilePathIDs(const std::string & filePath, unsigned int id)
{
	std::ifstream stream("fileIDs/idFilePaths.paths");
	std::stringstream strStream;
	strStream << stream.rdbuf();

	YAML::Node data = YAML::Load(strStream.str());
	YAML::Emitter idFilePath;
	if (!data[id])
	{
		idFilePath << YAML::BeginMap;
		idFilePath << YAML::Key << id << YAML::Value << filePath;
		idFilePath << YAML::EndMap;
	
		std::ofstream fout("fileIDs/idFilePaths.paths", std::ofstream::app);
		fout << idFilePath.c_str() << std::endl;
	}
}

std::unique_ptr<Mesh> SceneSerializer::DeSerializeMesh(unsigned int meshID, YAML::Node idFilePaths)
{
	std::unique_ptr<Mesh> mesh(new Mesh(meshID));
	if (idFilePaths[meshID])
	{
		std::ifstream meshStream(idFilePaths[meshID].as<std::string>());
		std::stringstream meshStrStream;
		meshStrStream << meshStream.rdbuf();
		YAML::Node meshData = YAML::Load(meshStrStream.str());
		//Load Mat
		if (meshData["MaterialID"])
		{
			unsigned int matID = meshData["MaterialID"].as<unsigned int>();
			mesh->SetMaterial(std::move(DeSerializeMaterial(matID, idFilePaths)));
		}
		//Load model
		if (meshData["ModelID"])
		{
			unsigned int modelID = meshData["ModelID"].as<unsigned int>();
			mesh->ImportModelFromTxtFile(idFilePaths[1234567890].as<std::string>());
		}
	}
	else
		std::cout << "Mesh id not found in file paths" << std::endl;

	return mesh;
}

std::unique_ptr<Material> SceneSerializer::DeSerializeMaterial(unsigned int matID, YAML::Node idFilePaths)
{
	std::ifstream matStream(idFilePaths[matID].as<std::string>());
	std::stringstream matStrStream;
	matStrStream << matStream.rdbuf();
	YAML::Node matData = YAML::Load(matStrStream.str());
	//Load Shader
	if (matData["ShaderFilePath"])
	{
		std::unique_ptr<Shader> shader(new Shader(matData["ShaderFilePath"].as<std::string>()));
		shader->Bind();
		if (matData["ShaderColor"])
		{
			float r = matData["ShaderColor"]["r"].as<float>();
			float g = matData["ShaderColor"]["g"].as<float>();
			float b = matData["ShaderColor"]["b"].as<float>();
			float a = matData["ShaderColor"]["a"].as<float>();
			shader->SetUniform4f("u_Color", r, g, b, a);
		}
		else
			shader->SetUniform4f("u_Color", 1, 1, 1, 1);
		//Load Texture
		if (matData["TextureFilePath"])
		{
			std::unique_ptr<Texture> texture(new Texture(matData["TextureFilePath"].as<std::string>()));
			int slot = 0;
			texture->Bind(slot);
			shader->SetUniform1i("u_Texture", slot);
			std::unique_ptr<Material> material(new Material(std::move(shader), std::move(texture), matID));
			return material;
		}
		else
		{
			std::unique_ptr<Material> material(new Material(std::move(shader), matID));
			return material;
		}
	}
	return nullptr;
}
