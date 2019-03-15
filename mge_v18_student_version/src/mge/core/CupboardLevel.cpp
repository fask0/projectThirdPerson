#include <iostream>
#include <vector>

#include "mge/core/CupboardLevel.hpp"
#include "mge/core/GameController.hpp"

#include "glm.hpp"

CupboardLevel::CupboardLevel(std::string pName, glm::vec3 pPosition, int pLayers)
	: Level(pName, pPosition, pLayers)
{
	_minX = -28;
	_maxX = 26;
	_minZ = -35;
	_maxZ = 44;
}

CupboardLevel::~CupboardLevel()
{
	Level::~Level();
}

void CupboardLevel::update(float pStep)
{
	Level::update(pStep);
}

void CupboardLevel::Init()
{
	Level::Init();
	GameController::Lights[0]->setLocalPosition(glm::vec3(0, 60, -19));
	GameController::Lights[0]->_color = glm::vec3(0.9f, 0.85f, 0.8f);
	GameController::MainCamera->removeAllBehaviours();
	GameController::MainCamera->addBehaviour(new CameraMovementBehaviour(-30, 30, -30, 40, 10, 35, GameController::Window, GameController::MainCamera->getLocalPosition(), 1.0f, 20.0f));
}
