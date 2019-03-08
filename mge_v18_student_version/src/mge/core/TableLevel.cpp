#include <iostream>
#include <vector>

#include "mge/core/TableLevel.hpp"

#include "glm.hpp"

TableLevel::TableLevel(std::string pName, glm::vec3 pPosition, int pLayers)
	: Level(pName, pPosition, pLayers)
{
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
