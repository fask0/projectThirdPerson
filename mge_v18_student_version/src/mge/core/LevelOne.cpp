#include <iostream>
#include <vector>

#include "mge/core/LevelOne.hpp"

#include "glm.hpp"

LevelOne::LevelOne(std::string pName, glm::vec3 pPosition, int pLayers)
	: Level(pName, pPosition, pLayers)
{
	_minX = -25;
	_maxX = 25;
	_minZ = -25;
	_maxZ = 25;
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
}
