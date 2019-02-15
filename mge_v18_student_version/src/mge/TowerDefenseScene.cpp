#include "TowerDefenseScene.hpp"
#include <iostream>
#include <string>

#include "glm.hpp"

#include "mge/core/Renderer.hpp"

#include "mge/core/LineSegment.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/CollisionManager.hpp"
#include "mge/core/GridManager.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/WobbleMaterial.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "mge/materials/TerrainMaterial.hpp"
#include "mge/materials/TextureGridMaterial.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/materials/LitTextureGridMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/WASDBehaviour.hpp"
#include "mge/behaviours/CameraOrbitBehaviour.hpp"
#include "mge/behaviours/CollisionBehaviour.hpp"
#include "mge/behaviours/CameraMovementBehaviour.hpp"

#include "mge/util/DebugHud.hpp"
#include "mge/core/GameController.hpp"

#include "mge/config.hpp"
#include "Lua/lua.hpp"

TowerDefenseScene::TowerDefenseScene() :AbstractGame(), _hud(0)
{

}

void TowerDefenseScene::initialize()
{
	initializeLua();

	//setup the core part
	AbstractGame::initialize(WindowWidth, WindowHeight);

	//setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;
}

void TowerDefenseScene::initializeLua()
{
	std::cout << "Initializing Lua" << std::endl;

	//Create state
	lua = luaL_newstate();
	luaL_openlibs(lua);
	luaL_loadfile(lua, (config::MGE_LUA_PATH + "main.lua").c_str());

	std::cout << "Lua State created" << std::endl;

	//Run
	lua_call(lua, 0, 0);

	//Set vars
	lua_getglobal(lua, "Debug");
	Debug = lua_toboolean(lua, -1);
	lua_pop(lua, -1);
	std::cout << "Debug set" << std::endl;

	lua_getglobal(lua, "WindowHeight");
	WindowHeight = lua_tointeger(lua, -1);
	lua_pop(lua, -1);

	lua_getglobal(lua, "WindowWidth");
	WindowWidth = lua_tointeger(lua, -1);
	lua_pop(lua, -1);
	std::cout << "Windowsize set" << std::endl;
}

