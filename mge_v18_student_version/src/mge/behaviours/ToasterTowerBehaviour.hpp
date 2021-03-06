#ifndef TOASTERTOWERBEHAVIOUR_HPP
#define TOASTERTOWERBEHAVIOUR_HPP

#include "mge/behaviours/TowerBehaviour.hpp"
#include "mge/core/ToasterProjectile.hpp"
#include "mge/core/Enemy.hpp"
#include <time.h>

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class ToasterTowerBehaviour : public TowerBehaviour
{
public:
	ToasterTowerBehaviour();
	virtual ~ToasterTowerBehaviour();
	virtual void update(float pStep);

private:
	//Methods
	void CheckForEnemies();
	void Rotate();
	void Attack();
	//Variables
	bool _enemiesInRange;
	Enemy* _furthestEnemy;
	bool _isProjectileCreated;
	ToasterProjectile* _projectile;
	clock_t _lastAttackTime;
};

#endif // ROTATINGBEHAVIOUR_HPP
