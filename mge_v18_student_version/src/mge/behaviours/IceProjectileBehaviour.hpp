#ifndef ICEPROJECTILEBEHAVIOUR_HPP
#define ICEPROJECTILEBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

class IceProjectileBehaviour : public AbstractBehaviour
{
public:
	IceProjectileBehaviour();
	virtual ~IceProjectileBehaviour();

	virtual void update(float pStep);
private:
};

#endif // ROTATINGBEHAVIOUR_HPP
