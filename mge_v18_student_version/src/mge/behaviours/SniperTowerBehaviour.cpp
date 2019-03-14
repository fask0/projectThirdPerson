#include "mge/behaviours/SniperTowerBehaviour.hpp"
#include "mge/behaviours/EffectBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Helper.hpp"
#include "mge/core/SniperTower.hpp"

SniperTowerBehaviour::SniperTowerBehaviour() : TowerBehaviour()
{
	//ctor
	_lastAttackTime = clock();
}

SniperTowerBehaviour::~SniperTowerBehaviour()
{
	//dtor
}
void SniperTowerBehaviour::update(float pStep)
{
	CheckForEnemies();
	Rotate();
	Attack();
}

void SniperTowerBehaviour::CheckForEnemies()
{
	_enemiesInRange = false;
	float furthestDistance = 0;

	if (GameController::Enemies.size() == 0) return;
	for each (Enemy* enemy in GameController::Enemies)
	{
		glm::vec3 diff = enemy->getLocalPosition() - _owner->getLocalPosition();
		if ((diff.x * diff.x + diff.y * diff.y + diff.z * diff.z) <=
			GameController::SniperRange * GameController::SniperRange)
		{
			_enemiesInRange = true;
			if (enemy->distanceValue > furthestDistance)
			{
				_furthestEnemy = enemy;
				furthestDistance = enemy->distanceValue;
			}
		}
	}
}

void SniperTowerBehaviour::Rotate()
{
	if (_enemiesInRange)
	{
		Helper::LookAt(_owner, _furthestEnemy);
	}
}

void SniperTowerBehaviour::Attack()
{
	if (float(clock() - _lastAttackTime) / CLOCKS_PER_SEC >= GameController::SniperAttSpeed)
	{
		if (_enemiesInRange)
		{
			_furthestEnemy->TakeDamage(GameController::SniperDamage);
			dynamic_cast<SniperTower*>(_owner)->PlayAttackSound();
			_lastAttackTime = clock();
		}
	}
}

