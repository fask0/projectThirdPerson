#include <iostream>
#include <vector>
#include <time.h>
#include "glm.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/core/EnemySpawner.hpp"
#include "mge/core/Enemy.hpp"
#include "mge/core/World.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/Waypoint.hpp"
#include "mge/core/Rat.hpp"

#include "mge/behaviours/CollisionBehaviour.hpp"

EnemySpawner::EnemySpawner(std::string pName, glm::vec3 pPosition, Waypoint::Lane pLane)
	: GameObject(pName, pPosition), _lane(pLane)
{
	_currentWave = 0;
	_currentEnemiesInLane = 0;
	_waveHasStarted = false;

	switch (pLane)
	{
		case Waypoint::A:
		_baseSize = GameController::LaneOneBaseSize;
		_enemyGrowth = GameController::LaneOneSizeGrowthFrequency;
		_enemyScaling = GameController::LaneOneEnemyScalingPercentage;
		_delayBetweenEnemies = GameController::LaneOneDelayBetweenEnemies;
		break;

		case Waypoint::B:
		_baseSize = GameController::LaneTwoBaseSize;
		_enemyGrowth = GameController::LaneTwoSizeGrowthFrequency;
		_enemyScaling = GameController::LaneTwoEnemyScalingPercentage;
		_delayBetweenEnemies = GameController::LaneTwoDelayBetweenEnemies;
		break;

		case Waypoint::C:
		_baseSize = GameController::LaneThreeBaseSize;
		_enemyGrowth = GameController::LaneThreeSizeGrowthFrequency;
		_enemyScaling = GameController::LaneThreeEnemyScalingPercentage;
		_delayBetweenEnemies = GameController::LaneThreeDelayBetweenEnemies;
		break;

		case Waypoint::D:
		_baseSize = GameController::LaneFourBaseSize;
		_enemyGrowth = GameController::LaneFourSizeGrowthFrequency;
		_enemyScaling = GameController::LaneFourEnemyScalingPercentage;
		_delayBetweenEnemies = GameController::LaneFourDelayBetweenEnemies;
		break;
	}

	GameController::SpawnPointsInLevel.push_back(this);
}

EnemySpawner::~EnemySpawner()
{
	for (int i = 0; i < GameController::SpawnPointsInLevel.size(); ++i)
		if (GameController::SpawnPointsInLevel[i] == this)
			GameController::SpawnPointsInLevel.erase(GameController::SpawnPointsInLevel.begin() + i);

	GameObject::~GameObject();
}

void EnemySpawner::update(float pStep)
{
	GameObject::update(pStep);

	if (!_waveHasStarted) return;
	if (_currentEnemiesInLane < _size && clock() >= (_lastSpawnTime + _delayBetweenEnemies * CLOCKS_PER_SEC))
	{
		Enemy* enemy;
		//int selectEnemy = std::rand() % 2 + 1;
		int selectEnemy = 1;
		switch (selectEnemy)
		{
			case 1:
			enemy = new Rat("Rat", getLocalPosition(), _lane);
			std::cout << "spawning Rat number: " << _currentEnemiesInLane << std::endl;
			break;

			case 2:
			//Spawn enemy type 2

			if (_currentEnemiesInLane + enemy->getSize() > _size)
			{
				enemy = new Rat("Rat", getLocalPosition(), _lane);
			}
			break;
		}
		GameController::World->add(enemy);
		_currentEnemiesInLane += enemy->getSize();

		if (_currentEnemiesInLane >= _size)
			_waveHasStarted = false;

		_lastSpawnTime = clock();
	}
}

void EnemySpawner::initializeWave()
{
	if (_waveHasStarted) return;

	if (_currentWave % _enemyGrowth == 0)
		_size = _baseSize * (1 + _enemyScaling * 0.01f * _currentWave);

	_lastSpawnTime = 0;
	_currentEnemiesInLane = 0;

	_currentWave++;
	_waveHasStarted = true;
}