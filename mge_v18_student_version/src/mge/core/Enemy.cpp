#include "mge/core/GameObject.hpp"
#include "mge/core/Enemy.hpp"
#include "mge/behaviours/WaypointFollowBehaviour.hpp"
#include "mge/core/Waypoint.hpp"
#include "mge/core/GameController.hpp"

Enemy::Enemy(std::string pName, glm::vec3 pPosition, Waypoint::Lane pLane)
	: GameObject(pName, pPosition), _lane(pLane)
{
	this->addBehaviour(new WaypointFollowBehaviour());
	GameController::Enemies.push_back(this);
}

Enemy::~Enemy()
{
}

void Enemy::update(float pStep)
{
}
