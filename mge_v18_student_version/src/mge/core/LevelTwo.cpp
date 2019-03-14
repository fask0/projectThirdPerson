#include <iostream>
#include <vector>

#include "mge/core/LevelTwo.hpp"

#include "glm.hpp"

LevelTwo::LevelTwo(std::string pName, glm::vec3 pPosition, int pLayers)
	: Level(pName, pPosition, pLayers)
{
	_minX = -25;
	_maxX = 25;
	_minZ = -25;
	_maxZ = 25;
}

LevelTwo::~LevelTwo()
{
	Level::~Level();
}

void LevelTwo::update(float pStep)
{
	Level::update(pStep);
}

void LevelTwo::Init()
{
	Level::Init();
}
