#include <iostream>
#include "glm.hpp"

#include "mge/core/Waypoint.hpp"

Waypoint::Waypoint(std::string pName, glm::vec3 pPosition, Waypoint::Lane pLane)
	: GameObject(pName, pPosition), _lane(pLane)
{
	//WaypointFollowBehaviour::waypointsInLevel.push_back(this);
}

Waypoint::~Waypoint()
{
}

void Waypoint::update(float pStep)
{
}
