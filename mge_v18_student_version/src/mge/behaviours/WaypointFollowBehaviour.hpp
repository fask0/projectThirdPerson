#pragma once

#include <iostream>
#include <vector>

#include "mge/behaviours/AbstractBehaviour.hpp"

#include "mge/core/Waypoint.hpp"

class WaypointFollowBehaviour : public AbstractBehaviour
{
	public:
	//static std::vector<Waypoint*> waypointsInLevel;

	WaypointFollowBehaviour();
	~WaypointFollowBehaviour();

	void update(float pStep);


	//private:
	//std::vector<Waypoint*> _toDo;
	//std::vector<Waypoint*> _done;
};

