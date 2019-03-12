#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "SFML/Graphics.hpp"
#include "mge/core/AdvancedSprite.hpp"

class TowerIconBehaviour : public AbstractBehaviour
{
public:
	TowerIconBehaviour(int pTowerNumber, sf::Texture* pDescription);
	virtual ~TowerIconBehaviour();

	virtual void update(float pstep);

	void On2DMouseEnter() override;
	void On2DMouseExit() override;
	void On2DMouseClick() override;

private:
	int _towerNumber;
	AdvancedSprite* _description;
	int _descriptionIndex;
};
