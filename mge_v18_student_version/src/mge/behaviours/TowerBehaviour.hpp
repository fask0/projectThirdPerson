#ifndef TOWERBEHAVIOUR_HPP
#define TOWERBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class TowerBehaviour : public AbstractBehaviour
{
public:
	TowerBehaviour();
	virtual ~TowerBehaviour();

	virtual void update(float pStep);

};

#endif // ROTATINGBEHAVIOUR_HPP
