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
#include "mge/core/Enemy.hpp"
#include "mge/core/Rat.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/WobbleMaterial.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "mge/materials/TerrainMaterial.hpp"
#include "mge/materials/TextureGridMaterial.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/materials/LitTextureGridMaterial.hpp"
#include "mge/materials//LitDynamicGridTextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/WASDBehaviour.hpp"
#include "mge/behaviours/CameraOrbitBehaviour.hpp"
#include "mge/behaviours/CollisionBehaviour.hpp"
#include "mge/behaviours/CameraMovementBehaviour.hpp"
#include "mge/behaviours/WaypointFollowBehaviour.hpp"

#include "mge/util/DebugHud.hpp"
#include "mge/core/GameController.hpp"

#include "mge/config.hpp"
#include "Lua/lua.hpp"

#include "mge/core/EnemySpawner.hpp"
#include "mge/core/ToasterTower.hpp"
#include "mge/core/HoneyTower.hpp"
#include "mge/core/ShockTower.hpp"
#include "mge/core/IceTower.hpp"
#include "mge/core/MagnifyingGlassTower.hpp"
#include "mge/core/SniperTower.hpp"

#include "mge/core/UIManager.hpp"
#include "mge/core/AdvancedSprite.hpp"

TowerDefenseScene::TowerDefenseScene() :AbstractGame(), _hud(0)
{

}

