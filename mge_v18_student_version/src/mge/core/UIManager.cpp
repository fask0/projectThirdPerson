#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include "mge/core/UIManager.hpp"
#include "mge/config.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include "mge/behaviours/WASDBehaviour.hpp"

//std::vector<AdvancedSprite*> UIManager::_sprites;

UIManager::UIManager(sf::RenderWindow * pWindow) : _window(pWindow)
{
	assert(_window != NULL);
	GameController::UIManager = this;
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
}