//build the game _world
void TowerDefenseScene::_initializeScene()
{
	//MESHES

	//load a bunch of meshes we will be using throughout this demo
	//each mesh only has to be loaded once, but can be used multiple times:
	//F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
	//Mesh* newPlaneMesh = Mesh::load(config::MGE_MODEL_PATH + "unityexport2");
	Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane");
	Mesh* teapotS = Mesh::load(config::MGE_MODEL_PATH + "teapot_smooth");
	Mesh* cylinderS = Mesh::load(config::MGE_MODEL_PATH + "cylinder_smooth");
	Mesh* sphere1 = Mesh::load(config::MGE_MODEL_PATH + "sphere1");
	Mesh* sphere2 = Mesh::load(config::MGE_MODEL_PATH + "sphere2");
	Mesh* sphere3 = Mesh::load(config::MGE_MODEL_PATH + "sphere3");
	Mesh* sphere4 = Mesh::load(config::MGE_MODEL_PATH + "sphere4");
	Mesh* monkeyHeadS = Mesh::load(config::MGE_MODEL_PATH + "suzanna_smooth");

	//Directional
	Light* light = new Light("light", glm::vec3(0, 10, 0), glm::vec3(0.9f, 1.0f, 0.8f), 10.0f, 30.0f, Light::Directional);

	//SpotLight
	Light* light2 = new Light("light2", glm::vec3(0, 10, 0), glm::vec3(0, 0, 1), 10.0f, 30.0f, Light::Spotlight);
	light->rotate(glm::radians(-110.0f), glm::vec3(1, 0, 0));
	light->rotate(glm::radians(-45.0f), glm::vec3(0, 1, 0));
	light2->rotate(glm::radians(180.0f), glm::vec3(1, 0, 0));

	light->addBehaviour(new RotatingBehaviour());

	_world->add(light);
	_world->add(light2);

	//SCENE SETUP

	TextureGridMaterial* gridMaterial = new TextureGridMaterial(Texture::load(config::MGE_TEXTURE_PATH + "land.jpg"));
	LitTextureGridMaterial* litTextureGridMaterial = new LitTextureGridMaterial(GameController::Lights[0], Texture::load(config::MGE_TEXTURE_PATH + "land.jpg"));
	AbstractMaterial* blueMaterial = new ColorMaterial(glm::vec4(0, 0, 1, 1));
	LitMaterial* litMaterial1 = new LitMaterial(light, glm::vec3(0.9f, 0.9f, 0.9f));
	litMaterial1->AddLight(light2);
	AbstractMaterial* litMaterial = litMaterial1;
	TerrainMaterial* terrainMaterial = new TerrainMaterial(Texture::load(config::MGE_TEXTURE_PATH + "splatmap.png"),
		Texture::load(config::MGE_TEXTURE_PATH + "diffuse1.jpg"),
		Texture::load(config::MGE_TEXTURE_PATH + "water.jpg"),
		Texture::load(config::MGE_TEXTURE_PATH + "diffuse3.jpg"),
		Texture::load(config::MGE_TEXTURE_PATH + "diffuse4.jpg"),
		Texture::load(config::MGE_TEXTURE_PATH + "heightmap.png"),
		0);
	LitTextureMaterial* litTextureMaterial = new LitTextureMaterial(light, Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg"));



	//add camera first (it will be updated last)
	Camera* camera = new Camera(_window, "camera", glm::vec3(0, 16, 0));
	camera->rotate(glm::radians(-72.78f), glm::vec3(1, 0, 0));
	camera->addBehaviour(new CameraMovementBehaviour(-30, 30, 30, -30, 5, 40, _window, camera->getLocalPosition(), 5.0f, 40.0f));
	_world->add(camera);
	_world->setMainCamera(camera);

	//add the floor
	Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "Scene0/scene001");
	GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
	plane->scale(glm::vec3(5, 5, 5));
	plane->setMesh(planeMesh);
	plane->setMaterial(litTextureGridMaterial);
	_world->add(plane);

	//GameObject* plane2 = new GameObject("plane2", glm::vec3(40, -10, 0));
	//plane2->scale(glm::vec3(10, 10, 10));
	//plane2->setMesh(planeMesh);
	//plane2->setMaterial(litTextureGridMaterial);
	//_world->add(plane2);

	CollisionManager* colManager = new CollisionManager("collisionManager", glm::vec3(0, 0, 0));
	_world->add(colManager);

	//GameObject* colliderA = new GameObject("A", glm::vec3(6, 0, 0));
	//CollisionBehaviour* colA = new CollisionBehaviour(glm::vec3(5, 5, 5));
	//colliderA->addBehaviour(colA);
	//colliderA->addBehaviour(new WASDBehaviour());
	//colA->DrawCollider();
	//_world->add(colliderA);

	GameObject* colliderB = new GameObject("B", glm::vec3(0, 2, 0));
	CollisionBehaviour* colB = new CollisionBehaviour(1);
	colliderB->setBehaviour(colB);
	colB->DrawCollider();
	//colliderB->setMaterial(litTextureMaterial);
	_world->add(colliderB);

	GameController::GridObjects.push_back(plane);
	//GameController::GridObjects.push_back(plane2);
	GridManager* gridManager = new GridManager(GameController::GridObjects, _window, _world);
	_world->add(gridManager);
	SetGridManager(gridManager);

	_plane = plane;
	_camera = camera;
	_mat = litTextureGridMaterial;
}

void TowerDefenseScene::_render()
{
	AbstractGame::_render();

	glm::vec3 normalizedDiff = _camera->rayCastNormalizedDiffVec();

	glm::vec3 cameraToPlane = _plane->getWorldPosition() - _camera->getWorldPosition();
	glm::vec3 parallel = glm::dot(cameraToPlane, normalizedDiff) * normalizedDiff;
	glm::vec3 perpendicular = cameraToPlane - parallel;

	float distance = glm::length(perpendicular);

	float planeCamYDiff = _camera->getWorldPosition().y - _plane->getWorldPosition().y;
	float multiplyValue = planeCamYDiff / normalizedDiff.y;
	glm::vec3 thingy = (normalizedDiff * fabs(multiplyValue));
	glm::vec3 planePos = _camera->getWorldPosition() + thingy;

	_mat->setHighlightArea(planePos);

	_updateHud();
}

void TowerDefenseScene::_updateHud()
{
	std::string debugInfo = "";
	debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

	_hud->setDebugInfo(debugInfo);
	_hud->draw();
}

TowerDefenseScene::~TowerDefenseScene()
{
	//dtor
}
