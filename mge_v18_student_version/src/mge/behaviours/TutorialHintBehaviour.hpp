#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "SFML/Graphics.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include <time.h>

class TutorialHintBehaviour : public AbstractBehaviour
{
public:
	TutorialHintBehaviour(std::vector<sf::Texture*> pHintItems);
	virtual ~TutorialHintBehaviour();

	virtual void update(float pstep);

	void On2DMouseClick() override;

private:
	std::vector<sf::Texture*> hintItems;
	AdvancedSprite* _advancedOwner;
	clock_t _lastClockTime;

	int _textureIndex = 0;
};
