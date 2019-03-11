#include "mge/behaviours/MenuOnHoverBehaviour.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>

MenuOnHoverBehaviour::MenuOnHoverBehaviour(std::vector<AdvancedSprite*> pMenuItems) : AbstractBehaviour(), menuItems(pMenuItems)
{
	//ctor
}

MenuOnHoverBehaviour::~MenuOnHoverBehaviour()
{
	//dtor
}

void MenuOnHoverBehaviour::update(float pstep)
{
	bool atleastOneBeingHoveredOver = dynamic_cast<AdvancedSprite*>(_owner)->IsBeingHoveredOver;
	for each (AdvancedSprite* sprite in menuItems)
	{
		if (sprite->IsBeingHoveredOver)
		{
			atleastOneBeingHoveredOver = true;
		}
	}
	MenuIsExtended = atleastOneBeingHoveredOver;
	if (MenuIsExtended)
	{
		Extend();
	}
	else
	{
		Retract();
	}
}

void MenuOnHoverBehaviour::Extend()
{
	int offset = 24;
	for (int i = 0; i < menuItems.size(); i++)
	{
		if (menuItems[i]->getPosition().x < dynamic_cast<AdvancedSprite*>(_owner)->getPosition().x + ((i + 1) * menuItems[0]->getGlobalBounds().width) + offset - i)
		{
			menuItems[i]->setPosition(menuItems[i]->getPosition().x + 8.0f, menuItems[i]->getPosition().y);
		}
		else
		{
			menuItems[i]->setPosition(dynamic_cast<AdvancedSprite*>(_owner)->getPosition().x + ((i + 1) * menuItems[0]->getGlobalBounds().width) + offset - i, menuItems[i]->getPosition().y);
		}
	}
}

void MenuOnHoverBehaviour::Retract()
{
	int offset = 10;
	for (int i = 0; i < menuItems.size(); i++)
	{
		if (menuItems[i]->getPosition().x > dynamic_cast<AdvancedSprite*>(_owner)->getPosition().x + offset)
		{
			menuItems[i]->setPosition(menuItems[i]->getPosition().x - 8.0f, menuItems[i]->getPosition().y);
		}
		else
		{
			menuItems[i]->setPosition(dynamic_cast<AdvancedSprite*>(_owner)->getPosition().x + offset, menuItems[i]->getPosition().y);
		}
	}
}

void MenuOnHoverBehaviour::On2DMouseEnter()
{
	AbstractBehaviour::On2DMouseEnter();
}

void MenuOnHoverBehaviour::On2DMouseExit()
{
	AbstractBehaviour::On2DMouseExit();
}