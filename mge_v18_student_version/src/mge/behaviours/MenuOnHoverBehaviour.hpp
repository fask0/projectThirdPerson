#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "SFML/Graphics.hpp"
#include "mge/core/AdvancedSprite.hpp"

class MenuOnHoverBehaviour : public AbstractBehaviour
{
public:
	MenuOnHoverBehaviour(std::vector<AdvancedSprite*> pMenuItems);
	virtual ~MenuOnHoverBehaviour();

	virtual void update(float pstep);

	void On2DMouseEnter() override;
	void On2DMouseExit() override;

private:
	std::vector<AdvancedSprite*> menuItems;
	AdvancedSprite* _advancedOwner;
	bool MenuIsExtended;

	void Extend();
	void Retract();
};
