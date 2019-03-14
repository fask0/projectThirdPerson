#include <iostream>
#include <vector>

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"

#include "mge/core/Level.hpp"
#include "mge/core/EnemySpawner.hpp"
#include "mge/core/Waypoint.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/CollisionManager.hpp"
#include "mge/core/GridManager.hpp"

#include "mge/behaviours/HealthBarBehaviour.hpp"
#include "mge/behaviours/MenuOnHoverBehaviour.hpp"
#include "mge/behaviours/SwitchSpriteOnHoverBehaviour.hpp"
#include "mge/behaviours/TowerIconBehaviour.hpp"
#include "Lua/lua.hpp"

#include "glm.hpp"
#include "mge/config.hpp"

Level::Level(std::string pName, glm::vec3 pPosition, int pLayers)
	: GameObject(pName, pPosition), _layerAmount(pLayers)
{
	GameController::Levels.push_back(this);
	_lowMusicVolume = GameController::MaxMusicVolume * 0.25f;
	_currentMusicVolume = GameController::MaxMusicVolume;
}

Level::~Level()
{
}

void Level::update(float pStep)
{
	GameObject::update(pStep);
	if (GameController::Enemies.size() > 0)
	{
		if (_currentMusicVolume > _lowMusicVolume)
		{
			_currentMusicVolume -= pStep * 20;
			GameController::GameplayMusic->SetVolume(_currentMusicVolume);
		}
	}
	else
	{
		if (_currentMusicVolume < GameController::MaxMusicVolume)
		{
			_currentMusicVolume += pStep * 20;
			GameController::GameplayMusic->SetVolume(_currentMusicVolume);
		}
	}
	updateNextWaveButton();
}

void Level::Init()
{
	_enemySpawnPoints.clear();
	_waypoints.clear();
	_layers.clear();
	GameController::GridObjects.clear();
	GameController::MainCamera->setTransform(GameController::InitialCameraTransform);
	GameController::CameraBehaviour->SetBounds(_minX, _maxX, _minZ, _maxZ);
	initLuaVariables();

	for (int i = 0; i < _layerAmount; ++i)
	{
		GameObject* o = new GameObject("layer" + std::to_string(i), glm::vec3(0, 0, 0));
		_layers.push_back(o);
	}

	for (int i = 0; i < _layers.size(); ++i)
	{
		_layers[i]->setMesh(Mesh::load(config::MGE_MODEL_PATH + "/Levels/" + _name + "/layer" + std::to_string(i)));

		if (i == 0)
		{
			LitDynamicTextureGridMaterial* mat = new LitDynamicTextureGridMaterial(GameController::Lights[0]);
			_layers[i]->setMaterial(mat);
			GameController::GridObjects.push_back(_layers[i]);
			GameController::MainPlane = _layers[i];
			GameController::MainPlaneMaterial = mat;
		}
		else
		{
			LitDynamicTextureGridMaterial* mat = new LitDynamicTextureGridMaterial(GameController::Lights[0], true);
			_layers[i]->setMaterial(mat);
		}

		if (_layers[i]->getMesh()->collidersInMesh.size() > 0)
		{
			for (auto &obj : _layers[i]->getMesh()->collidersInMesh)
			{
				if (dynamic_cast<EnemySpawner*>(obj))
					_enemySpawnPoints.push_back(dynamic_cast<EnemySpawner*>(obj));
				else if (dynamic_cast<Waypoint*>(obj))
					_waypoints.push_back(dynamic_cast<Waypoint*>(obj));

				this->add(obj);
			}
		}

		this->add(_layers[i]);
	}

	GridManager* gridManager = new GridManager(GameController::GridObjects, GameController::Window, this);
	this->add(gridManager);
	GameController::TowerDefenseScene->SetGridManager(gridManager);
	inintialize2Dobjects();
	initializeNextWaveButton();
	if (GameController::MainMenuMusic->GetMusic().getStatus() == sf::Music::Playing)
		GameController::MainMenuMusic->Pause();

	if (GameController::GameplayMusic->GetMusic().getStatus() != sf::Music::Playing)
		GameController::GameplayMusic->Play();
}

void Level::reset()
{
	while (_children.size() > 0)
	{
		GameObject* child = _children[0];
		remove(child);
		delete child;
	}
	_parent->remove(this);
	CollisionManager::projectileCollisions.clear();
	CollisionManager::towerCollisions.clear();
	GameController::UIManager->_sprites.clear();
}

