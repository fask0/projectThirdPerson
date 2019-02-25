#pragma once

#include <iostream>
#include <vector>

#include "mge/behaviours/WaypointFollowBehaviour.hpp"

#include "mge/core/GameObject.hpp"

class Waypoint : public GameObject
{
	public:
	enum Lane
	{
		A,
		B,
		C,
		D
	};

	Waypoint(std::string pName = "Waypoint", glm::vec3 pPosition = glm::vec3(0, 0, 0), Lane pLane = A, int pIndex = 0);
	~Waypoint();

	void update(float pStep);

	Lane getLane();

	private:
	Lane _lane;
};
