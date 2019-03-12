#include "mge/behaviours/HoneyTowerBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Helper.hpp"
#include "mge/core/HoneyProjectile.hpp"
#include "mge/core/HoneyTower.hpp"

HoneyTowerBehaviour::HoneyTowerBehaviour() : TowerBehaviour()
{
	//ctor
	_projectile = nullptr;
	_lastAttackTime = clock();
}

HoneyTowerBehaviour::~HoneyTowerBehaviour()
{
	//dtor
	_projectile = nullptr;
}
void HoneyTowerBehaviour::update(float pStep)
{
	CheckForEnemies();
	Rotate();
	Attack();
}

void HoneyTowerBehaviour::CheckForEnemies()
{
	_enemiesInRange = false;
	if (GameController::Enemies.size() == 0) return;
	for each (Enemy* enemy in GameController::Enemies)
	{
		glm::vec3 diff = enemy->getLocalPosition() - _owner->getLocalPosition();
		if ((diff.x * diff.x + diff.y * diff.y + diff.z * diff.z) <=
			GameController::HoneyRange * GameController::HoneyRange)
		{
			_enemiesInRange = true;
			_furthestEnemy = enemy;
			return;
		}
	}
}

void HoneyTowerBehaviour::Rotate()
{
	if (_enemiesInRange)
	{
		Helper::LookAt(dynamic_cast<HoneyTower*>(_owner)->getMouse(), _furthestEnemy);
	}
}

void HoneyTowerBehaviour::Attack()
{
	if (float(clock() - _lastAttackTime) / CLOCKS_PER_SEC >= GameController::HoneyAttSpeed)
	{
		if (_enemiesInRange)
		{
			glm::vec3 diff = (_owner->getLocalPosition() - _furthestEnemy->getLocalPosition());
			_projectile = new HoneyProjectile(dynamic_cast<HoneyTower*>(_owner)->getMouse()->getTransform(), glm::sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z));
			GameController::CurrentLevel->add(_projectile);
			dynamic_cast<HoneyTower*>(_owner)->PlayAttackSound();
			_lastAttackTime = clock();
		}
	}
}

