#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "mge/core/AdvancedSprite.hpp"

/**
 * Very simple class capable of rendering a simple piece of text through SFML.
 */
class UIManager
{
public:
	UIManager(sf::RenderWindow * pWindow);
	virtual ~UIManager();
	void Draw();

	void AddSprite(sf::Sprite* pSprite);

private:
	sf::RenderWindow * _window;
	std::vector<sf::Sprite*> _sprites;

	UIManager(const UIManager&);
	UIManager& operator=(const UIManager&);

};

#endif // DEBUGHUD_HPP
