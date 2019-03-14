#include <iostream>
#include <vector>

#include "mge/core/TableLevel.hpp"
#include "mge/core/GameController.hpp"

#include "glm.hpp"

TableLevel::TableLevel(std::string pName, glm::vec3 pPosition, int pLayers)
	: Level(pName, pPosition, pLayers)
{
	_minX = -35;
	_maxX = 35;
	_minZ = -30;
	_maxZ = 30;
}

TableLevel::~TableLevel()
{
	Level::~Level();
}

void TableLevel::update(float pStep)
{
	Level::update(pStep);
}

void TableLevel::Init()
{
	Level::Init();
	GameController::Lights[0]->setLocalPosition(glm::vec3(0, 40, -19));
	GameController::Lights[0]->_color = glm::vec3(0.9f, 0.85f, 0.8f);
	GameController::MainCamera->removeAllBehaviours();
	GameController::MainCamera->addBehaviour(new CameraMovementBehaviour(-30, 30, -30, 30, 10, 35, GameController::Window, GameController::MainCamera->getLocalPosition(), 1.0f, 20.0f));
}
