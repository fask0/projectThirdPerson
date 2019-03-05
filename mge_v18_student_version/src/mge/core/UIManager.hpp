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

	void AddSprite(AdvancedSprite* pSprite, sf::Texture* pTexture);

private:
	sf::RenderWindow * _window;
	sf::Font _font;

	std::vector<AdvancedSprite*> _sprites;
	std::vector<sf::Texture*> _textures;

	std::vector<sf::Text*> _texts;


	UIManager(const UIManager&);
	UIManager& operator=(const UIManager&);

};

#endif // DEBUGHUD_HPP
