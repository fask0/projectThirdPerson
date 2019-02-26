#ifndef TOASTERTOWERBEHAVIOUR_HPP
#define TOASTERTOWERBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class ToasterTowerBehaviour : public AbstractBehaviour
{
public:
	ToasterTowerBehaviour();
	virtual ~ToasterTowerBehaviour();

	virtual void update(float pStep);

};

#endif // ROTATINGBEHAVIOUR_HPP
