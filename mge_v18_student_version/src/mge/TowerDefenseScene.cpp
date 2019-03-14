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
	GameController::InitialCameraTransform = _camera->getTransform();

	//add light to the scene
	Light* light = new Light("light", glm::vec3(0, 40, -19), glm::vec3(0.9f, 1.0f, 0.8f), 10.0f, 30.0f, Light::Directional);
	_world->add(light);
	light->addBehaviour(new WASDBehaviour());

	//Initialize all the 2D objects in the scene
	//inintialize2Dobjects();
}

void TowerDefenseScene::inintialize2Dobjects()
{
	//Load textures
	//Coin texture
	sf::Texture* coinIcon = new sf::Texture();
	coinIcon->loadFromFile(config::MGE_SPRITES_PATH + "coin.png");
	//Icon textures
	sf::Texture* menuIcon = new sf::Texture();
	menuIcon->loadFromFile(config::MGE_SPRITES_PATH + "menu_button.png");
	sf::Texture* menuIconSel = new sf::Texture();
	menuIconSel->loadFromFile(config::MGE_SPRITES_PATH + "menu_button_sel.png");
	sf::Texture* disgustingIcon = new sf::Texture();
	disgustingIcon->loadFromFile(config::MGE_SPRITES_PATH + "disgustingness.png");
	sf::Texture* toasterIcon = new sf::Texture();
	toasterIcon->loadFromFile(config::MGE_SPRITES_PATH + "toaster_icon_colour0.png");
	sf::Texture* toasterIconSel = new sf::Texture();
	toasterIconSel->loadFromFile(config::MGE_SPRITES_PATH + "toaster_icon_colour_sel0.png");
	sf::Texture* honeyIcon = new sf::Texture();
	honeyIcon->loadFromFile(config::MGE_SPRITES_PATH + "honey_icon_colour.png");
	sf::Texture* honeyIconSel = new sf::Texture();
	honeyIconSel->loadFromFile(config::MGE_SPRITES_PATH + "honey_icon_colour_sel.png");
	sf::Texture* iceIcon = new sf::Texture();
	iceIcon->loadFromFile(config::MGE_SPRITES_PATH + "ice_icon_colour.png");
	sf::Texture* iceIconSel = new sf::Texture();
	iceIconSel->loadFromFile(config::MGE_SPRITES_PATH + "ice_icon_sel.png");
	sf::Texture* batteryIcon = new sf::Texture();
	batteryIcon->loadFromFile(config::MGE_SPRITES_PATH + "battery_icon_colour.png");
	sf::Texture* batteryIconSel = new sf::Texture();
	batteryIconSel->loadFromFile(config::MGE_SPRITES_PATH + "battery_icon_sel.png");
	sf::Texture* magnifyingGlassIcon = new sf::Texture();
	magnifyingGlassIcon->loadFromFile(config::MGE_SPRITES_PATH + "magnifying_glass_colour.png");
	sf::Texture* magnifyingGlassIconSel = new sf::Texture();
	magnifyingGlassIconSel->loadFromFile(config::MGE_SPRITES_PATH + "magnifying_glass_sel.png");
	sf::Texture* sniperIcon = new sf::Texture();
	sniperIcon->loadFromFile(config::MGE_SPRITES_PATH + "peas_icon_colour.png");
	sf::Texture* sniperIconSel = new sf::Texture();
	sniperIconSel->loadFromFile(config::MGE_SPRITES_PATH + "peas_icon_sel.png");
	//Healthbar textures
	std::vector<sf::Texture*> healthBarSprites;
	sf::Texture* healthBarTexture0 = new sf::Texture();
	sf::Texture* healthBarTexture1 = new sf::Texture();
	sf::Texture* healthBarTexture2 = new sf::Texture();
	sf::Texture* healthBarTexture3 = new sf::Texture();
	sf::Texture* healthBarTexture4 = new sf::Texture();
	sf::Texture* healthBarTexture5 = new sf::Texture();
	sf::Texture* healthBarTexture6 = new sf::Texture();
	sf::Texture* healthBarTexture7 = new sf::Texture();
	sf::Texture* healthBarTexture8 = new sf::Texture();
	sf::Texture* healthBarTexture9 = new sf::Texture();
	healthBarTexture0->loadFromFile(config::MGE_SPRITES_PATH + "cheese_bar.png");
	healthBarTexture1->loadFromFile(config::MGE_SPRITES_PATH + "cheese_bar1.png");
	healthBarTexture2->loadFromFile(config::MGE_SPRITES_PATH + "cheese_bar2.png");
	healthBarTexture3->loadFromFile(config::MGE_SPRITES_PATH + "cheese_bar3.png");
	healthBarTexture4->loadFromFile(config::MGE_SPRITES_PATH + "cheese_bar4.png");
	healthBarTexture5->loadFromFile(config::MGE_SPRITES_PATH + "cheese_bar5.png");
	healthBarTexture6->loadFromFile(config::MGE_SPRITES_PATH + "cheese_bar6.png");
	healthBarTexture7->loadFromFile(config::MGE_SPRITES_PATH + "cheese_bar7.png");
	healthBarTexture8->loadFromFile(config::MGE_SPRITES_PATH + "cheese_bar8.png");
	healthBarTexture9->loadFromFile(config::MGE_SPRITES_PATH + "cheese_bar9.png");
	healthBarSprites.push_back(healthBarTexture9);
	healthBarSprites.push_back(healthBarTexture8);
	healthBarSprites.push_back(healthBarTexture7);
	healthBarSprites.push_back(healthBarTexture6);
	healthBarSprites.push_back(healthBarTexture5);
	healthBarSprites.push_back(healthBarTexture4);
	healthBarSprites.push_back(healthBarTexture3);
	healthBarSprites.push_back(healthBarTexture2);
	healthBarSprites.push_back(healthBarTexture1);
	//Description textures
	sf::Texture* toasterDescription = new sf::Texture();
	sf::Texture* honeyDescription = new sf::Texture();
	sf::Texture* iceDescription = new sf::Texture();
	sf::Texture* magnifyingGlassDescription = new sf::Texture();
	sf::Texture* sniperDescription = new sf::Texture();
	sf::Texture* batteryDescription = new sf::Texture();
	toasterDescription->loadFromFile(config::MGE_SPRITES_PATH + "descriptions/toaster_description.png");
	honeyDescription->loadFromFile(config::MGE_SPRITES_PATH + "descriptions/honey_description.png");
	iceDescription->loadFromFile(config::MGE_SPRITES_PATH + "descriptions/ice_description.png");
	magnifyingGlassDescription->loadFromFile(config::MGE_SPRITES_PATH + "descriptions/magnifying_glass_description.png");
	sniperDescription->loadFromFile(config::MGE_SPRITES_PATH + "descriptions/sniper_description.png");
	batteryDescription->loadFromFile(config::MGE_SPRITES_PATH + "descriptions/battery_description.png");

	//------//
	// Coin //
	//------//
	AdvancedSprite* coin = new AdvancedSprite(coinIcon);
	coin->setPosition(WindowWidth - coinIcon->getSize().x - 172, WindowHeight - coinIcon->getSize().y - 80);
	sf::Text* coinsText = new sf::Text();
	sf::Font font = sf::Font();
	font.loadFromFile(config::MGE_SPRITES_PATH + "CREABBB_.TTF");
	coinsText->setFillColor(sf::Color::White);
	coinsText->setPosition(WindowWidth - 164, WindowHeight - coinIcon->getSize().y - 80);
	coinsText->setFont(font);

	//------------//
	// Health Bar //
	//------------//
	AdvancedSprite* healthBar = new AdvancedSprite(healthBarTexture0);
	healthBar->setPosition(WindowWidth - healthBarTexture0->getSize().x - 64, WindowHeight - healthBarTexture0->getSize().y - 96 - coinIcon->getSize().y - 8);
	healthBar->addBehaviour(new HealthBarBehaviour(healthBarSprites));

	//-------------//
	// Tower Icons //
	//-------------//
	std::vector<AdvancedSprite*> menuSprites;
	AdvancedSprite* menuSprite = new AdvancedSprite(menuIcon);
	menuSprite->setPosition(64, WindowHeight - menuIcon->getSize().y - 64);
	menuSprite->addBehaviour(new SwitchSpriteOnHoverBehaviour(menuIconSel));
	AdvancedSprite* toasterSprite = new AdvancedSprite(toasterIcon);
	toasterSprite->setPosition(64 + toasterIcon->getSize().x, WindowHeight - toasterIcon->getSize().y - 64 - ((menuIcon->getSize().y - toasterIcon->getSize().y) / 2));
	toasterSprite->addBehaviour(new SwitchSpriteOnHoverBehaviour(toasterIconSel));
	toasterSprite->addBehaviour(new TowerIconBehaviour(1, toasterDescription));
	menuSprites.push_back(toasterSprite);
	AdvancedSprite* honeySprite = new AdvancedSprite(honeyIcon);
	honeySprite->setPosition(64 + toasterIcon->getSize().x * 2, WindowHeight - toasterIcon->getSize().y - 64 - ((menuIcon->getSize().y - toasterIcon->getSize().y) / 2));
	honeySprite->addBehaviour(new SwitchSpriteOnHoverBehaviour(honeyIconSel));
	honeySprite->addBehaviour(new TowerIconBehaviour(2, honeyDescription));
	menuSprites.push_back(honeySprite);
	AdvancedSprite* iceSprite = new AdvancedSprite(iceIcon);
	iceSprite->setPosition(64 + toasterIcon->getSize().x * 3, WindowHeight - toasterIcon->getSize().y - 64 - ((menuIcon->getSize().y - toasterIcon->getSize().y) / 2));
	iceSprite->addBehaviour(new SwitchSpriteOnHoverBehaviour(iceIconSel));
	iceSprite->addBehaviour(new TowerIconBehaviour(4, iceDescription));
	menuSprites.push_back(iceSprite);
	AdvancedSprite* batterySprite = new AdvancedSprite(batteryIcon);
	batterySprite->setPosition(64 + toasterIcon->getSize().x * 4, WindowHeight - toasterIcon->getSize().y - 64 - ((menuIcon->getSize().y - toasterIcon->getSize().y) / 2));
	batterySprite->addBehaviour(new SwitchSpriteOnHoverBehaviour(batteryIconSel));
	batterySprite->addBehaviour(new TowerIconBehaviour(3, batteryDescription));
	menuSprites.push_back(batterySprite);
	AdvancedSprite* magnifyingGlassSprite = new AdvancedSprite(magnifyingGlassIcon);
	magnifyingGlassSprite->setPosition(64 + toasterIcon->getSize().x * 5, WindowHeight - toasterIcon->getSize().y - 64 - ((menuIcon->getSize().y - toasterIcon->getSize().y) / 2));
	magnifyingGlassSprite->addBehaviour(new SwitchSpriteOnHoverBehaviour(magnifyingGlassIconSel));
	magnifyingGlassSprite->addBehaviour(new TowerIconBehaviour(5, magnifyingGlassDescription));
	menuSprites.push_back(magnifyingGlassSprite);
	AdvancedSprite* sniperSprite = new AdvancedSprite(sniperIcon);
	sniperSprite->setPosition(64 + toasterIcon->getSize().x * 6, WindowHeight - toasterIcon->getSize().y - 64 - ((menuIcon->getSize().y - toasterIcon->getSize().y) / 2));
	sniperSprite->addBehaviour(new SwitchSpriteOnHoverBehaviour(sniperIconSel));
	sniperSprite->addBehaviour(new TowerIconBehaviour(6, sniperDescription));
	menuSprites.push_back(sniperSprite);
	menuSprite->addBehaviour(new MenuOnHoverBehaviour(menuSprites));

	//Add sprites to world and UImanager
	//CoinF
	_world->add(coin);
	_uiManager->AddSprite(coin);
	//Healthbar
	_world->add(healthBar);
	_uiManager->AddSprite(healthBar);
	//Icons
	_world->add(menuSprite);
	_world->add(magnifyingGlassSprite);
	_world->add(sniperSprite);
	_world->add(toasterSprite);
	_world->add(honeySprite);
	_world->add(iceSprite);
	_world->add(batterySprite);
	_uiManager->AddSprite(sniperSprite);
	_uiManager->AddSprite(magnifyingGlassSprite);
	_uiManager->AddSprite(iceSprite);
	_uiManager->AddSprite(batterySprite);
	_uiManager->AddSprite(honeySprite);
	_uiManager->AddSprite(toasterSprite);
	_uiManager->AddSprite(menuSprite);
	//Texts
	_uiManager->AddText(coinsText);
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
