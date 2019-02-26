#ifndef TOASTERTOWERBEHAVIOUR_HPP
#define TOASTERTOWERBEHAVIOUR_HPP

#include "mge/behaviours/TowerBehaviour.hpp"
#include "mge/core/Enemy.hpp"

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
};

#endif // ROTATINGBEHAVIOUR_HPP
