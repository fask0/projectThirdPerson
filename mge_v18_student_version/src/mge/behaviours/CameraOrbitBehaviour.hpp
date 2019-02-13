#ifndef CAMERAORBITBEHAVIOUR_HPP
#define CAMERAORBITBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/GameObject.hpp"

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class CameraOrbitBehaviour : public AbstractBehaviour
{
	public:
	CameraOrbitBehaviour(GameObject * target, float distance, float maxTiltAngle, float rotationSpeed);
	virtual ~CameraOrbitBehaviour();

	virtual void update(float pstep);


	private:
	glm::mat4 _target;
	float _distance;
	float _maxTiltAngle;
	float _rotationSpeed;

	float _yRotation = 0.0f;
	float _xRotation = 0.0f;
};

#endif // ROTATINGBEHAVIOUR_HPP
