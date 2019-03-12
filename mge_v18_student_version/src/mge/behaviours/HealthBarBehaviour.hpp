#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "SFML/Graphics.hpp"
#include "mge/core/AdvancedSprite.hpp"

class HealthBarBehaviour : public AbstractBehaviour
{
public:
	HealthBarBehaviour(std::vector<sf::Texture*> pHealthBarStages);
	virtual ~HealthBarBehaviour();

	virtual void update(float pstep);

private:
	std::vector<sf::Texture*> _healthBarStages;
};
