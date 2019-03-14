#include "mge/behaviours/TutorialHintBehaviour.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>

TutorialHintBehaviour::TutorialHintBehaviour(std::vector<sf::Texture*> pHintItems) : AbstractBehaviour(), hintItems(pHintItems)
{
	_lastClockTime = clock();
	//ctor
}

TutorialHintBehaviour::~TutorialHintBehaviour()
{
	//dtor
}

void TutorialHintBehaviour::update(float pstep)
{
}

void TutorialHintBehaviour::On2DMouseClick()
{
	if (clock() - _lastClockTime > 0.5f * CLOCKS_PER_SEC)
	{
		if (_textureIndex < hintItems.size())
		{
			dynamic_cast<AdvancedSprite*>(_owner)->Texture = hintItems[_textureIndex];
			_textureIndex++;
			_lastClockTime = clock();
		}
		else
		{
			for (int i = 0; i < GameController::UIManager->_sprites.size(); i++)
			{
				if (GameController::UIManager->_sprites[i] == dynamic_cast<AdvancedSprite*>(_owner))
				{
					GameController::UIManager->_sprites.erase(GameController::UIManager->_sprites.begin() + i);
					i--;
				}
			}
			_owner->Kill();
		}
	}
}