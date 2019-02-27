#pragma once

#include <iostream>
#include <vector>

#include "mge/core/Enemy.hpp"

class Rat : public Enemy
{
	public:
	Rat(std::string pName = "Rat",
		glm::vec3 pPosition = glm::vec3(0, 0, 0),
		Waypoint::Lane pLane = Waypoint::A,
		std::string pTag = "ratEnemy");
	~Rat();

	virtual void update(float pStep);
	void OnCollisionEnter(GameObject* pOther) override;
};