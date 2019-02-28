#ifndef TOASTERPROJECTILEBEHAVIOUR_HPP
#define TOASTERPROJECTILEBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

class ToasterProjectileBehaviour : public AbstractBehaviour
{
public:
	ToasterProjectileBehaviour();
	virtual ~ToasterProjectileBehaviour();

	virtual void update(float pStep);
private:
};

#endif // ROTATINGBEHAVIOUR_HPP
