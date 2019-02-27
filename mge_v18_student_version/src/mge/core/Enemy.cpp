#include <iostream>
#include <vector>

#include "mge/behaviours/WaypointFollowBehaviour.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/core/Enemy.hpp"
#include "mge/core/Waypoint.hpp"
#include "mge/core/GameController.hpp"

Enemy::Enemy(std::string pName, glm::vec3 pPosition, Waypoint::Lane pLane, std::string pTag)
	: GameObject(pName, pPosition), _lane(pLane)
{
	_tag = pTag;
	speed = 3 * 0.25f;

	_waypointFollowBehaviour = new WaypointFollowBehaviour(pLane);
	addBehaviour(_waypointFollowBehaviour);
	_waypointFollowBehaviour->Init();

	_ignoreTags.push_back(_tag);
	_ignoreTags.push_back("tower");

	GameController::Enemies.push_back(this);
}

Enemy::~Enemy()
{
}

void Enemy::update(float pStep)
{
	GameObject::update(pStep);
}

void Enemy::OnCollisionEnter(GameObject * pOther)
{
	_waypointFollowBehaviour->onOwnerCollisionEnter(pOther);
}

void Enemy::OnCollisionStay(GameObject * pOther)
{
	_waypointFollowBehaviour->onOwnerCollisionStay(pOther);
}

void Enemy::OnCollisionExit(GameObject * pOther)
{
	_waypointFollowBehaviour->onOwnerCollisionExit(pOther);
}