void TowerDefenseScene::initialize()
{
	initializeLua();

	//setup the core part
	AbstractGame::initialize(WindowWidth, WindowHeight);
	GameController::Window = _window;

	//setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;

	GameController::World = _world;
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
	GameController::Debug = Debug;
	lua_pop(lua, -1);
	std::cout << "Debug set" << std::endl;

	lua_getglobal(lua, "DrawColliders");
	GameController::DrawColliders = lua_toboolean(lua, -1);
	lua_pop(lua, -1);

	lua_getglobal(lua, "WindowHeight");
	WindowHeight = lua_tointeger(lua, -1);
	lua_pop(lua, -1);

	lua_getglobal(lua, "WindowWidth");
	WindowWidth = lua_tointeger(lua, -1);
	lua_pop(lua, -1);
	std::cout << "Windowsize set" << std::endl;

	//Level
	//Lane A
	GameController::LaneOneBaseSize = intFromLua("LaneOneBaseSize");
	GameController::LaneOneSizeGrowthFrequency = intFromLua("LaneOneSizeGrowthFrequency");
	GameController::LaneOneEnemyScalingPercentage = intFromLua("LaneOneEnemyScalingPercentage");
	GameController::LaneOneDelayBetweenEnemies = floatFromLua("LaneOneDelayBetweenEnemies");
	//Lane B
	GameController::LaneTwoBaseSize = intFromLua("LaneTwoBaseSize");
	GameController::LaneTwoSizeGrowthFrequency = intFromLua("LaneTwoSizeGrowthFrequency");
	GameController::LaneTwoEnemyScalingPercentage = intFromLua("LaneTwoEnemyScalingPercentage");
	GameController::LaneTwoDelayBetweenEnemies = floatFromLua("LaneTwoDelayBetweenEnemies");
	//Lane C
	GameController::LaneThreeBaseSize = intFromLua("LaneThreeBaseSize");
	GameController::LaneThreeSizeGrowthFrequency = intFromLua("LaneThreeSizeGrowthFrequency");
	GameController::LaneThreeEnemyScalingPercentage = intFromLua("LaneThreeEnemyScalingPercentage");
	GameController::LaneThreeDelayBetweenEnemies = floatFromLua("LaneThreeDelayBetweenEnemies");
	//Lane D
	GameController::LaneFourBaseSize = intFromLua("LaneFourBaseSize");
	GameController::LaneFourSizeGrowthFrequency = intFromLua("LaneFourSizeGrowthFrequency");
	GameController::LaneFourEnemyScalingPercentage = intFromLua("LaneFourEnemyScalingPercentage");
	GameController::LaneFourDelayBetweenEnemies = floatFromLua("LaneFourDelayBetweenEnemies");

	GameController::StartingMoney = intFromLua("StartingMoney");
	//Toaster tower
	GameController::ToasterRange = floatFromLua("ToasterRange");
	GameController::ToasterAttSpeed = floatFromLua("ToasterAttSpeed");
	GameController::ToasterDamage = intFromLua("ToasterDamage");
	GameController::ToasterCost = intFromLua("ToasterCost");
	//Honey tower
	GameController::HoneyRange = floatFromLua("HoneyRange");
	GameController::HoneyAttSpeed = floatFromLua("HoneyAttSpeed");
	GameController::HoneyCost = intFromLua("HoneyCost");
	GameController::HoneySlowAmount = intFromLua("HoneySlowAmount");
	//Shock tower
	GameController::ShockRange = floatFromLua("ShockRange");
	GameController::ShockAttSpeed = floatFromLua("ShockAttSpeed");
	GameController::ShockCost = intFromLua("ShockCost");
	GameController::ShockDamage = floatFromLua("ShockDamage");
	//Ice tower
	GameController::IceRange = floatFromLua("IceRange");
	GameController::IceAttSpeed = floatFromLua("IceAttSpeed");
	GameController::IceFreezeTime = floatFromLua("IceFreezeTime");
	GameController::IceCost = intFromLua("IceCost");
	GameController::IceDamage = intFromLua("IceDamage");
	//Magnifying glass tower
	GameController::MagnifyingRange = floatFromLua("MagnifyingRange");
	GameController::MagnifyingFireDamage = floatFromLua("MagnifyingFireDamage");
	GameController::MagnifyingFireRate = floatFromLua("MagnifyingFireRate");
	GameController::MagnifyingFireDuration = floatFromLua("MagnifyingFireDuration");
	GameController::MagnifyingCost = intFromLua("MagnifyingCost");
	//Sniper tower
	GameController::SniperRange = floatFromLua("SniperRange");
	GameController::SniperAttSpeed = floatFromLua("SniperAttSpeed");
	GameController::SniperCost = intFromLua("SniperCost");
	GameController::SniperDamage = intFromLua("SniperDamage");

	//Rats
	//Rat
	GameController::RatSize = intFromLua("RatSize");
	GameController::RatHealth = intFromLua("RatHealth");
	GameController::RatHealthRegen = intFromLua("RatHealthRegen");
	GameController::RatDamage = intFromLua("RatDamage");
	GameController::RatSpeed = floatFromLua("RatSpeed");
	GameController::RatEffectRecoverySpeed = floatFromLua("RatEffectRecoverySpeed");
	//ChadRat
	GameController::ChadSize = intFromLua("ChadSize");
	GameController::ChadHealth = intFromLua("ChadHealth");
	GameController::ChadHealthRegen = intFromLua("ChadHealthRegen");
	GameController::ChadDamage = intFromLua("ChadDamage");
	GameController::ChadSpeed = floatFromLua("ChadSpeed");
	GameController::ChadEffectRecoverySpeed = floatFromLua("ChadEffectRecoverySpeed");
	//SanicRat
	GameController::SanicSize = intFromLua("SanicSize");
	GameController::SanicHealth = intFromLua("SanicHealth");
	GameController::SanicHealthRegen = intFromLua("SanicHealthRegen");
	GameController::SanicDamage = intFromLua("SanicDamage");
	GameController::SanicSpeed = floatFromLua("SanicSpeed");
	GameController::SanicEffectRecoverySpeed = floatFromLua("SanicEffectRecoverySpeed");
}

int TowerDefenseScene::intFromLua(std::string pVariableName)
{
	int i;
	lua_getglobal(lua, pVariableName.c_str());
	i = lua_tointeger(lua, -1);
	lua_pop(lua, -1);
	return i;
}

float TowerDefenseScene::floatFromLua(std::string pVariableName)
{
	float f;
	lua_getglobal(lua, pVariableName.c_str());
	f = lua_tonumber(lua, -1);
	lua_pop(lua, -1);
	return f;
}

bool TowerDefenseScene::boolFromLua(std::string pVariableName)
{
	bool b;
	lua_getglobal(lua, pVariableName.c_str());
	b = lua_toboolean(lua, -1);
	lua_pop(lua, -1);
	return b;
}

