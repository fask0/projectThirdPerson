#include <iostream>
#include <vector>

#include "mge/core/CupboardLevel.hpp"

#include "glm.hpp"

CupboardLevel::CupboardLevel(std::string pName, glm::vec3 pPosition, int pLayers)
	: Level(pName, pPosition, pLayers)
{
	_minX = -25;
	_maxX = 25;
	_minZ = -25;
	_maxZ = 25;
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
}
