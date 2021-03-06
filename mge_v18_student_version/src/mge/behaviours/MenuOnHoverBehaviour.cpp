#include "mge/behaviours/SwitchSpriteOnHoverBehaviour.hpp"
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
		dynamic_cast<SwitchSpriteOnHoverBehaviour*>(_owner->getBehaviours()[0])->SwitchTexture = true;
		Extend(pstep);
	}
	else
	{
		dynamic_cast<SwitchSpriteOnHoverBehaviour*>(_owner->getBehaviours()[0])->SwitchTexture = false;
		Retract(pstep);
	}
}

void MenuOnHoverBehaviour::Extend(float pStep)
{
	int offset = 24;
	for (int i = 0; i < menuItems.size(); i++)
	{
		if (menuItems[i]->getPosition().x < dynamic_cast<AdvancedSprite*>(_owner)->getPosition().x + ((i + 1) * menuItems[1]->getGlobalBounds().width) + offset - i)
		{
			menuItems[i]->setPosition(menuItems[i]->getPosition().x + (1200.0f * pStep), menuItems[i]->getPosition().y);
			if (menuItems[i]->getPosition().x > dynamic_cast<AdvancedSprite*>(_owner)->getPosition().x + ((i + 1) * menuItems[1]->getGlobalBounds().width) + offset - i)
			{
				menuItems[i]->setPosition(dynamic_cast<AdvancedSprite*>(_owner)->getPosition().x + ((i + 1) * menuItems[1]->getGlobalBounds().width) + offset - i, menuItems[i]->getPosition().y);
			}
		}
		else
		{
			menuItems[i]->setPosition(dynamic_cast<AdvancedSprite*>(_owner)->getPosition().x + ((i + 1) * menuItems[1]->getGlobalBounds().width) + offset - i, menuItems[i]->getPosition().y);
		}
	}
}

void MenuOnHoverBehaviour::Retract(float pStep)
{
	int offset = 10;
	for (int i = 0; i < menuItems.size(); i++)
	{
		if (menuItems[i]->getPosition().x > dynamic_cast<AdvancedSprite*>(_owner)->getPosition().x + offset)
		{
			menuItems[i]->setPosition(menuItems[i]->getPosition().x - (1200.0f * pStep), menuItems[i]->getPosition().y);
			if (menuItems[i]->getPosition().x < dynamic_cast<AdvancedSprite*>(_owner)->getPosition().x + offset)
			{
				menuItems[i]->setPosition(dynamic_cast<AdvancedSprite*>(_owner)->getPosition().x + offset, menuItems[i]->getPosition().y);
			}
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