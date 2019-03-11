#include "mge/behaviours/TowerIconBehaviour.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>
#include "mge/core/GameController.hpp"

TowerIconBehaviour::TowerIconBehaviour(int pTowerNumber, sf::Texture* pDescription) : AbstractBehaviour(), _towerNumber(pTowerNumber)
{
	_description = new AdvancedSprite(pDescription);
	//ctor
}

TowerIconBehaviour::~TowerIconBehaviour()
{
	//dtor
}

void TowerIconBehaviour::update(float pstep)
{
	_description->setPosition(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y - _description->getLocalBounds().height - 32));
}

void TowerIconBehaviour::On2DMouseEnter()
{
	_descriptionIndex = GameController::UIManager->_sprites.size();
	GameController::UIManager->AddSprite(_description);
	AbstractBehaviour::On2DMouseEnter();
}

void TowerIconBehaviour::On2DMouseExit()
{
	for (int i = 0; i < GameController::UIManager->_sprites.size(); i++)
	{
		if (GameController::UIManager->_sprites[i] == _description)
		{
			GameController::UIManager->_sprites.erase(GameController::UIManager->_sprites.begin() + i);
		}
	}
	AbstractBehaviour::On2DMouseExit();
}

void TowerIconBehaviour::On2DMouseClick()
{
	GameController::GridManager->SelectTower(_towerNumber);
	GameController::GridManager->PauseTowerPlacement();
	AbstractBehaviour::On2DMouseClick();
}