void Level::initLuaVariables()
{
	_lua = luaL_newstate();
	luaL_openlibs(_lua);
	luaL_loadfile(_lua, (config::MGE_LUA_PATH + _name + ".lua").c_str());

	//Run
	lua_call(_lua, 0, 0);

	//Lane A
	GameController::LaneOneNormieFromWave = intFromLua("LaneOneNormieFromWave");
	GameController::LaneOneSanicFromWave = intFromLua("LaneOneSanicFromWave");
	GameController::LaneOneChadFromWave = intFromLua("LaneOneChadFromWave");
	GameController::LaneOneBaseSize = intFromLua("LaneOneBaseSize");
	GameController::LaneOneSizeGrowthFrequency = intFromLua("LaneOneSizeGrowthFrequency");
	GameController::LaneOneEnemyScalingPercentage = intFromLua("LaneOneEnemyScalingPercentage");
	GameController::LaneOneDelayBetweenEnemies = floatFromLua("LaneOneDelayBetweenEnemies");
	//Lane B
	GameController::LaneTwoNormieFromWave = intFromLua("LaneTwoNormieFromWave");
	GameController::LaneTwoSanicFromWave = intFromLua("LaneTwoSanicFromWave");
	GameController::LaneTwoChadFromWave = intFromLua("LaneTwoChadFromWave");
	GameController::LaneTwoBaseSize = intFromLua("LaneTwoBaseSize");
	GameController::LaneTwoSizeGrowthFrequency = intFromLua("LaneTwoSizeGrowthFrequency");
	GameController::LaneTwoEnemyScalingPercentage = intFromLua("LaneTwoEnemyScalingPercentage");
	GameController::LaneTwoDelayBetweenEnemies = floatFromLua("LaneTwoDelayBetweenEnemies");
	//Lane C
	GameController::LaneTreeNormieFromWave = intFromLua("LaneTreeNormieFromWave");
	GameController::LaneTreeSanicFromWave = intFromLua("LaneTreeSanicFromWave");
	GameController::LaneTreeChadFromWave = intFromLua("LaneTreeChadFromWave");
	GameController::LaneThreeBaseSize = intFromLua("LaneThreeBaseSize");
	GameController::LaneThreeSizeGrowthFrequency = intFromLua("LaneThreeSizeGrowthFrequency");
	GameController::LaneThreeEnemyScalingPercentage = intFromLua("LaneThreeEnemyScalingPercentage");
	GameController::LaneThreeDelayBetweenEnemies = floatFromLua("LaneThreeDelayBetweenEnemies");
	//Lane D
	GameController::LaneFourNormieFromWave = intFromLua("LaneFourNormieFromWave");
	GameController::LaneFourSanicFromWave = intFromLua("LaneFourSanicFromWave");
	GameController::LaneFourChadFromWave = intFromLua("LaneFourChadFromWave");
	GameController::LaneFourBaseSize = intFromLua("LaneFourBaseSize");
	GameController::LaneFourSizeGrowthFrequency = intFromLua("LaneFourSizeGrowthFrequency");
	GameController::LaneFourEnemyScalingPercentage = intFromLua("LaneFourEnemyScalingPercentage");
	GameController::LaneFourDelayBetweenEnemies = floatFromLua("LaneFourDelayBetweenEnemies");
	//Misc
	GameController::StartingMoney = intFromLua("StartingMoney");

	lua_close(_lua);
}

int Level::intFromLua(std::string pVariableName)
{
	int i;
	lua_getglobal(_lua, pVariableName.c_str());
	i = lua_tointeger(_lua, -1);
	lua_pop(_lua, -1);
	return i;
}

float Level::floatFromLua(std::string pVariableName)
{
	float f;
	lua_getglobal(_lua, pVariableName.c_str());
	f = lua_tonumber(_lua, -1);
	lua_pop(_lua, -1);
	return f;
}

bool Level::boolFromLua(std::string pVariableName)
{
	bool b;
	lua_getglobal(_lua, pVariableName.c_str());
	b = lua_toboolean(_lua, -1);
	lua_pop(_lua, -1);
	return b;
}

