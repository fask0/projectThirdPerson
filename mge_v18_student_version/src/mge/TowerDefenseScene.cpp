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

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/WASDBehaviour.hpp"
#include "mge/behaviours/CameraOrbitBehaviour.hpp"
#include "mge/behaviours/CollisionBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

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

	//SCENE SETUP

	TextureGridMaterial* gridMaterial = new TextureGridMaterial(Texture::load(config::MGE_TEXTURE_PATH + "land.jpg"));
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

	//add camera first (it will be updated last)
	Camera* camera = new Camera(_window, "camera", glm::vec3(0, 16, 20));
	camera->rotate(glm::radians(-35.0f), glm::vec3(1, 0, 0));
	_world->add(camera);
	_world->setMainCamera(camera);

	//add the floor
	GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
	plane->scale(glm::vec3(20, 20, 20));
	plane->setMesh(newPlaneMesh);
	plane->setMaterial(gridMaterial);
	_world->add(plane);

	CollisionManager* colManager = new CollisionManager("collisionManager", glm::vec3(0, 0, 0));
	_world->add(colManager);

	GameObject* colliderA = new GameObject("A", glm::vec3(0, -0.5f, 0));
	CollisionBehaviour* colA = new CollisionBehaviour(glm::vec3(1, 1, 1));
	colliderA->setBehaviour(colA);
	colA->DrawCollider();
	_world->add(colliderA);

	GameObject* colliderB = new GameObject("B", glm::vec3(0, 2, 0));
	CollisionBehaviour* colB = new CollisionBehaviour(1);
	colliderB->setBehaviour(colB);
	colB->DrawCollider();
	_world->add(colliderB);

	std::vector<GameObject*> objs;
	objs.push_back(plane);
	GridManager* gridManager = new GridManager(objs, _window);
	_world->add(gridManager);
	SetGridManager(gridManager);

	_plane = plane;
	_camera = camera;
	_mat = gridMaterial;
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
