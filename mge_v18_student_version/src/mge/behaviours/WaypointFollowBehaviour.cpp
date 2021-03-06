#include "mge/behaviours/WaypointFollowBehaviour.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/Waypoint.hpp"
#include "mge/core/WaypointManager.hpp"
#include "mge/core/Enemy.hpp"
#include "mge/core/Helper.hpp"
#include "mge/core/GameObject.hpp"
#include "glm.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

WaypointFollowBehaviour::WaypointFollowBehaviour(Waypoint::Lane pLane)
	: AbstractBehaviour()
{
	for (int i = 0; i < GameController::CurrentLevel->getWaypoints().size(); ++i)
		if (GameController::CurrentLevel->getWaypoints()[i]->getLane() == pLane)
			_toDo.push_back(GameController::CurrentLevel->getWaypoints()[i]);
	struct
	{
		bool operator()(Waypoint* wp1, Waypoint* wp2)
		{
			return wp1->getIndex() < wp2->getIndex();
		}
	} sortWaypoints;

	std::sort(_toDo.begin(), _toDo.end(), sortWaypoints);
	_currentWaypoint = _toDo[0];
	_dummyTransform = new GameObject("dummy", glm::vec3(0, 0, 0));
}

WaypointFollowBehaviour::~WaypointFollowBehaviour()
{
	_currentWaypoint = nullptr;
	_enemyOwner = nullptr;
	delete _dummyTransform;
	_dummyTransform = nullptr;
}

void WaypointFollowBehaviour::update(float pStep)
{
	if (_toDo.size() == 0)
	{
		GameController::CurrentHealth -= _enemyOwner->getDamage();
		_owner->Kill();
		return;
	}
	_velocity = _direction * _enemyOwner->getSpeed() * pStep;
	glm::vec3 oPos = _enemyOwner->getLocalPosition();
	glm::vec3 distToCurrent = _currentWaypoint->getLocalPosition() - oPos;

	if (_enemyOwner->getSpeed() <= 0 && _done.size() != 0)
	{
		glm::vec3 distToPrev = _done[0]->getLocalPosition() - oPos;

		if (glm::abs(distToPrev.x) <= 0.5f &&
			glm::abs(distToPrev.z) <= 0.5f)
		{
			_velocity *= 0.05f;
		}
	}
	else if (glm::abs(distToCurrent.x) <= _enemyOwner->getSpeed() * pStep * 3 &&
			 glm::abs(distToCurrent.z) <= _enemyOwner->getSpeed() * pStep * 3)
	{
		if (_toDo.size() > 1)
			_currentWaypoint = _toDo[1];
		else
			_currentWaypoint = _toDo[0];
		_direction = getDir();
		_done.insert(_done.begin(), _toDo[0]);
		_toDo.erase(_toDo.begin());
	}

	Helper::Slerp(_enemyOwner, _dummyTransform, _enemyOwner->getSpeed() * 5 * pStep);
	_enemyOwner->setLocalPosition(oPos + _velocity);
}

void WaypointFollowBehaviour::Init()
{
	_enemyOwner = dynamic_cast<Enemy*>(_owner);
	_direction = getDir();
	_dummyTransform->setLocalPosition(_enemyOwner->getLocalPosition());
	Helper::LookAt(_dummyTransform, _currentWaypoint);
	Helper::LookAt(_enemyOwner, _currentWaypoint);
}

glm::vec3 WaypointFollowBehaviour::getDir()
{
	glm::vec3 dir = _currentWaypoint->getLocalPosition() - _enemyOwner->getLocalPosition();
	dir.y = 0;
	_dummyTransform->setLocalPosition(_enemyOwner->getLocalPosition());
	Helper::LookAt(_dummyTransform, _currentWaypoint);
	return glm::normalize(dir);
}
