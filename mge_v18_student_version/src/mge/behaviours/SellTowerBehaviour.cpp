#include "mge/behaviours/SellTowerBehaviour.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>

SellTowerBehaviour::SellTowerBehaviour() : AbstractBehaviour()
{
	//ctor
}

SellTowerBehaviour::~SellTowerBehaviour()
{
	//dtor
}

void SellTowerBehaviour::update(float pstep)
{
}

void SellTowerBehaviour::On2DMouseClick()
{
	GameController::GridManager->SellSelectedTower();
}