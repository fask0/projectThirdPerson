#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "SFML/Graphics.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include "mge/core/MenuManager.hpp"
#include "mge/core/GameController.hpp"

class MenuButtonBehaviour : public AbstractBehaviour
{
public:
	MenuButtonBehaviour(bool pLoadNextLevel = true);
	MenuButtonBehaviour(int pIndexLevelToLoadOnClick);
	MenuButtonBehaviour(MenuManager::Menu pMenuToLoadOnClick, bool pLoadNextLevel = false);
	MenuButtonBehaviour(MenuManager::Menu pMenuToLoadOnClick, int pIndexLevelToLoadOnClick);
	virtual ~MenuButtonBehaviour();

	virtual void update(float pstep);
	void On2DMouseClick() override;

private:
	bool _loadLevelNextUpdate = false;
	bool _loadNextLevel;
	int _levelToLoad = -1;
	MenuManager::Menu _menuToLoad = MenuManager::Menu::None;
};
