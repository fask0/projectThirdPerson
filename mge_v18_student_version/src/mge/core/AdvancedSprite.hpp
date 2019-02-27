#ifndef ADVANCEDSPRITE_HPP
#define ADVANCEDSPRITE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "mge/core/GameObject.hpp"

class AdvancedSprite : public sf::Sprite, public GameObject
{
public:
	AdvancedSprite();
	~AdvancedSprite();

	void update(float pStep) override;
private:
	bool _lastMouseOver = false;
};

#endif