#include "AbstractBehaviour.hpp"
#include <iostream>

AbstractBehaviour::AbstractBehaviour() :_owner(nullptr) {}

AbstractBehaviour::~AbstractBehaviour()
{
	_owner = nullptr;
}

void AbstractBehaviour::setOwner(GameObject* pOwner)
{
	_owner = pOwner;
}

GameObject* AbstractBehaviour::getOwner()
{
	return _owner;
}

