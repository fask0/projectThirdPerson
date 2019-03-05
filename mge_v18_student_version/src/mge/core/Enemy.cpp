#include <iostream>
#include <vector>
#include <time.h>

#include "mge/behaviours/WaypointFollowBehaviour.hpp"
#include "mge/behaviours/CollisionBehaviour.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/core/Enemy.hpp"
#include "mge/core/Waypoint.hpp"
#include "mge/core/GameController.hpp"

Enemy::Enemy(std::string pName, glm::vec3 pPosition, Waypoint::Lane pLane, std::string pTag)
	: GameObject(pName, pPosition), _lane(pLane)
{
	_tag = pTag;

	WaypointFollowBehaviour* wpBehaviour = new WaypointFollowBehaviour(pLane);
	addBehaviour(wpBehaviour);
	wpBehaviour->Init();

	CollisionBehaviour* colBehaviour = new CollisionBehaviour(0.5f, false, glm::vec3(0, 0.25f, 0));
	addBehaviour(colBehaviour);
	if (GameController::DrawColliders)
		colBehaviour->DrawCollider();

	_ignoreTags.push_back(_tag);
	_ignoreTags.push_back("tower");

	GameController::Enemies.push_back(this);
}

Enemy::~Enemy()
{
	for (int i = 0; i < GameController::Enemies.size(); ++i)
		if (GameController::Enemies[i] == this)
			GameController::Enemies.erase(GameController::Enemies.begin() + i);

	GameObject::~GameObject();
}

void Enemy::update(float pStep)
{
	GameObject::update(pStep);

	if (_speed == _baseSpeed) return;
	if (_speed + pStep * _effectRecovery <= _baseSpeed)
		_speed += pStep * _effectRecovery;
	else if (_speed - pStep * _effectRecovery >= _baseSpeed)
		_speed -= pStep * _effectRecovery;
}

void Enemy::OnCollisionEnter(GameObject * pOther)
{
}

void Enemy::OnCollisionStay(GameObject * pOther)
{
}

void Enemy::OnCollisionExit(GameObject * pOther)
{
}

void Enemy::Knockback(float pForce)
{
	_speed = -pForce * 0.1f;
}

void Enemy::Heal(int pHealth)
{
	_health += pHealth;

	if (_health > _baseHealth)
		_health = _baseHealth;
}

void Enemy::TakeDamage(int pDamage)
{
	_health -= pDamage;

	if (_health > 0) return;
	GameController::GridManager->_currentMoney += KillValue;
	Kill();
}

void Enemy::speedUp(float pSpeedUpPercent)
{
	_speedUp += pSpeedUpPercent;
}

void Enemy::slowDown(float pSlowDownPercent)
{
	_slowDown += pSlowDownPercent;
	if (_slowDown > 100)
		_slowDown = 100;
	if (_slowDown < 0)
		_slowDown = 0;
}

void Enemy::setSlowDown(float pSlowDownPercent)
{
	_slowDown = pSlowDownPercent;
}

float Enemy::getSpeed()
{
	if (_speed > 0)
		return _speed * (1 + (_speedUp * 0.01f - _slowDown * 0.01f));
	else
		return _speed;
}

int Enemy::getSize()
{
	return _size;
}
