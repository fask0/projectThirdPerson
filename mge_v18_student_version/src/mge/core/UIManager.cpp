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
	_font.loadFromFile(config::MGE_SPRITES_PATH + "CREABBB_.TTF");

	//sf::Text* text = new sf::Text("Test123", sf::Font());
	//text->setString("Money: ");
	//text->setPosition(10, 25);
	//text->setCharacterSize(16);
	//_texts.push_back(text);
}

UIManager::~UIManager()
{
	//dtor
}

void UIManager::AddSprite(AdvancedSprite* pSprite)
{
	_sprites.push_back(pSprite);
}

void UIManager::AddText(sf::Text* pText)
{
	_texts.push_back(pText);
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
			_sprites[i]->setTexture(*_sprites[i]->Texture);
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
			if (i == 0 && GameController::GridManager != NULL)
				text.setString(text.getString() + std::to_string(GameController::GridManager->_currentMoney));

			glActiveTexture(GL_TEXTURE0);
			_window->pushGLStates();
			_window->draw(text);
			_window->popGLStates();
		}
	}
}
