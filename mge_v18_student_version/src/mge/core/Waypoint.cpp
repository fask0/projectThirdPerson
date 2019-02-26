#include <iostream>
#include "glm.hpp"

#include "mge/core/GameController.hpp"
#include "mge/core/Waypoint.hpp"

Waypoint::Waypoint(std::string pName, glm::vec3 pPosition, Waypoint::Lane pLane, int pIndex)
	: GameObject(pName, pPosition), _lane(pLane)
{
	GameController::WaypointsInLevel.push_back(this);
}

Waypoint::~Waypoint()
{
}

void Waypoint::update(float pStep)
{
}

Waypoint::Lane Waypoint::getLane()
{
	return _lane;
}
