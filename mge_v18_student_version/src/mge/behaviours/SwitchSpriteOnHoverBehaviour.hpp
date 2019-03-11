#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "SFML/Graphics.hpp"

class SwitchSpriteOnHoverBehaviour : public AbstractBehaviour
{
public:
	SwitchSpriteOnHoverBehaviour(sf::Texture* pSwitchTexture);
	virtual ~SwitchSpriteOnHoverBehaviour();

	virtual void update(float pstep);

	void On2DMouseEnter() override;
	void On2DMouseExit() override;

private:
	sf::Texture* _switchTexture;
};
