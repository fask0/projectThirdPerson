#include "mge/behaviours/ToasterTowerBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/Helper.hpp"

ToasterTowerBehaviour::ToasterTowerBehaviour() : TowerBehaviour()
{
	//ctor
}

ToasterTowerBehaviour::~ToasterTowerBehaviour()
{
	//dtor
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
	if (_enemiesInRange)
	{

	}
}
