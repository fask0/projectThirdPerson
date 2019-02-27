#include <iostream>
#include <vector>

#include "mge/core/Rat.hpp"
#include "mge/core/Enemy.hpp"

Rat::Rat(std::string pName, glm::vec3 pPosition, Waypoint::Lane pLane, std::string pTag)
	: Enemy(pName, pPosition, pLane, pTag)
{
}

Rat::~Rat()
{
}

void Rat::update(float pStep)
{
	Enemy::update(pStep);
	_speedUpDuration -= pStep;
	_slowDownDuration -= pStep;

	if (_speedUpDuration <= 0)
		_speedUp = 0;
	if (_slowDownDuration <= 0)
		_slowDown = 0;
}

void Rat::OnCollisionEnter(GameObject * pOther)
{
	Enemy::OnCollisionEnter(pOther);
}
