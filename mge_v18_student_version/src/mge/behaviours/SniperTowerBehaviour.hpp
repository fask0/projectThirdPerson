#ifndef SNIPERTOWERBEHAVIOUR_HPP
#define SNIPERTOWERBEHAVIOUR_HPP

#include "mge/behaviours/TowerBehaviour.hpp"
#include "mge/core/Enemy.hpp"
#include <time.h>

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class SniperTowerBehaviour : public TowerBehaviour
{
public:
	SniperTowerBehaviour();
	virtual ~SniperTowerBehaviour();
	virtual void update(float pStep);

private:
	//Methods
	void CheckForEnemies();
	void Rotate();
	void Attack();
	//Variables
	bool _enemiesInRange;
	Enemy* _furthestEnemy = nullptr;
	clock_t _lastAttackTime;
};

#endif // ROTATINGBEHAVIOUR_HPP
