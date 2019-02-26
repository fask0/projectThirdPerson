#include "mge/core/HoneyTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"

Mesh* HoneyTower::Mesh;
AbstractMaterial* HoneyTower::Material;

HoneyTower::HoneyTower() : Tower("Honey Tower")
{
	_range = GameController::HoneyRange;
	_attSpeed = GameController::HoneyAttSpeed;
	_cost = GameController::HoneyCost;
	_material = Material;
}

HoneyTower::~HoneyTower()
{
	//dtor
	Tower::~Tower();
}

void HoneyTower::update(float pStep)
{
	//rayCast();

	GameObject::update(pStep);
}

void HoneyTower::AddTowerBehaviour()
{

}
