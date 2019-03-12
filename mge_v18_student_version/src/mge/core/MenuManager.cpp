#include "mge/core/AdvancedSprite.hpp"
#include "mge/core/MenuManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "mge/core/GameObject.hpp"
#include "mge/core/GameController.hpp"

MenuManager::MenuManager() :GameObject("Menu Manager")
{
}


MenuManager::~MenuManager()
{
}

void MenuManager::update(float pStep)
{
	GameObject::update(pStep);
}
