#ifndef MAGNIFYINGGLASSTOWERBEHAVIOUR_HPP
#define MAGNIFYINGGLASSTOWERBEHAVIOUR_HPP

#include "mge/behaviours/TowerBehaviour.hpp"
#include "mge/core/Enemy.hpp"
#include <time.h>

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class MagnifyingGlassTowerBehaviour : public TowerBehaviour
{
public:
	MagnifyingGlassTowerBehaviour();
	virtual ~MagnifyingGlassTowerBehaviour();
	virtual void update(float pStep);

private:
	//Methods
	void CheckForEnemies();
	void Attack();
	//Variables
	bool _enemiesInRange;
	Enemy* _furthestEnemy;
	clock_t _lastAttackTime;

	std::vector<Enemy*> _allInRangeEnemies;
};

#endif // ROTATINGBEHAVIOUR_HPP
