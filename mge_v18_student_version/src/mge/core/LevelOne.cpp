#include <iostream>
#include <vector>

#include "mge/core/LevelOne.hpp"
#include "mge/core/GameController.hpp"

#include "glm.hpp"

LevelOne::LevelOne(std::string pName, glm::vec3 pPosition, int pLayers)
	: Level(pName, pPosition, pLayers)
{
	_minX = -25;
	_maxX = 25;
	_minZ = -24;
	_maxZ = 26;
}

LevelOne::~LevelOne()
{
	Level::~Level();
}

void LevelOne::update(float pStep)
{
	Level::update(pStep);
}

void LevelOne::Init()
{
	Level::Init();
	GameController::Lights[0]->setLocalPosition(glm::vec3(0, 40, -19));
	GameController::Lights[0]->_color = glm::vec3(0.9f, 0.85f, 0.8f);
	GameController::MainCamera->removeAllBehaviours();
	GameController::MainCamera->addBehaviour(new CameraMovementBehaviour(-30, 30, -17, 25, 10, 35, GameController::Window, GameController::MainCamera->getLocalPosition(), 1.0f, 20.0f));
}
