#include "MyDemo.hpp"
#include <iostream>
#include <string>

#include "glm.hpp"

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/WobbleMaterial.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "mge/materials/TerrainMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/WASDBehaviour.hpp"
#include "mge/behaviours/CameraOrbitBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"

MyDemo::MyDemo() :AbstractGame(), _hud(0)
{
}

void MyDemo::initialize()
{
	//setup the core part
	AbstractGame::initialize();

	//setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void MyDemo::_initializeScene()
{
	//MESHES

	//load a bunch of meshes we will be using throughout this demo
	//each mesh only has to be loaded once, but can be used multiple times:
	//F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
	Mesh* newPlaneMesh = Mesh::load(config::MGE_MODEL_PATH + "plane_8192.obj");
	Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
	Mesh* teapotS = Mesh::load(config::MGE_MODEL_PATH + "teapot_smooth.obj");
	Mesh* cylinderS = Mesh::load(config::MGE_MODEL_PATH + "cylinder_smooth.obj");
	Mesh* sphere1 = Mesh::load(config::MGE_MODEL_PATH + "sphere1.obj");
	Mesh* sphere2 = Mesh::load(config::MGE_MODEL_PATH + "sphere2.obj");
	Mesh* sphere3 = Mesh::load(config::MGE_MODEL_PATH + "sphere3.obj");
	Mesh* sphere4 = Mesh::load(config::MGE_MODEL_PATH + "sphere4.obj");
	Mesh* monkeyHeadS = Mesh::load(config::MGE_MODEL_PATH + "suzanna_smooth.obj");


	//Directional
	Light* light = new Light("light", glm::vec3(0, 10, 0), glm::vec3(1, 1, 1), 10.0f, 30.0f, Light::Directional);

	//SpotLight
	Light* light2 = new Light("light2", glm::vec3(0, 10, 0), glm::vec3(0, 0, 1), 10.0f, 30.0f, Light::Spotlight);
	light->rotate(glm::radians(180.0f), glm::vec3(1, 0, 0));
	light2->rotate(glm::radians(180.0f), glm::vec3(1, 0, 0));

	//Behaviours
	//light2->setBehaviour(new WASDBehaviour());
	light->setBehaviour(new RotatingBehaviour());

	_world->add(light);
	_world->add(light2);

	//MATERIALS

	//create some materials to display the cube, the plane and the light
	AbstractMaterial* lightMaterial = new ColorMaterial(glm::vec3(1, 1, 0));
	AbstractMaterial* stoneMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg"));
	AbstractMaterial* grassMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "land.jpg"));
	AbstractMaterial* blueMaterial = new ColorMaterial(glm::vec3(0, 0, 1));
	LitMaterial* litMaterial1 = new LitMaterial(light, glm::vec3(0.9f, 0.9f, 0.9f));
	litMaterial1->AddLight(light2);
	AbstractMaterial* litMaterial = litMaterial1;
	AbstractMaterial* terrainMaterial = new TerrainMaterial(Texture::load(config::MGE_TEXTURE_PATH + "splatmap.png"),
		Texture::load(config::MGE_TEXTURE_PATH + "diffuse1.jpg"),
		Texture::load(config::MGE_TEXTURE_PATH + "water.jpg"),
		Texture::load(config::MGE_TEXTURE_PATH + "diffuse3.jpg"),
		Texture::load(config::MGE_TEXTURE_PATH + "diffuse4.jpg"),
		Texture::load(config::MGE_TEXTURE_PATH + "heightmap.png"),
		2);
	//SCENE SETUP

	//add camera first (it will be updated last)
	Camera* camera = new Camera("camera", glm::vec3(0, 4, 6));
	camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
	_world->add(camera);
	_world->setMainCamera(camera);

	//add the floor
	GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
	plane->scale(glm::vec3(20, 20, 20));
	plane->setMesh(newPlaneMesh);
	plane->setMaterial(terrainMaterial);
	_world->add(plane);

	camera->addBehaviour(new CameraOrbitBehaviour(plane, 3, 90, 1));
}

void MyDemo::_render()
{
	AbstractGame::_render();

	_updateHud();
}

void MyDemo::_updateHud()
{
	std::string debugInfo = "";
	debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

	_hud->setDebugInfo(debugInfo);
	_hud->draw();
}

MyDemo::~MyDemo()
{
	//dtor
}