void Level::inintialize2Dobjects()
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
	toasterDescription->loadFromFile(config::MGE_SPRITES_PATH + "descriptions/baked_blades.png");
	honeyDescription->loadFromFile(config::MGE_SPRITES_PATH + "descriptions/honey_hive.png");
	iceDescription->loadFromFile(config::MGE_SPRITES_PATH + "descriptions/cold_clash.png");
	magnifyingGlassDescription->loadFromFile(config::MGE_SPRITES_PATH + "descriptions/blistering_beam.png");
	sniperDescription->loadFromFile(config::MGE_SPRITES_PATH + "descriptions/piercing_peas.png");
	batteryDescription->loadFromFile(config::MGE_SPRITES_PATH + "descriptions/electric_eraser.png");

	//------//
	// Coin //
	//------//
	AdvancedSprite* coin = new AdvancedSprite(coinIcon);
	coin->setPosition(GameController::Window->getSize().x - coinIcon->getSize().x - 172, GameController::Window->getSize().y - coinIcon->getSize().y - 80);
	sf::Text* coinsText = new sf::Text();
	sf::Font font = sf::Font();
	font.loadFromFile(config::MGE_SPRITES_PATH + "CREABBB_.TTF");
	coinsText->setFillColor(sf::Color(48, 52, 55, 255));
	coinsText->setPosition(GameController::Window->getSize().x - 164, GameController::Window->getSize().y - coinIcon->getSize().y - 80);
	coinsText->setFont(font);

	//------//
	// Wabe //
	//------//
	sf::Text* waveText = new sf::Text();
	waveText->setString("0 / 15");
	waveText->setFillColor(sf::Color(48, 52, 55, 255));
	waveText->setFont(font);
	waveText->setCharacterSize(55);
	waveText->setPosition(GameController::Window->getSize().x / 2 - waveText->getGlobalBounds().width / 2, 16);

	//------------//
	// Health Bar //
	//------------//
	AdvancedSprite* healthBar = new AdvancedSprite(healthBarTexture0);
	healthBar->setPosition(GameController::Window->getSize().x - healthBarTexture0->getSize().x - 64, GameController::Window->getSize().y - healthBarTexture0->getSize().y - 96 - coinIcon->getSize().y - 8);
	healthBar->addBehaviour(new HealthBarBehaviour(healthBarSprites));

	//-------------//
	// Tower Icons //
	//-------------//
	std::vector<AdvancedSprite*> menuSprites;
	AdvancedSprite* menuSprite = new AdvancedSprite(menuIcon);
	menuSprite->setPosition(64, GameController::Window->getSize().y - menuIcon->getSize().y - 64);
	menuSprite->addBehaviour(new SwitchSpriteOnHoverBehaviour(menuIconSel));
	AdvancedSprite* toasterSprite = new AdvancedSprite(toasterIcon);
	toasterSprite->setPosition(64 + toasterIcon->getSize().x, GameController::Window->getSize().y - toasterIcon->getSize().y - 64 - ((menuIcon->getSize().y - toasterIcon->getSize().y) / 2));
	toasterSprite->addBehaviour(new SwitchSpriteOnHoverBehaviour(toasterIconSel));
	toasterSprite->addBehaviour(new TowerIconBehaviour(1, toasterDescription));
	menuSprites.push_back(toasterSprite);
	AdvancedSprite* honeySprite = new AdvancedSprite(honeyIcon);
	honeySprite->setPosition(64 + toasterIcon->getSize().x * 2, GameController::Window->getSize().y - toasterIcon->getSize().y - 64 - ((menuIcon->getSize().y - toasterIcon->getSize().y) / 2));
	honeySprite->addBehaviour(new SwitchSpriteOnHoverBehaviour(honeyIconSel));
	honeySprite->addBehaviour(new TowerIconBehaviour(2, honeyDescription));
	menuSprites.push_back(honeySprite);
	AdvancedSprite* iceSprite = new AdvancedSprite(iceIcon);
	iceSprite->setPosition(64 + toasterIcon->getSize().x * 3, GameController::Window->getSize().y - toasterIcon->getSize().y - 64 - ((menuIcon->getSize().y - toasterIcon->getSize().y) / 2));
	iceSprite->addBehaviour(new SwitchSpriteOnHoverBehaviour(iceIconSel));
	iceSprite->addBehaviour(new TowerIconBehaviour(4, iceDescription));
	menuSprites.push_back(iceSprite);
	AdvancedSprite* batterySprite = new AdvancedSprite(batteryIcon);
	batterySprite->setPosition(64 + toasterIcon->getSize().x * 4, GameController::Window->getSize().y - toasterIcon->getSize().y - 64 - ((menuIcon->getSize().y - toasterIcon->getSize().y) / 2));
	batterySprite->addBehaviour(new SwitchSpriteOnHoverBehaviour(batteryIconSel));
	batterySprite->addBehaviour(new TowerIconBehaviour(3, batteryDescription));
	menuSprites.push_back(batterySprite);
	AdvancedSprite* magnifyingGlassSprite = new AdvancedSprite(magnifyingGlassIcon);
	magnifyingGlassSprite->setPosition(64 + toasterIcon->getSize().x * 5, GameController::Window->getSize().y - toasterIcon->getSize().y - 64 - ((menuIcon->getSize().y - toasterIcon->getSize().y) / 2));
	magnifyingGlassSprite->addBehaviour(new SwitchSpriteOnHoverBehaviour(magnifyingGlassIconSel));
	magnifyingGlassSprite->addBehaviour(new TowerIconBehaviour(5, magnifyingGlassDescription));
	menuSprites.push_back(magnifyingGlassSprite);
	AdvancedSprite* sniperSprite = new AdvancedSprite(sniperIcon);
	sniperSprite->setPosition(64 + toasterIcon->getSize().x * 6, GameController::Window->getSize().y - toasterIcon->getSize().y - 64 - ((menuIcon->getSize().y - toasterIcon->getSize().y) / 2));
	sniperSprite->addBehaviour(new SwitchSpriteOnHoverBehaviour(sniperIconSel));
	sniperSprite->addBehaviour(new TowerIconBehaviour(6, sniperDescription));
	menuSprites.push_back(sniperSprite);
	menuSprite->addBehaviour(new MenuOnHoverBehaviour(menuSprites));

	//Add sprites to world and UImanager
	//CoinF

	this->add(coin);
	GameController::UIManager->AddSprite(coin);
	//Healthbar
	this->add(healthBar);
	GameController::UIManager->AddSprite(healthBar);
	//Icons
	this->add(menuSprite);
	this->add(magnifyingGlassSprite);
	this->add(sniperSprite);
	this->add(toasterSprite);
	this->add(honeySprite);
	this->add(iceSprite);
	this->add(batterySprite);
	GameController::UIManager->AddSprite(sniperSprite);
	GameController::UIManager->AddSprite(magnifyingGlassSprite);
	GameController::UIManager->AddSprite(batterySprite);
	GameController::UIManager->AddSprite(iceSprite);
	GameController::UIManager->AddSprite(honeySprite);
	GameController::UIManager->AddSprite(toasterSprite);
	GameController::UIManager->AddSprite(menuSprite);
	//Texts
	GameController::UIManager->AddText(coinsText);
	GameController::UIManager->AddText(waveText);
}

