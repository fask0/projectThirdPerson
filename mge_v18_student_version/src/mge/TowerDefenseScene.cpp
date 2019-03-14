#include "TowerDefenseScene.hpp"

#include "mge/core/CollisionManager.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include "mge/core/GridManager.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/UIManager.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Light.hpp"

#include "mge/behaviours/SwitchSpriteOnHoverBehaviour.hpp"
#include "mge/behaviours/CameraMovementBehaviour.hpp"
#include "mge/behaviours/MenuOnHoverBehaviour.hpp"
#include "mge/behaviours/TowerIconBehaviour.hpp"
#include "mge/behaviours/HealthBarBehaviour.hpp"
#include "mge/behaviours/WASDBehaviour.hpp"

#include "mge/util/DebugHud.hpp"
#include "Lua/lua.hpp"
#include "mge/config.hpp"
#include "glm.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"
#include "mge/materials/AbstractMaterial.hpp"

#include "mge/materials/TextureMaterial.hpp"

#include <iostream>
#include <string>

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
	Mesh* _healthBarMesh = Mesh::load(config::MGE_MODEL_PATH + "teapot_smooth.obj");
	GameController::HealthBarMesh = _healthBarMesh;
	Texture* _healthBarTexture = Texture::load(config::MGE_TEXTURE_PATH + "HealthBarTexture.png");
	GameController::HealthBarMaterial = new TextureMaterial(_healthBarTexture);

	//Initialize menu
	GameController::MenuManager->CreateMenu(MenuManager::Menu::MainMenu);
}

void TowerDefenseScene::initializeLua()
{
	std::cout << "Initializing Lua" << std::endl;

	//Create state
	lua = luaL_newstate();
	luaL_openlibs(lua);
	luaL_loadfile(lua, (config::MGE_LUA_PATH + "main.lua").c_str());

	//Run
	lua_call(lua, 0, 0);

	//Set vars
	GameController::DrawColliders = boolFromLua("DrawColliders");
	GameController::Debug = boolFromLua("Debug");
	GameController::MaxHealth = intFromLua("MaxHealth");
	GameController::CurrentHealth = GameController::MaxHealth;
	WindowHeight = intFromLua("WindowHeight");
	WindowWidth = intFromLua("WindowWidth");
	GameController::WindowWidth = WindowWidth;
	GameController::WindowHeight = WindowHeight;

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

	std::cout << "All Lua variables initialized." << std::endl;
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

void TowerDefenseScene::initializeSingletons()
{
	GameController* gameController = new GameController();
	gameController->Init();
	CollisionManager* colManager = new CollisionManager("collisionManager", glm::vec3(0, 0, 0));
	_world->add(colManager);
	GameController::TowerDefenseScene = this;
	GameController::MenuManager = new MenuManager();
	_world->add(GameController::MenuManager);
	_uiManager = new UIManager(_window);
}

//build the game _world
void TowerDefenseScene::_initializeScene()
{
	//Initialize all the singletons in the scene
	initializeSingletons();

	//add camera first (it will be updated last)
	_camera = new Camera(_window, "camera", glm::vec3(0, 35, 0), glm::perspective(glm::radians(60.0f), float(WindowWidth) / float(WindowHeight), 0.1f, 1000.0f));
	_camera->rotate(glm::radians(-72.78f), glm::vec3(1, 0, 0));
	_camera->addBehaviour(new CameraMovementBehaviour(-30, 30, -17, 17, 10, 35, _window, _camera->getLocalPosition(), 1.0f, 20.0f));
	_world->add(_camera);
	_world->setMainCamera(_camera);

	//add light to the scene
	//0.7f, 0.8f, 1.0f)
	//glm::vec3(0, 40, -19)
	Light* light = new Light("light", glm::vec3(0, 40, -5), glm::vec3(0.9f, 0.85f, 0.8f), 10.0f, 30.0f, Light::Directional);
	_world->add(light);
	light->addBehaviour(new WASDBehaviour());
}

void TowerDefenseScene::inintialize2Dobjects()
{
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
