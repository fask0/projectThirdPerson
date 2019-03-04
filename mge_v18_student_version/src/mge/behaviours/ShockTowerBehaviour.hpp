#ifndef SHOCKTOWERBEHAVIOUR_HPP
#define SHOCKTOWERBEHAVIOUR_HPP

#include "mge/behaviours/TowerBehaviour.hpp"
#include "mge/core/HoneyProjectile.hpp"
#include "mge/core/Enemy.hpp"
#include <time.h>

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class ShockTowerBehaviour : public TowerBehaviour
{
public:
	ShockTowerBehaviour();
	virtual ~ShockTowerBehaviour();
	virtual void update(float pStep);

private:
	//Methods
	void CheckForEnemies();
	void Attack();
	//Variables
	bool _enemiesInRange;
	Enemy* _furthestEnemy;
	HoneyProjectile* _projectile;
	clock_t _lastAttackTime;

	std::vector<Enemy*> _allInRangeEnemies;
};

#endif // ROTATINGBEHAVIOUR_HPP