void Level::initializeNextWaveButton()
{
	_nextWaveButtonTex = new sf::Texture();
	_nextWaveButtonTex->loadFromFile(config::MGE_SPRITES_PATH + "next_wave_when_you_can_press_it.png");
	_nextWaveButtonSelTex = new sf::Texture();
	_nextWaveButtonSelTex->loadFromFile(config::MGE_SPRITES_PATH + "next_wave_sel.png");
	_waveInProgressButtonTex = new sf::Texture();
	_waveInProgressButtonTex->loadFromFile(config::MGE_SPRITES_PATH + "next_wave_when_you_cant_press_it.png");

	_nextWaveButton = new AdvancedSprite(_nextWaveButtonTex);
	_nextWaveButton->setPosition(GameController::WindowWidth - 64 - _nextWaveButtonTex->getSize().x, GameController::WindowHeight - _nextWaveButtonTex->getSize().y / 2 - 256);
	_nextWaveButton->addBehaviour(new SwitchSpriteOnHoverBehaviour(_nextWaveButtonSelTex));
	_nextWaveButton->addBehaviour(new NextWaveButtonBehaviour());

	this->add(_nextWaveButton);
	GameController::UIManager->AddSprite(_nextWaveButton);
}

void Level::updateNextWaveButton()
{
	if (GameController::Enemies.size() > 0)
	{
		if (_nextWaveButton->Texture != _waveInProgressButtonTex)
		{
			_nextWaveButton->Texture = _waveInProgressButtonTex;
			_nextWaveButton->removeAllBehaviours();
		}
	}

	else if (GameController::Enemies.size() == 0)
	{
		bool started = false;
		for each (EnemySpawner* spawner in GameController::SpawnPoints)
		{
			if (spawner->_waveHasStarted)
			{
				started = true;
			}
		}

		if (!started)
		{
			if (_nextWaveButton->getBehaviours().size() < 2)
			{
				_nextWaveButton->Texture = _nextWaveButtonTex;
				_nextWaveButton->addBehaviour(new SwitchSpriteOnHoverBehaviour(_nextWaveButtonSelTex));
				_nextWaveButton->addBehaviour(new NextWaveButtonBehaviour());
			}
		}
	}
}
