#include "mge/core/GameObject.hpp"
#include "mge/core/Enemy.hpp"

Enemy::Enemy(std::string pName, glm::vec3 pPosition, Waypoint::Lane pLane)
	: GameObject(pName, pPosition), _lane(pLane)
{
	this->addBehaviour(new WaypointFollowBehaviour(pLane));
}

Enemy::~Enemy()
{
}

void Enemy::update(float pStep)
{
}
