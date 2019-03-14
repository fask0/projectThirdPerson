#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "SFML/Graphics.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include "mge/core/EnemySpawner.hpp"

class NextWaveButtonBehaviour : public AbstractBehaviour
{
public:
	NextWaveButtonBehaviour();
	virtual ~NextWaveButtonBehaviour();

	virtual void update(float pstep);

	void On2DMouseClick() override;

};
