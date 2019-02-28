#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include "mge/core/UIManager.hpp"
#include "mge/config.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/AdvancedSprite.hpp"

UIManager::UIManager(sf::RenderWindow * pWindow) : _window(pWindow)
{
	assert(_window != NULL);
	GameController::UIManager = this;
}

UIManager::~UIManager()
{
	//dtor
}

void UIManager::AddSprite(sf::Sprite* pSprite)
{
	_sprites.push_back(pSprite);
}

void UIManager::Draw()
{
	//glDisable( GL_CULL_FACE );
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();
	for each (sf::Sprite* sprite in _sprites)
	{
		_window->draw(*sprite);
	}
	_window->popGLStates();
}
