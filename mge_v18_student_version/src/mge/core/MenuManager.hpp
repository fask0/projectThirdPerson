#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "mge/core/GameObject.hpp"
#include "mge/core/AdvancedSprite.hpp"

class MenuManager : public GameObject
{
public:
	MenuManager();
	~MenuManager();

	void update(float pStep) override;


	enum Menu
	{
		MainMenu,
		LevelSelectMenu,
		WinMenu,
		LoseMenu,
		LoadingScreen,
		PauseScreen,
		None,
		CloseAllScreens
	};
	void ClearMenus();
	void CreateMenu(Menu pMenu);

	void Inputs(sf::Event pEvent);

	//pIndex of -1 = next level 
	void LoadLevelNextFrame(int pIndex = -1);
	bool GetWinScreenBeingDisplayed();
	bool AreAnyScreensEnabled = true;

private:
	void init();
	void initMainMenu();
	void initLevelSelectMenu();
	void initWinMenu();
	void initLoseMenu();
	void initLoadingScreen();
	void initPauseScreen();

	bool _mainMenuBeingDisplayed = false;
	bool _levelSelectMenuBeingDisplayed = false;
	bool _winMenuBeingDisplayed = false;
	bool _loseMenuBeingDisplayed = false;
	bool _loadingScreenBeingDisplayed = false;
	bool _pauseScreenBeingDisplayed = false;

	bool _loadLevelNextFrame = false;
	int _levelIndex;
	int _frameCount = 10;

	AdvancedSprite* _mainMenu;
	AdvancedSprite* _levelSelectMenu;
	AdvancedSprite* _winMenu;
	AdvancedSprite* _loseMenu;
	AdvancedSprite* _loadingScreen;
	AdvancedSprite* _pauseScreen;
};