#include <iostream>
#include <vector>

#include "mge/core/TutorialLevel.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/TutorialHintBehaviour.hpp"

#include "glm.hpp"
#include "mge/config.hpp"
#include "mge/core/World.hpp"

TutorialLevel::TutorialLevel(std::string pName, glm::vec3 pPosition, int pLayers)
	: Level(pName, pPosition, pLayers)
{
	_minX = -25;
	_maxX = 25;
	_minZ = -25;
	_maxZ = 25;
}

TutorialLevel::~TutorialLevel()
{
	Level::~Level();
}

void TutorialLevel::update(float pStep)
{
	Level::update(pStep);
	updateHints();
}

void TutorialLevel::Init()
{
	Level::Init();
	GameController::Lights[0]->setLocalPosition(glm::vec3(0, 40, -19));
	GameController::Lights[0]->_color = glm::vec3(0.9f, 0.85f, 0.8f);
	GameController::MainCamera->removeAllBehaviours();
	GameController::MainCamera->addBehaviour(new CameraMovementBehaviour(-30, 30, -17, 25, 10, 35, GameController::Window, GameController::MainCamera->getLocalPosition(), 1.0f, 20.0f));
	initializeHints();
	_hintHasBeenSpawned = false;
}

void TutorialLevel::initializeHints()
{
	sf::Texture* hintOneTex = new sf::Texture();
	sf::Texture* hintTwoTex = new sf::Texture();
	sf::Texture* hintThreeTex = new sf::Texture();
	sf::Texture* hintFourTex = new sf::Texture();
	sf::Texture* hintFiveTex = new sf::Texture();
	sf::Texture* hintSixTex = new sf::Texture();
	std::vector<sf::Texture*> list;

	hintOneTex->loadFromFile(config::MGE_SPRITES_PATH + "hints/first_line.png");
	hintTwoTex->loadFromFile(config::MGE_SPRITES_PATH + "hints/second_line.png");
	hintThreeTex->loadFromFile(config::MGE_SPRITES_PATH + "hints/third_line.png");
	hintFourTex->loadFromFile(config::MGE_SPRITES_PATH + "hints/forth_line.png");
	hintFiveTex->loadFromFile(config::MGE_SPRITES_PATH + "hints/fifth_line.png");
	hintSixTex->loadFromFile(config::MGE_SPRITES_PATH + "hints/last_line.png");

	_hintOne = new AdvancedSprite(hintOneTex);
	_hintOne->setPosition(GameController::WindowWidth - hintOneTex->getSize().x - 64, GameController::WindowHeight / 4);

	list.push_back(hintTwoTex);
	list.push_back(hintThreeTex);
	list.push_back(hintFourTex);
	list.push_back(hintFiveTex);
	list.push_back(hintSixTex);
	_hintOne->addBehaviour(new TutorialHintBehaviour(list));
}

void TutorialLevel::updateHints()
{
	if (GameController::SpawnPoints.size() < 1)
	{
		_hintHasBeenSpawned = false;
		return;
	}

	if (!GameController::SpawnPoints[0]->_waveHasStarted && GameController::Enemies.size() <= 0 &&
		!_hintHasBeenSpawned)
	{
		if (!GameController::MenuManager->AreAnyScreensEnabled)
		{
			if (GameController::SpawnPoints[0]->_currentWave == 0)
			{
				GameController::UIManager->AddSprite(_hintOne);
				GameController::World->add(_hintOne);
				_hintHasBeenSpawned = true;
			}
		}
	}
	else
	{
		if (GameController::SpawnPoints[0]->_waveHasStarted && GameController::Enemies.size() > 0)
		{
			for (int i = 0; i < GameController::UIManager->_sprites.size(); i++)
			{
				if (GameController::UIManager->_sprites[i] == _hintOne)
				{
					GameController::World->remove(_hintOne);
					GameController::UIManager->_sprites.erase(GameController::UIManager->_sprites.begin() + i);
					i--;
				}
			}
			_hintHasBeenSpawned = false;
		}
	}
}
