#include "mge/core/AdvancedSprite.hpp"
#include "mge/core/MenuManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "mge/core/GameObject.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include "mge/behaviours/SwitchSpriteOnHoverBehaviour.hpp"
#include "mge/behaviours/MenuButtonBehaviour.hpp"
#include "mge/behaviours/MenuOnHoverBehaviour.hpp"
#include "mge/config.hpp"
#include "mge/core/CollisionManager.hpp"

MenuManager::MenuManager() :GameObject("Menu Manager")
{
	init();
}


MenuManager::~MenuManager()
{
}

void MenuManager::ClearMenus()
{
	_mainMenuBeingDisplayed = false;
	_levelSelectMenuBeingDisplayed = false;
	_winMenuBeingDisplayed = false;
	_loseMenuBeingDisplayed = false;
	_loadingScreenBeingDisplayed = false;
	_pauseScreenBeingDisplayed = false;
	for (int i = 0; i < GameController::UIManager->_sprites.size(); i++)
	{
		if (GameController::UIManager->_sprites[i] == _mainMenu ||
			GameController::UIManager->_sprites[i] == _levelSelectMenu ||
			GameController::UIManager->_sprites[i] == _winMenu ||
			GameController::UIManager->_sprites[i] == _loseMenu ||
			GameController::UIManager->_sprites[i] == _loadingScreen ||
			GameController::UIManager->_sprites[i] == _pauseScreen)
		{
			GameController::UIManager->_sprites.erase(GameController::UIManager->_sprites.begin() + i);
		}
	}
	for (int i = 0; i < GameController::World->_children.size(); i++)
	{
		if (dynamic_cast<AdvancedSprite*>(GameController::World->_children[i]))
		{
			GameController::World->remove(GameController::World->_children[i]);
		}
	}
}

void MenuManager::CreateMenu(Menu pMenu)
{
	//Clear menus
	ClearMenus();

	switch (pMenu)
	{
		case MenuManager::MainMenu:
		GameController::UIManager->_sprites.push_back(_mainMenu);
		GameController::World->add(_mainMenu);
		_mainMenuBeingDisplayed = true;
		break;
		case MenuManager::LevelSelectMenu:
		GameController::UIManager->_sprites.push_back(_levelSelectMenu);
		GameController::World->add(_levelSelectMenu);
		_levelSelectMenuBeingDisplayed = true;
		break;
		case MenuManager::WinMenu:
		GameController::UIManager->_sprites.push_back(_winMenu);
		GameController::World->add(_winMenu);
		_winMenuBeingDisplayed = true;
		break;
		case MenuManager::LoseMenu:
		GameController::UIManager->_sprites.push_back(_loseMenu);
		GameController::World->add(_loseMenu);
		_loseMenuBeingDisplayed = true;
		break;
		case MenuManager::LoadingScreen:
		GameController::UIManager->_sprites.push_back(_loadingScreen);
		GameController::World->add(_loadingScreen);
		_loadingScreenBeingDisplayed = true;
		break;
		case MenuManager::PauseScreen:
		GameController::UIManager->_sprites.push_back(_pauseScreen);
		GameController::World->add(_pauseScreen);
		_pauseScreenBeingDisplayed = true;
		break;
	}
}

void MenuManager::init()
{
	initMainMenu();
	initLevelSelectMenu();
	initWinMenu();
	initLoseMenu();
	initLoadingScreen();
	initPauseScreen();
}

void MenuManager::initMainMenu()
{
	//---------------//
	// Load textures //
	//---------------//
	sf::Texture* mainMenuTex = new sf::Texture();
	mainMenuTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/MainMenuBackground.png");
	//Button textures
	sf::Texture* startButtonTex = new sf::Texture();
	startButtonTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/start.png");
	sf::Texture* levelSelectButtonTex = new sf::Texture();
	levelSelectButtonTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/level_select.png");
	sf::Texture* exitButtonTex = new sf::Texture();
	exitButtonTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/exit.png");
	//Selected button textures
	sf::Texture* startButtonSelTex = new sf::Texture();
	startButtonSelTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/start_sel.png");
	sf::Texture* levelSelectButtonSelTex = new sf::Texture();
	levelSelectButtonSelTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/level_select_sel.png");
	sf::Texture* exitButtonSelTex = new sf::Texture();
	exitButtonSelTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/exit_sel.png");

	//----------------//
	// Create Sprites //
	//----------------//
	_mainMenu = new AdvancedSprite(mainMenuTex);
	//Buttons
	AdvancedSprite* startButton = new AdvancedSprite(startButtonTex);
	AdvancedSprite* levelSelectButton = new AdvancedSprite(levelSelectButtonTex);
	AdvancedSprite* exitButton = new AdvancedSprite(exitButtonTex);
	//Add behaviours
	startButton->addBehaviour(new SwitchSpriteOnHoverBehaviour(startButtonSelTex));
	startButton->addBehaviour(new MenuButtonBehaviour(Menu::LoadingScreen, true));
	levelSelectButton->addBehaviour(new SwitchSpriteOnHoverBehaviour(levelSelectButtonSelTex));
	levelSelectButton->addBehaviour(new MenuButtonBehaviour(Menu::LevelSelectMenu));
	exitButton->addBehaviour(new SwitchSpriteOnHoverBehaviour(exitButtonSelTex));
	exitButton->addBehaviour(new MenuButtonBehaviour(Menu::None, false));
	//Set positions
	startButton->setPosition(sf::Vector2f(160, 416));
	levelSelectButton->setPosition(sf::Vector2f(160, 512));
	exitButton->setPosition(sf::Vector2f(160, 608));
	//Add to main menu
	_mainMenu->add(startButton);
	_mainMenu->add(levelSelectButton);
	_mainMenu->add(exitButton);
}

