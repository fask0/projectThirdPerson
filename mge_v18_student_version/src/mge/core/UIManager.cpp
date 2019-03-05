#include <cassert>
#include <iostream>
#include <string>
#include <cstring>

#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>
#include "mge/core/UIManager.hpp"
#include "mge/config.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include "mge/core/GridManager.hpp"

//std::vector<AdvancedSprite*> UIManager::_sprites;

UIManager::UIManager(sf::RenderWindow * pWindow) : _window(pWindow)
{
	assert(_window != NULL);
	GameController::UIManager = this;
	_font.loadFromFile(config::MGE_FONT_PATH + "arial.ttf");

	sf::Text* text = new sf::Text("Test123", sf::Font());
	text->setString("Money: ");
	text->setPosition(10, 25);
	text->setCharacterSize(16);
	text->setFillColor(sf::Color::White);
	_texts.push_back(text);
}

UIManager::~UIManager()
{
	//dtor
}

void UIManager::AddSprite(AdvancedSprite* pSprite, sf::Texture* pTexture)
{
	_sprites.push_back(pSprite);
	_textures.push_back(pTexture);
}

void UIManager::Draw()
{
	//Sprites
	if (_sprites.size() > 0)
	{
		//glDisable( GL_CULL_FACE );
		glActiveTexture(GL_TEXTURE0);
		_window->pushGLStates();
		for (int i = 0; i < _sprites.size(); i++)
		{
			_sprites[i]->setTexture(*_textures[i]);
			_window->draw(*_sprites[i]);
		}
		_window->popGLStates();
	}
	//Text
	if (_texts.size() > 0)
	{
		for (int i = 0; i < _texts.size(); i++)
		{
			_texts[i]->setFont(_font);
			sf::Text text = *_texts[i];
			if (i == 0)
				text.setString(text.getString() + std::to_string(GameController::GridManager->_currentMoney));

			glActiveTexture(GL_TEXTURE0);
			_window->pushGLStates();
			_window->draw(text);
			_window->popGLStates();
		}
	}
}
