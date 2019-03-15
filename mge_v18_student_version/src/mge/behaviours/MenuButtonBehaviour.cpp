#include "mge/behaviours/MenuButtonBehaviour.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>
#include "mge/core/EnemySpawner.hpp"
#include <chrono>
#include <thread>

MenuButtonBehaviour::MenuButtonBehaviour(bool pLoadNextLevel) : AbstractBehaviour(), _loadNextLevel(pLoadNextLevel)
{
}

MenuButtonBehaviour::MenuButtonBehaviour(int pLevelToLoadOnClick) : AbstractBehaviour(), _levelToLoad(pLevelToLoadOnClick), _loadNextLevel(false)
{
}

MenuButtonBehaviour::MenuButtonBehaviour(MenuManager::Menu pMenuToLoadOnClick, bool pLoadNextLevel) : AbstractBehaviour(), _menuToLoad(pMenuToLoadOnClick), _loadNextLevel(pLoadNextLevel)
{
}

MenuButtonBehaviour::MenuButtonBehaviour(MenuManager::Menu pMenuToLoadOnClick, int pIndexLevelToLoadOnClick) : AbstractBehaviour(), _menuToLoad(pMenuToLoadOnClick), _levelToLoad(pIndexLevelToLoadOnClick), _loadNextLevel(false)
{
}

MenuButtonBehaviour::~MenuButtonBehaviour()
{
}

void MenuButtonBehaviour::update(float pstep)
{
}

void MenuButtonBehaviour::On2DMouseClick()
{
	if (_menuToLoad != MenuManager::Menu::None)
	{
		if (_menuToLoad == MenuManager::Menu::CloseAllScreens)
		{
			GameController::MenuManager->ClearMenus();
		}
		else
		{
			if (GameController::CurrentLevel != nullptr)
			{
				GameController::CurrentLevel->_children.clear();
				GameController::UIManager->_sprites.clear();
				GameController::UIManager->_texts.clear();
				GameController::CurrentHealth = GameController::MaxHealth;
				GameController::GridManager->_currentMoney = GameController::StartingMoney;
				GameController::Enemies.clear();
				for each (EnemySpawner* spawner in GameController::SpawnPoints)
				{
					spawner->_currentWave = 0;
				}
			}
			GameController::MenuManager->CreateMenu(_menuToLoad);
			GameController::UIManager->Draw();
			if (GameController::GameplayMusic->GetMusic().getStatus() == sf::Music::Playing)
			{
				GameController::GameplayMusic->Pause();
				if (GameController::MainMenuMusic->GetMusic().getStatus() != sf::Music::Playing)
					GameController::MainMenuMusic->Play();
			}
		}
	}
	else if (_levelToLoad < 0 && !_loadNextLevel)
	{
		exit(0);
		return;
	}
	if (_levelToLoad >= 0)
	{
		GameController::MenuManager->LoadLevelNextFrame(_levelToLoad);
	}
	if (_loadNextLevel)
	{
		GameController::MenuManager->LoadLevelNextFrame();
	}
}