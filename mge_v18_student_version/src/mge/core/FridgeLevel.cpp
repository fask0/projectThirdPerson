#include <iostream>
#include <vector>

#include "mge/core/FridgeLevel.hpp"

#include "glm.hpp"

FridgeLevel::FridgeLevel(std::string pName, glm::vec3 pPosition, int pLayers)
	: Level(pName, pPosition, pLayers)
{
	_minX = -25;
	_maxX = 25;
	_minZ = -24;
	_maxZ = 25;
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
}
