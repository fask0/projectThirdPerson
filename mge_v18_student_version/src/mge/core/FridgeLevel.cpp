#include <iostream>
#include <vector>

#include "mge/core/FridgeLevel.hpp"

#include "glm.hpp"

FridgeLevel::FridgeLevel(std::string pName, glm::vec3 pPosition, int pLayers)
	: Level(pName, pPosition, pLayers)
{
	_minX = -23;
	_maxX = 23;
	_minZ = -23;
	_maxZ = 23;
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
