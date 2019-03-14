#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "SFML/Graphics.hpp"
#include "mge/core/AdvancedSprite.hpp"

class SellTowerBehaviour : public AbstractBehaviour
{
public:
	SellTowerBehaviour();
	virtual ~SellTowerBehaviour();

	virtual void update(float pstep);

	void On2DMouseClick() override;
};
