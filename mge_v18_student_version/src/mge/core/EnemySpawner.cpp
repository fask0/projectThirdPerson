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
#include "mge/core/ChadRat.hpp"
#include "mge/core/SanicRat.hpp"
#include "SFML/Graphics.hpp"

#include "mge/behaviours/CollisionBehaviour.hpp"
#include "mge/behaviours/SwitchSpriteOnHoverBehaviour.hpp"

#include "mge/config.hpp"

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

	GameController::SpawnPoints.push_back(this);
}

EnemySpawner::~EnemySpawner()
{
	for (int i = 0; i < GameController::SpawnPoints.size(); ++i)
		if (GameController::SpawnPoints[i] == this)
			GameController::SpawnPoints.erase(GameController::SpawnPoints.begin() + i);
}

void EnemySpawner::update(float pStep)
{
	GameObject::update(pStep);

	if (_currentWave > 14 && GameController::Enemies.size() == 0 && !_waveHasStarted)
	{
		if (!GameController::MenuManager->GetWinScreenBeingDisplayed())
		{
			GameController::MenuManager->CreateMenu(MenuManager::Menu::WinMenu);
			_currentWave = 0;
		}
		return;
	}

	if (!_waveHasStarted) return;
	if (_currentEnemiesInLane < _size && clock() >= (_lastSpawnTime + _delayBetweenEnemies * CLOCKS_PER_SEC))
	{
		spawnEnemy();

		if (_currentEnemiesInLane >= _size)
			_waveHasStarted = false;

		_lastSpawnTime = clock();
	}
}

void EnemySpawner::spawnEnemy()
{
	Enemy* enemy;
	int selectEnemy = std::rand() % 3 + 1;

	switch (selectEnemy)
	{
		case 1:
		if (!_isNormieAvailable)
		{
			spawnEnemy();
			return;
		}
		else
			enemy = new Rat("Rat", getLocalPosition(), _lane);
		break;

		case 2:
		if (!_isSanicAvailable)
		{
			spawnEnemy();
			return;
		}
		else
			enemy = new SanicRat("SanicRat", getLocalPosition(), _lane);
		break;

		case 3:
		if (!_isChadAvailable)
		{
			spawnEnemy();
			return;
		}
		else
			enemy = new ChadRat("ChadRat", getLocalPosition(), _lane);
		break;
	}
	GameController::CurrentLevel->add(enemy);
	_currentEnemiesInLane += enemy->getSize();
}

void EnemySpawner::checkAvailable()
{
	switch (_lane)
	{
		case Waypoint::A:
		_isNormieAvailable = (_currentWave >= GameController::LaneOneNormieFromWave);
		_isSanicAvailable = (_currentWave >= GameController::LaneOneSanicFromWave);
		_isChadAvailable = (_currentWave >= GameController::LaneOneChadFromWave);
		break;

		case Waypoint::B:
		_isNormieAvailable = (_currentWave >= GameController::LaneTwoNormieFromWave);
		_isSanicAvailable = (_currentWave >= GameController::LaneTwoSanicFromWave);
		_isChadAvailable = (_currentWave >= GameController::LaneTwoChadFromWave);
		break;

		case Waypoint::C:
		_isNormieAvailable = (_currentWave >= GameController::LaneTreeNormieFromWave);
		_isSanicAvailable = (_currentWave >= GameController::LaneTreeSanicFromWave);
		_isChadAvailable = (_currentWave >= GameController::LaneTreeChadFromWave);
		break;

		case Waypoint::D:
		_isNormieAvailable = (_currentWave >= GameController::LaneFourNormieFromWave);
		_isSanicAvailable = (_currentWave >= GameController::LaneFourSanicFromWave);
		_isChadAvailable = (_currentWave >= GameController::LaneFourChadFromWave);
		break;
	}
}

void EnemySpawner::initializeWave()
{
	if (_waveHasStarted) return;

	if (_currentWave % _enemyGrowth == 0)
		_size = _baseSize * (1 + _enemyScaling * 0.01f * _currentWave);

	if (GameController::WaveAlarm->GetSound().getStatus() != sf::Sound::Playing)
		GameController::WaveAlarm->Play();

	_lastSpawnTime = 0;
	_currentEnemiesInLane = 0;
	_currentWave++;
	checkAvailable();
	_waveHasStarted = true;
}
