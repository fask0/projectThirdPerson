#ifndef HONEYTOWERBEHAVIOUR_HPP
#define HONEYTOWERBEHAVIOUR_HPP

#include "mge/behaviours/TowerBehaviour.hpp"
#include "mge/core/HoneyProjectile.hpp"
#include "mge/core/Enemy.hpp"
#include <time.h>

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class HoneyTowerBehaviour : public TowerBehaviour
{
public:
	HoneyTowerBehaviour();
	virtual ~HoneyTowerBehaviour();
	virtual void update(float pStep);

private:
	//Methods
	void CheckForEnemies();
	void Rotate();
	void Attack();
	//Variables
	bool _enemiesInRange;
	Enemy* _furthestEnemy;
	HoneyProjectile* _projectile;
	clock_t _lastAttackTime;
};

#endif // ROTATINGBEHAVIOUR_HPP
