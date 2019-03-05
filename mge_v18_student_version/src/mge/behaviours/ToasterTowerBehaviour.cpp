#include "mge/behaviours/ToasterTowerBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Helper.hpp"
#include "mge/core/ToasterProjectile.hpp"
#include "mge/core/ToasterTower.hpp"

ToasterTowerBehaviour::ToasterTowerBehaviour() : TowerBehaviour()
{
	//ctor
	_isProjectileCreated = false;
	_projectile = nullptr;
	_lastAttackTime = clock();
}

ToasterTowerBehaviour::~ToasterTowerBehaviour()
{
	//dtor
	_projectile = nullptr;
}
void ToasterTowerBehaviour::update(float pStep)
{
	CheckForEnemies();
	Rotate();
	Attack();
}

void ToasterTowerBehaviour::CheckForEnemies()
{
	_enemiesInRange = false;
	if (GameController::Enemies.size() == 0) return;
	for each (Enemy* enemy in GameController::Enemies)
	{
		glm::vec3 diff = enemy->getLocalPosition() - _owner->getLocalPosition();
		if ((diff.x * diff.x + diff.y * diff.y + diff.z * diff.z) <=
			GameController::ToasterRange * GameController::ToasterRange)
		{
			_enemiesInRange = true;
			_furthestEnemy = enemy;
			return;
		}
	}
}

void ToasterTowerBehaviour::Rotate()
{
	if (_enemiesInRange)
	{
		Helper::LookAt(_owner, _furthestEnemy);
	}
}

void ToasterTowerBehaviour::Attack()
{
	if (float(clock() - _lastAttackTime) / CLOCKS_PER_SEC >= GameController::ToasterAttSpeed)
	{
		if (!_isProjectileCreated)
		{
			_projectile = new ToasterProjectile(_owner->getTransform());
			GameController::World->add(_projectile);
			_isProjectileCreated = true;
			dynamic_cast<ToasterTower*>(_owner)->primedProjectile = _projectile;
		}
		if (_enemiesInRange && _isProjectileCreated)
		{
			Rotate();
			_projectile->Shoot();
			_lastAttackTime = clock();
			_isProjectileCreated = false;
			dynamic_cast<ToasterTower*>(_owner)->primedProjectile = nullptr;
		}
	}
}
