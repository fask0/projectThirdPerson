#include <iostream>
#include <vector>

#include "mge/core/TableLevel.hpp"

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
}
