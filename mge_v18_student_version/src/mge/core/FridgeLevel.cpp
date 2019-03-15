#include <iostream>
#include <vector>

#include "mge/core/FridgeLevel.hpp"
#include "mge/core/GameController.hpp"

#include "glm.hpp"

FridgeLevel::FridgeLevel(std::string pName, glm::vec3 pPosition, int pLayers)
	: Level(pName, pPosition, pLayers)
{
	_minX = -25;
	_maxX = 25;
	_minZ = -24;
	_maxZ = 22;
}

FridgeLevel::~FridgeLevel()
{
	Level::~Level();
}

void FridgeLevel::update(float pStep)
{
	Level::update(pStep);
}

void FridgeLevel::Init()
{
	Level::Init();
	GameController::Lights[0]->setLocalPosition(glm::vec3(0, 40, -5));
	GameController::Lights[0]->_color = glm::vec3(0.9f, 0.85f, 1.0f);
	GameController::MainCamera->removeAllBehaviours();
	GameController::MainCamera->addBehaviour(new CameraMovementBehaviour(-30, 30, -25, 20, 10, 35, GameController::Window, GameController::MainCamera->getLocalPosition(), 1.0f, 20.0f));
}
