#include "mge/behaviours/HoneyProjectileBehaviour.hpp"
#include "mge/core/ToasterProjectile.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/behaviours/CollisionBehaviour.hpp"

HoneyProjectileBehaviour::HoneyProjectileBehaviour(float pDiffBetweenTowerAndTarget) :AbstractBehaviour()
{
	float projectileMovementSpeed = 0.2f;
	float upVelocity = 0.75f;
	float steps = pDiffBetweenTowerAndTarget / (projectileMovementSpeed);

	_gravityStrength = upVelocity / steps;

	_velocity = glm::vec3(projectileMovementSpeed, upVelocity, 0);
}

HoneyProjectileBehaviour::~HoneyProjectileBehaviour()
{
	//dtor
}

void HoneyProjectileBehaviour::update(float pStep)
{
	if (_owner->getLocalPosition().y < 0 && !_reachedDestination)
	{
		_reachedDestination = true;
		_owner->setLocalPosition(glm::vec3(_owner->getLocalPosition().x, 0.0f, _owner->getLocalPosition().z));
		CollisionBehaviour* behaviour = new CollisionBehaviour(CollisionBehaviour::Projectile, 2.0f, true);
		_owner->addBehaviour(behaviour);
		behaviour->DrawCollider();
	}
	if (!_reachedDestination)
	{
		_velocity.y -= _gravityStrength;
		_owner->translate(_velocity);
	}
}
