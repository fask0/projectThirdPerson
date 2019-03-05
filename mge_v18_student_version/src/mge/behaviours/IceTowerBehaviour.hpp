#ifndef ICETOWERBEHAVIOUR_HPP
#define ICETOWERBEHAVIOUR_HPP

#include "mge/behaviours/TowerBehaviour.hpp"
#include "mge/core/Enemy.hpp"
#include "mge/core/IceProjectile.hpp"
#include <time.h>

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class IceTowerBehaviour : public TowerBehaviour
{
public:
	IceTowerBehaviour();
	virtual ~IceTowerBehaviour();
	virtual void update(float pStep);

private:
	//Methods
	void CheckForEnemies();
	void Rotate();
	void Attack();
	//Variables
	bool _enemiesInRange;
	Enemy* _furthestEnemy;
	clock_t _lastAttackTime;
	bool _isProjectileCreated;
	IceProjectile* _projectile;

	std::vector<Enemy*> _allInRangeEnemies;
};

#endif // ROTATINGBEHAVIOUR_HPP
