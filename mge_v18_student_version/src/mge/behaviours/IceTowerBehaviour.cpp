#include "mge/behaviours/IceTowerBehaviour.hpp"
#include "mge/behaviours/EffectBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Helper.hpp"
#include "mge/core/IceTower.hpp"

IceTowerBehaviour::IceTowerBehaviour() : TowerBehaviour()
{
	//ctor
	_lastAttackTime = clock();
	_dummyObj = new GameObject("dummyObj", glm::vec3(0, 0, 0));
}

IceTowerBehaviour::~IceTowerBehaviour()
{
	//dtor
}
void IceTowerBehaviour::update(float pStep)
{
	CheckForEnemies();
	Rotate();
	Attack();
}

void IceTowerBehaviour::CheckForEnemies()
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
			_allInRangeEnemies.push_back(enemy);
		}
	}
	if (_enemiesInRange)
	{
		int rand = std::rand() % _allInRangeEnemies.size();
		_furthestEnemy = _allInRangeEnemies[rand];
	}
}

void IceTowerBehaviour::Rotate()
{
	if (_enemiesInRange)
	{
		Helper::LookAt(dynamic_cast<IceTower*>(_owner)->getMouse(), _furthestEnemy);
	}
}

void IceTowerBehaviour::Attack()
{
	if (float(clock() - _lastAttackTime) / CLOCKS_PER_SEC >= GameController::IceAttSpeed)
	{
		if (_enemiesInRange)
		{
			_projectile = new IceProjectile(dynamic_cast<IceTower*>(_owner)->getMouse()->getTransform());
			GameController::CurrentLevel->add(_projectile);
			dynamic_cast<IceTower*>(_owner)->PlayAttackSound();
			_lastAttackTime = clock();
		}
	}
}

