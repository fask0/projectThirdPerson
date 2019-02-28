#include "mge/behaviours/ToasterProjectileBehaviour.hpp"
#include "mge/core/GameObject.hpp"

ToasterProjectileBehaviour::ToasterProjectileBehaviour() :AbstractBehaviour()
{
}

ToasterProjectileBehaviour::~ToasterProjectileBehaviour()
{
	//dtor
}

void ToasterProjectileBehaviour::update(float pStep)
{
	_owner->translate(glm::vec3(50.0f * pStep, 0, 0));
}