void MenuManager::initLevelSelectMenu()
{
	//---------------//
	// Load textures //
	//---------------//
	sf::Texture* menuTex = new sf::Texture();
	menuTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/LevelSelectScreen.png");
	//Images
	sf::Texture* kitchenTex = new sf::Texture();
	kitchenTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/kitchenRounded.png");
	sf::Texture* fridgeTex = new sf::Texture();
	fridgeTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/FridgeRounded.png");
	sf::Texture* tableTex = new sf::Texture();
	tableTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/DiningTableRounded.png");
	//Button textures
	sf::Texture* backButtonTex = new sf::Texture();
	backButtonTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/back.png");
	sf::Texture* level1ButtonTex = new sf::Texture();
	level1ButtonTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/level1.png");
	sf::Texture* level2ButtonTex = new sf::Texture();
	level2ButtonTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/level2.png");
	sf::Texture* level3ButtonTex = new sf::Texture();
	level3ButtonTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/level3.png");
	sf::Texture* level4ButtonTex = new sf::Texture();
	level4ButtonTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/level4.png");
	sf::Texture* level5ButtonTex = new sf::Texture();
	level5ButtonTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/level5.png");
	sf::Texture* level6ButtonTex = new sf::Texture();
	level6ButtonTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/level6.png");
	//Selected button textures
	sf::Texture* backButtonSelTex = new sf::Texture();
	backButtonSelTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/back_sel.png");
	sf::Texture* level1ButtonSelTex = new sf::Texture();
	level1ButtonSelTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/level1_sel.png");
	sf::Texture* level2ButtonSelTex = new sf::Texture();
	level2ButtonSelTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/level2_sel.png");
	sf::Texture* level3ButtonSelTex = new sf::Texture();
	level3ButtonSelTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/level3_sel.png");
	sf::Texture* level4ButtonSelTex = new sf::Texture();
	level4ButtonSelTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/level4_sel.png");
	sf::Texture* level5ButtonSelTex = new sf::Texture();
	level5ButtonSelTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/level5_sel.png");
	sf::Texture* level6ButtonSelTex = new sf::Texture();
	level6ButtonSelTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/level6_sel.png");

	//----------------//
	// Create Sprites //
	//----------------//
	_levelSelectMenu = new AdvancedSprite(menuTex);
	//Images
	AdvancedSprite* kitchenImage = new AdvancedSprite(kitchenTex);
	AdvancedSprite* fridgeImage = new AdvancedSprite(fridgeTex);
	AdvancedSprite* tableImage = new AdvancedSprite(tableTex);
	//Buttons
	AdvancedSprite* backButton = new AdvancedSprite(backButtonTex);
	AdvancedSprite* level1Button = new AdvancedSprite(level1ButtonTex);
	AdvancedSprite* level2Button = new AdvancedSprite(level2ButtonTex);
	AdvancedSprite* level3Button = new AdvancedSprite(level3ButtonTex);
	AdvancedSprite* level4Button = new AdvancedSprite(level4ButtonTex);
	AdvancedSprite* level5Button = new AdvancedSprite(level5ButtonTex);
	AdvancedSprite* level6Button = new AdvancedSprite(level6ButtonTex);
	//Add behaviours
	backButton->addBehaviour(new SwitchSpriteOnHoverBehaviour(backButtonSelTex));
	backButton->addBehaviour(new MenuButtonBehaviour(Menu::MainMenu));
	level1Button->addBehaviour(new SwitchSpriteOnHoverBehaviour(level1ButtonSelTex));
	level1Button->addBehaviour(new MenuButtonBehaviour(Menu::LoadingScreen, 0));
	//Hover menu -----------------
	level2Button->addBehaviour(new SwitchSpriteOnHoverBehaviour(level2ButtonSelTex));
	level2Button->addBehaviour(new MenuButtonBehaviour(Menu::LoadingScreen, 1));
	level3Button->addBehaviour(new SwitchSpriteOnHoverBehaviour(level3ButtonSelTex));
	level3Button->addBehaviour(new MenuButtonBehaviour(Menu::LoadingScreen, 2));
	level4Button->addBehaviour(new SwitchSpriteOnHoverBehaviour(level4ButtonSelTex));
	level4Button->addBehaviour(new MenuButtonBehaviour(Menu::LoadingScreen, 3));
	level5Button->addBehaviour(new SwitchSpriteOnHoverBehaviour(level5ButtonSelTex));
	level5Button->addBehaviour(new MenuButtonBehaviour(Menu::LoadingScreen, 4));
	level6Button->addBehaviour(new SwitchSpriteOnHoverBehaviour(level6ButtonSelTex));
	level6Button->addBehaviour(new MenuButtonBehaviour(Menu::LoadingScreen, 5));
	//Set positions
	backButton->setPosition(sf::Vector2f(GameController::WindowWidth - 64 - backButtonTex->getSize().x, GameController::WindowHeight - 64 - backButtonTex->getSize().y));
	level1Button->setPosition(sf::Vector2f(550 + 135 - kitchenTex->getSize().x / 2 - level1ButtonTex->getSize().x / 2, 600));
	level2Button->setPosition(sf::Vector2f(550 + 135 - kitchenTex->getSize().x / 2 - level2ButtonTex->getSize().x / 2, 688));
	level3Button->setPosition(sf::Vector2f(550 + 135 - kitchenTex->getSize().x / 2 - level3ButtonTex->getSize().x / 2, 776));
	level4Button->setPosition(sf::Vector2f(550 + 135 - kitchenTex->getSize().x / 2 - level4ButtonTex->getSize().x / 2, 864));
	level5Button->setPosition(sf::Vector2f(1100 + 135 - fridgeTex->getSize().x / 2 - level5ButtonTex->getSize().x / 2, 600));
	level6Button->setPosition(sf::Vector2f(1650 + 135 - tableTex->getSize().x / 2 - level6ButtonTex->getSize().x / 2, 600));
	kitchenImage->setPosition(sf::Vector2f(550 + 135 - kitchenTex->getSize().x, 64));
	fridgeImage->setPosition(sf::Vector2f(1100 + 135 - fridgeTex->getSize().x, 64));
	tableImage->setPosition(sf::Vector2f(1650 + 135 - tableTex->getSize().x, 64));
	//Add to main menu
	_levelSelectMenu->add(backButton);
	_levelSelectMenu->add(level1Button);
	_levelSelectMenu->add(level2Button);
	_levelSelectMenu->add(level3Button);
	_levelSelectMenu->add(level4Button);
	_levelSelectMenu->add(level5Button);
	_levelSelectMenu->add(level6Button);

	_levelSelectMenu->add(kitchenImage);
	_levelSelectMenu->add(fridgeImage);
	_levelSelectMenu->add(tableImage);
}

