#include "AbstractBehaviour.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include "mge/core/GameController.hpp"
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
	if (dynamic_cast<AdvancedSprite*>(_owner))
	{
		dynamic_cast<AdvancedSprite*>(_owner)->IsBeingHoveredOver = true;
		GameController::UIClick->Play();
	}
}
void AbstractBehaviour::On2DMouseExit()
{
	if (dynamic_cast<AdvancedSprite*>(_owner))
	{
		dynamic_cast<AdvancedSprite*>(_owner)->IsBeingHoveredOver = false;
	}
}
void AbstractBehaviour::On2DMouseOver()
{
}
void AbstractBehaviour::On2DMouseClick()
{
}

