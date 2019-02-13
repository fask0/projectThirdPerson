#ifndef WASDBEHAVIOUR_HPP
#define WASDBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class WASDBehaviour : public AbstractBehaviour
{
	public:
	WASDBehaviour();
	virtual ~WASDBehaviour();

	virtual void update(float pstep);

};

#endif // ROTATINGBEHAVIOUR_HPP
