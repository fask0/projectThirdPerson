#include "mge/behaviours/TowerBehaviour.hpp"
#include "mge/core/GameObject.hpp"

TowerBehaviour::TowerBehaviour() :AbstractBehaviour()
{
	//ctor
}

TowerBehaviour::~TowerBehaviour()
{
	//dtor
}

void TowerBehaviour::update(float pStep)
{
	//rotates 45° per second
	_owner->rotate(pStep * glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
}
