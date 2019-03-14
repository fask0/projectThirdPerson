#include "mge/behaviours/SwitchSpriteOnHoverBehaviour.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>
#include "mge/core/GameController.hpp"

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
	if (_advancedOwner == nullptr)
		_advancedOwner = dynamic_cast<AdvancedSprite*>(_owner);

	if (SwitchTexture)
		_advancedOwner->Texture = _switchTexture;
	else
		_advancedOwner->Texture = _advancedOwner->StartTexture;
}

void SwitchSpriteOnHoverBehaviour::On2DMouseOver()
{
	GameController::TowerDefenseScene->isHoveringOverSomething = true;
}

void SwitchSpriteOnHoverBehaviour::On2DMouseEnter()
{
	GameController::TowerDefenseScene->isHoveringOverSomething = true;
	SwitchTexture = true;
	AbstractBehaviour::On2DMouseEnter();
}

void SwitchSpriteOnHoverBehaviour::On2DMouseExit()
{
	SwitchTexture = false;
	AbstractBehaviour::On2DMouseExit();
}