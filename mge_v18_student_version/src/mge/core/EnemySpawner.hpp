#pragma once
#include <iostream>
#include <time.h>
#include "glm.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/core/Waypoint.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include "mge/behaviours/NextWaveButtonBehaviour.hpp"

class EnemySpawner : public GameObject
{
public:
	EnemySpawner(
		std::string pName = "Spawner",
		glm::vec3 pPosition = glm::vec3(0, 0, 0),
		Waypoint::Lane pLane = Waypoint::A);
	~EnemySpawner();

	virtual void update(float pStep) override;

	void initializeWave();
	bool _waveHasStarted;
	int _currentWave = 0;

private:
	Waypoint::Lane _lane;
	int _size;
	int _baseSize;
	int _currentEnemiesInLane;
	int _enemyScaling;
	int _enemyGrowth;
	float _delayBetweenEnemies;

	clock_t _lastSpawnTime;
};
