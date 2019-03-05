#include "mge/behaviours/IceProjectileBehaviour.hpp"
#include "mge/core/ToasterProjectile.hpp"
#include "mge/core/GameObject.hpp"

IceProjectileBehaviour::IceProjectileBehaviour() :AbstractBehaviour()
{
}

IceProjectileBehaviour::~IceProjectileBehaviour()
{
	//dtor
}

void IceProjectileBehaviour::update(float pStep)
{
	_owner->translate(glm::vec3(30.0f * pStep, 0, 0));
}