void MenuManager::initWinMenu()
{
	//Button textures
	sf::Texture* backButtonTex = new sf::Texture();
	backButtonTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/back.png");
	//Selected button textures
	sf::Texture* backButtonSelTex = new sf::Texture();
	backButtonSelTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/back_sel.png");
	//Buttons
	AdvancedSprite* backButton = new AdvancedSprite(backButtonTex);
	//Add behaviours
	backButton->addBehaviour(new SwitchSpriteOnHoverBehaviour(backButtonSelTex));
	backButton->addBehaviour(new MenuButtonBehaviour(Menu::MainMenu));
	//Set positions
	backButton->setPosition(GameController::WindowWidth - 64 - backButtonTex->getSize().x, GameController::WindowHeight - 64 - backButtonTex->getSize().y);

	sf::Texture* winScreenTex = new sf::Texture();
	winScreenTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/Win.png");
	_winMenu = new AdvancedSprite(winScreenTex);

	_winMenu->add(backButton);
}

void MenuManager::initLoseMenu()
{
	//Button textures
	sf::Texture* backButtonTex = new sf::Texture();
	backButtonTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/back.png");
	//Selected button textures
	sf::Texture* backButtonSelTex = new sf::Texture();
	backButtonSelTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/back_sel.png");
	//Buttons
	AdvancedSprite* backButton = new AdvancedSprite(backButtonTex);
	//Add behaviours
	backButton->addBehaviour(new SwitchSpriteOnHoverBehaviour(backButtonSelTex));
	backButton->addBehaviour(new MenuButtonBehaviour(Menu::MainMenu));
	//Set positions
	backButton->setPosition(sf::Vector2f(GameController::WindowWidth - 64 - backButtonTex->getSize().x, GameController::WindowHeight - 64 - backButtonTex->getSize().y));

	sf::Texture* loseScreenTex = new sf::Texture();
	loseScreenTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/Lose.png");
	_loseMenu = new AdvancedSprite(loseScreenTex);

	_loseMenu->add(backButton);
}

