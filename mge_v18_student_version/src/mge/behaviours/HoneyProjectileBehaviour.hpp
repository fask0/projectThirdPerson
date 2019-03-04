#ifndef HONEYPROJECTILEBEHAVIOUR_HPP
#define HONEYPROJECTILEBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm.hpp"

class HoneyProjectileBehaviour : public AbstractBehaviour
{
public:
	HoneyProjectileBehaviour(float pDiffBetweenTowerAndTarget);
	virtual ~HoneyProjectileBehaviour();

	virtual void update(float pStep);
private:
	glm::vec3 _velocity;
	float _gravityStrength;
	bool _reachedDestination = false;
};

#endif // ROTATINGBEHAVIOUR_HPP
