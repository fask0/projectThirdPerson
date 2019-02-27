#include <iostream>
#include <algorithm>
#include <vector>

#include "mge/behaviours/WaypointFollowBehaviour.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"

#include "mge/core/GameController.hpp"
#include "mge/core/Waypoint.hpp"
#include "mge/core/WaypointManager.hpp"
#include "mge/core/Enemy.hpp"

#include "glm.hpp"

WaypointFollowBehaviour::WaypointFollowBehaviour(Waypoint::Lane pLane)
	: AbstractBehaviour()
{
	for (int i = 0; i < GameController::WaypointsInLevel.size(); ++i)
		if (GameController::WaypointsInLevel[i]->getLane() == pLane)
			_toDo.push_back(GameController::WaypointsInLevel[i]);

	struct
	{
		bool operator()(Waypoint* wp1, Waypoint* wp2)
		{
			return wp1->getIndex() < wp2->getIndex();
		}
	} sortWaypoints;

	std::sort(_toDo.begin(), _toDo.end(), sortWaypoints);
}

WaypointFollowBehaviour::~WaypointFollowBehaviour()
{
}


void WaypointFollowBehaviour::update(float pStep)
{
	_velocity = _direction * _owner->getSpeed() * pStep;
	glm::vec3 oPos = _owner->getLocalPosition();
	_owner->setLocalPosition(oPos + _velocity);
}

void WaypointFollowBehaviour::Init()
{
	_direction = getDir();
}

void WaypointFollowBehaviour::onOwnerCollisionEnter(GameObject * pOther)
{
	if (pOther->GetTag().compare("waypoint"))
	{
		if (getNextWaypoint())
		{

		}
	}
}

void WaypointFollowBehaviour::onOwnerCollisionStay(GameObject * pOther)
{
}

void WaypointFollowBehaviour::onOwnerCollisionExit(GameObject * pOther)
{
	if (pOther->GetTag().compare("waypoint"))
	{

	}
}

glm::vec3 WaypointFollowBehaviour::getDir()
{
	glm::vec3 dir = _toDo[0]->getLocalPosition() - _owner->getLocalPosition();

	return glm::normalize(dir);
}

bool WaypointFollowBehaviour::getNextWaypoint()
{
	for (auto &wp : _toDo)
	{

	}
	return false;
}