//build the game _world
void TowerDefenseScene::_initializeScene()
{
	GameController* gameController = new GameController();
	GameController::TowerDefenseScene = this;
	//CollisionManager* colManager = new CollisionManager("collisionManager", glm::vec3(0, 0, 0));
	//_world->add(colManager);

	//UI
	std::cout << "Initializing 2D layer" << std::endl;
	_uiManager = new UIManager(_window);
	std::cout << "2D layer initialized." << std::endl;

	glm::vec3 cameraPosition = glm::vec3(0, 16, 0);
	glm::vec3 lightPosition = glm::vec3(0, 25, -19);
	//Directional
	//glm::vec3(-2.0f, 4.0f, -1.0f)
	//-17.0f, 6.0f, -17.0f
	Light* light = new Light("light", lightPosition, glm::vec3(0.9f, 1.0f, 0.8f), 10.0f, 30.0f, Light::Directional);
	light->rotate(glm::radians(-72.78f), glm::vec3(1, 0, 0));
	//light->rotate(45, glm::vec3(1, 0, 0));
	//light->rotate(45, glm::vec3(0, 1, 0));
	_world->add(light);
	light->addBehaviour(new WASDBehaviour());
	gameController->Init();

	//SCENE SETUP
	//add camera first (it will be updated last)
	Camera* camera = new Camera(_window, "camera", glm::vec3(0, 16, 0), glm::perspective(glm::radians(60.0f), float(WindowWidth) / float(WindowHeight), 0.1f, 1000.0f));
	camera->rotate(glm::radians(-72.78f), glm::vec3(1, 0, 0));
	camera->addBehaviour(new CameraMovementBehaviour(-30, 30, -17, 17, 1, 50, _window, camera->getLocalPosition(), 1.0f, 10.0f));
	//camera->setTransform(glm::lookAt(camera->getLocalPosition(), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
	_world->add(camera);
	_world->setMainCamera(camera);

	_camera = camera;

	sf::Texture* tex = new sf::Texture();
	tex->loadFromFile(config::MGE_TEXTURE_PATH + "bricks.jpg");

	AdvancedSprite* sprite = new AdvancedSprite();
	sprite->setPosition(0, 64);
	sprite->addBehaviour(new WASDBehaviour());
	_world->add(sprite);
	_uiManager->AddSprite(sprite, tex);
}

void TowerDefenseScene::_render()
{
	AbstractGame::_render();

	if (GameController::MainPlane != NULL)
	{
		glm::vec3 normalizedDiff = _camera->rayCastNormalizedDiffVec();
		glm::vec3 cameraToPlane = GameController::MainPlane->getWorldPosition() - _camera->getWorldPosition();
		glm::vec3 parallel = glm::dot(cameraToPlane, normalizedDiff) * normalizedDiff;
		glm::vec3 perpendicular = cameraToPlane - parallel;

		float distance = glm::length(perpendicular);

		float planeCamYDiff = _camera->getWorldPosition().y - GameController::MainPlane->getWorldPosition().y;
		float multiplyValue = planeCamYDiff / normalizedDiff.y;
		glm::vec3 thingy = (normalizedDiff * fabs(multiplyValue));
		glm::vec3 planePos = _camera->getWorldPosition() + thingy;

		GameController::MainPlaneMaterial->setHighlightArea(planePos);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		GameController::LoadNextLevel();
	}
	if (GameController::CurrentLevel != NULL && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		for (int i = 0; i < GameController::CurrentLevel->getEnemySpawnPoints().size(); ++i)
			GameController::CurrentLevel->getEnemySpawnPoints()[i]->initializeWave();
	}

	_updateHud();
	updateUIElements();
}

void TowerDefenseScene::_updateHud()
{
	std::string debugInfo = "";
	debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

	_hud->setDebugInfo(debugInfo);
	_hud->draw();
}

void TowerDefenseScene::updateUIElements()
{
	_uiManager->Draw();
}

TowerDefenseScene::~TowerDefenseScene()
{
	//dtor
}
