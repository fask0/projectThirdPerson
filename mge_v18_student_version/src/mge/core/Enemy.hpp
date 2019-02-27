#pragma once

#include <iostream>
#include <vector>
#include "glm.hpp"

#include "mge/behaviours/WaypointFollowBehaviour.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/core/Waypoint.hpp"

class Enemy : public GameObject
{
	public:
	Enemy(
		std::string pName = "Enemy",
		glm::vec3 pPosition = glm::vec3(0, 0, 0),
		Waypoint::Lane pLane = Waypoint::A,
		std::string pTag = "enemy");
	~Enemy();

	virtual void update(float pStep) override;

	virtual void OnCollisionEnter(GameObject* pOther) override;
	virtual void OnCollisionStay(GameObject* pOther) override;
	virtual void OnCollisionExit(GameObject* pOther) override;

	protected:
	Waypoint::Lane _lane;
	WaypointFollowBehaviour* _waypointFollowBehaviour;

	private:
	float _speed;
};