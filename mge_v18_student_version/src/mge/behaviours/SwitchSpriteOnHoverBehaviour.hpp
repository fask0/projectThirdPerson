#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "SFML/Graphics.hpp"
#include "mge/core/AdvancedSprite.hpp"

class SwitchSpriteOnHoverBehaviour : public AbstractBehaviour
{
public:
	SwitchSpriteOnHoverBehaviour(sf::Texture* pSwitchTexture);
	virtual ~SwitchSpriteOnHoverBehaviour();

	virtual void update(float pstep);

	void On2DMouseEnter() override;
	void On2DMouseExit() override;

	bool SwitchTexture = false;

private:
	sf::Texture* _switchTexture;
	AdvancedSprite* _advancedOwner = nullptr;
};
