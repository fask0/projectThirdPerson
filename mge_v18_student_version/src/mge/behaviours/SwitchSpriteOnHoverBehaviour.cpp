#include "mge/behaviours/SwitchSpriteOnHoverBehaviour.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>

SwitchSpriteOnHoverBehaviour::SwitchSpriteOnHoverBehaviour(sf::Texture* pSwitchTexture) : AbstractBehaviour(), _switchTexture(pSwitchTexture)
{
	//ctor
}

SwitchSpriteOnHoverBehaviour::~SwitchSpriteOnHoverBehaviour()
{
	//dtor
}

void SwitchSpriteOnHoverBehaviour::update(float pstep)
{
}

void SwitchSpriteOnHoverBehaviour::On2DMouseEnter()
{
	dynamic_cast<AdvancedSprite*>(_owner)->Texture = _switchTexture;
	AbstractBehaviour::On2DMouseEnter();
}

void SwitchSpriteOnHoverBehaviour::On2DMouseExit()
{
	dynamic_cast<AdvancedSprite*>(_owner)->Texture = dynamic_cast<AdvancedSprite*>(_owner)->StartTexture;
	AbstractBehaviour::On2DMouseExit();
}