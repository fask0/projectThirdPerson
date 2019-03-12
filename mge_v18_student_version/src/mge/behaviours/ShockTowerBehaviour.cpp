#include "mge/behaviours/ShockTowerBehaviour.hpp"
#include "mge/behaviours/EffectBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Helper.hpp"
#include "mge/core/ShockTower.hpp"

ShockTowerBehaviour::ShockTowerBehaviour() : TowerBehaviour()
{
	//ctor
	_projectile = nullptr;
	_lastAttackTime = clock();
}

ShockTowerBehaviour::~ShockTowerBehaviour()
{
	//dtor
	_projectile = nullptr;
}
void ShockTowerBehaviour::update(float pStep)
{
	CheckForEnemies();
	Attack();
}

void ShockTowerBehaviour::CheckForEnemies()
{
	_enemiesInRange = false;
	_allInRangeEnemies.clear();

	if (GameController::Enemies.size() == 0) return;
	for each (Enemy* enemy in GameController::Enemies)
	{
		glm::vec3 diff = enemy->getLocalPosition() - _owner->getLocalPosition();
		if ((diff.x * diff.x + diff.y * diff.y + diff.z * diff.z) <=
			GameController::ShockRange * GameController::ShockRange)
		{
			_enemiesInRange = true;
			_furthestEnemy = enemy;
			_allInRangeEnemies.push_back(enemy);
		}
	}

	dynamic_cast<ShockTower*>(_owner)->_enemiesInRange = _enemiesInRange;
}

void ShockTowerBehaviour::Attack()
{
	if (float(clock() - _lastAttackTime) / CLOCKS_PER_SEC >= GameController::ShockAttSpeed)
	{
		if (_enemiesInRange)
		{
			for each (Enemy* enemy in _allInRangeEnemies)
			{
				enemy->TakeDamage(5);
			}
			_lastAttackTime = clock();
		}
	}
}