void MenuManager::initLoadingScreen()
{
	sf::Texture* loadingScreenTex = new sf::Texture();
	loadingScreenTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/LoadingScreen.png");
	_loadingScreen = new AdvancedSprite(loadingScreenTex);
}

void MenuManager::initPauseScreen()
{
	//---------------//
	// Load textures //
	//---------------//
	sf::Texture* pauseScreenTex = new sf::Texture();
	pauseScreenTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/PauseScreen.png");
	//Button textures
	sf::Texture* backButtonTex = new sf::Texture();
	backButtonTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/back.png");
	sf::Texture* resumeButtonTex = new sf::Texture();
	resumeButtonTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/resume.png");
	//Selected button textures
	sf::Texture* backButtonSelTex = new sf::Texture();
	backButtonSelTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/back_sel.png");
	sf::Texture* resumeButtonSelTex = new sf::Texture();
	resumeButtonSelTex->loadFromFile(config::MGE_SPRITES_PATH + "menus/resume_sel.png");

	//----------------//
	// Create Sprites //
	//----------------//
	_pauseScreen = new AdvancedSprite(pauseScreenTex);
	//Buttons
	AdvancedSprite* backButton = new AdvancedSprite(backButtonTex);
	AdvancedSprite* resumeButton = new AdvancedSprite(resumeButtonTex);
	//Add behaviours
	backButton->addBehaviour(new SwitchSpriteOnHoverBehaviour(backButtonSelTex));
	backButton->addBehaviour(new MenuButtonBehaviour(Menu::MainMenu));
	resumeButton->addBehaviour(new SwitchSpriteOnHoverBehaviour(resumeButtonSelTex));
	resumeButton->addBehaviour(new MenuButtonBehaviour(Menu::CloseAllScreens));
	//Set positions
	backButton->setPosition(sf::Vector2f(GameController::WindowWidth / 2 - backButtonTex->getSize().x / 2, GameController::WindowHeight / 2 + backButtonTex->getSize().y / 2 + 32));
	resumeButton->setPosition(sf::Vector2f(GameController::WindowWidth / 2 - resumeButtonTex->getSize().x / 2, GameController::WindowHeight / 2 - resumeButtonTex->getSize().y / 2 - 32));
	//Add to menu
	_pauseScreen->add(backButton);
	_pauseScreen->add(resumeButton);
}

void MenuManager::update(float pStep)
{
	GameObject::update(pStep);
	if (_loadLevelNextFrame)
	{
		if (_frameCount <= 0)
		{
			if (_levelIndex >= 0)
			{
				GameController::LoadLevel(_levelIndex);
				GameController::MenuManager->ClearMenus();
			}
			else
			{
				GameController::LoadNextLevel();
				GameController::MenuManager->ClearMenus();
			}
			_loadLevelNextFrame = false;
			_frameCount = 2;
		}
		else
			_frameCount--;
	}

	if (GameController::CurrentHealth <= 0 && !_loseMenuBeingDisplayed)
	{
		if (GameController::CurrentLevel != nullptr)
		{
			GameController::CurrentLevel->_children.clear();
			GameController::UIManager->_sprites.clear();
			GameController::Enemies.clear();
			for each (EnemySpawner* spawner in GameController::SpawnPoints)
			{
				spawner->_currentWave = 0;
			}
		}
		GameController::CurrentHealth = GameController::MaxHealth;
		CreateMenu(Menu::LoseMenu);
	}
}

void MenuManager::LoadLevelNextFrame(int pIndex)
{
	_loadLevelNextFrame = true;
	_levelIndex = pIndex;
}

void MenuManager::Inputs(sf::Event pEvent)
{
	if (pEvent.type == sf::Event::KeyPressed)
	{
		if (pEvent.key.code == sf::Keyboard::Key::Escape)
		{
			if (!_mainMenuBeingDisplayed &&
				!_levelSelectMenuBeingDisplayed &&
				!_winMenuBeingDisplayed &&
				!_loseMenuBeingDisplayed &&
				!_loadingScreenBeingDisplayed)
			{
				if (!_pauseScreenBeingDisplayed)
					CreateMenu(Menu::PauseScreen);
				else
					ClearMenus();
			}
		}
	}
}

bool MenuManager::GetWinScreenBeingDisplayed()
{
	return _winMenuBeingDisplayed;
}

