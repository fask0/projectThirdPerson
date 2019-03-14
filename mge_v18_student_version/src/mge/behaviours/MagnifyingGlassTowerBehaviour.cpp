#include "mge/behaviours/MagnifyingGlassTowerBehaviour.hpp"
#include "mge/behaviours/EffectBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Helper.hpp"
#include "mge/core/MagnifyingGlassTower.hpp"

MagnifyingGlassTowerBehaviour::MagnifyingGlassTowerBehaviour() : TowerBehaviour()
{
	//ctor
	_lastAttackTime = clock();
}

MagnifyingGlassTowerBehaviour::~MagnifyingGlassTowerBehaviour()
{
	//dtor
}
void MagnifyingGlassTowerBehaviour::update(float pStep)
{
	CheckForEnemies();
	Attack();
}

void MagnifyingGlassTowerBehaviour::CheckForEnemies()
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
}

void MagnifyingGlassTowerBehaviour::Attack()
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

