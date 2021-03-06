#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/Waypoint.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Enemy.hpp"
#include "glm.hpp"
#include <iostream>
#include <vector>

class WaypointFollowBehaviour : public AbstractBehaviour
{
public:
	WaypointFollowBehaviour(Waypoint::Lane pLane);
	virtual ~WaypointFollowBehaviour();
	virtual void update(float pStep);

	void Init();

private:
	glm::vec3 _direction;
	glm::vec3 _velocity;

	std::vector<Waypoint*> _toDo;
	std::vector<Waypoint*> _done;
	Waypoint* _currentWaypoint;
	GameObject* _dummyTransform;
	Enemy* _enemyOwner;

	glm::vec3 getDir();
};