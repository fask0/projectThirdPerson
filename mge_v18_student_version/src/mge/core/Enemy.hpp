#pragma once

#include <iostream>
#include <vector>
#include "glm.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/core/Waypoint.hpp"

class Enemy : public GameObject
{
	public:
	Enemy(std::string pName = "Enemy", glm::vec3 pPosition = glm::vec3(0, 0, 0), Waypoint::Lane pLane = Waypoint::A);
	~Enemy();

	virtual void update(float pStep);

	protected:
	Waypoint::Lane _lane;
};