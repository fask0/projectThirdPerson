#include "mge/behaviours/HealthBarBehaviour.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>

HealthBarBehaviour::HealthBarBehaviour(std::vector<sf::Texture*> pHealthBarStages) : AbstractBehaviour(), _healthBarStages(pHealthBarStages)
{
	//ctor
}

HealthBarBehaviour::~HealthBarBehaviour()
{
	//dtor
}

void HealthBarBehaviour::update(float pstep)
{
	int stage = 9;
	for (int i = _healthBarStages.size(); i > 0; i--)
	{
		if (GameController::CurrentHealth < (float(GameController::MaxHealth) / float(_healthBarStages.size() + 1)) * i)
		{
			stage = i - 1;
		}
	}
	if (stage < 9)
	{
		dynamic_cast<AdvancedSprite*>(_owner)->Texture = _healthBarStages[stage];
	}
}