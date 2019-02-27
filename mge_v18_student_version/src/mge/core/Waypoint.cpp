#include <iostream>
#include "glm.hpp"

#include "mge/core/GameController.hpp"
#include "mge/core/Waypoint.hpp"

Waypoint::Waypoint(std::string pName, glm::vec3 pPosition, Waypoint::Lane pLane, int pIndex)
	: GameObject(pName, pPosition), _lane(pLane), _index(pIndex)
{
	_tag = "waypoint";

	_ignoreTags.push_back(_tag);
	_ignoreTags.push_back("tower");

	GameController::WaypointsInLevel.push_back(this);
}

Waypoint::~Waypoint()
{
}

void Waypoint::update(float pStep)
{
}

void Waypoint::OnCollisionEnter(GameObject* pOther)
{
	std::cout << "hello" << std::endl;
}

void Waypoint::OnCollisionExit(GameObject * pOther)
{
	std::cout << "bye" << std::endl;
}

Waypoint::Lane Waypoint::getLane()
{
	return _lane;
}

int Waypoint::getIndex()
{
	return _index;
}