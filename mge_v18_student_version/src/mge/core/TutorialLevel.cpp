#include <iostream>
#include <vector>

#include "mge/core/TutorialLevel.hpp"

#include "glm.hpp"

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
}

void TutorialLevel::Init()
{
	Level::Init();
}
