#include "mge/core/AdvancedSprite.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "mge/core/GameObject.hpp"
#include "mge/core/GameController.hpp"

AdvancedSprite::AdvancedSprite(sf::Texture* pTexture) : sf::Sprite(), GameObject("Advanced Sprite"), Texture(pTexture), StartTexture(pTexture), IsBeingHoveredOver(false)
{
}


AdvancedSprite::~AdvancedSprite()
{
}

void AdvancedSprite::update(float pStep)
{
	if (GameController::Window != nullptr)
	{
		sf::FloatRect spriteBoundaries = sf::Sprite::getGlobalBounds();
		sf::Vector2i mousePos = sf::Mouse::getPosition(*GameController::Window);

		if (mousePos.x > spriteBoundaries.left &&
			mousePos.x < spriteBoundaries.left + spriteBoundaries.width &&
			mousePos.y > spriteBoundaries.top &&
			mousePos.y < spriteBoundaries.top + spriteBoundaries.height)
		{
			if (_lastMouseOver)
			{
				//Execute mouseover
				for each (AbstractBehaviour* behaviour in getBehaviours())
				{
					behaviour->On2DMouseOver();
				}
			}
			else
			{
				//Execute mouseenter
				for each (AbstractBehaviour* behaviour in getBehaviours())
				{
					behaviour->On2DMouseEnter();
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				//Execute onclick
				for each (AbstractBehaviour* behaviour in getBehaviours())
				{
					behaviour->On2DMouseClick();
				}
			}
			_lastMouseOver = true;
		}
		else
		{
			if (_lastMouseOver)
			{
				//Execute mouseexit
				for each (AbstractBehaviour* behaviour in getBehaviours())
				{
					behaviour->On2DMouseExit();
				}
				_lastMouseOver = false;
			}
		}
	}
	GameObject::update(pStep);
}
