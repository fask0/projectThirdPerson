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

void AbstractBehaviour::On2DMouseEnter()
{
	std::cout << "Enter" << std::endl;
}
void AbstractBehaviour::On2DMouseExit()
{
	std::cout << "Exit" << std::endl;
}
void AbstractBehaviour::On2DMouseOver()
{
	std::cout << "Over" << std::endl;
}
void AbstractBehaviour::On2DMouseClick()
{
	std::cout << "Click" << std::endl;
}

