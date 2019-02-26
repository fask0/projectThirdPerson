#include "mge/core/ShockTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"

Mesh* ShockTower::Mesh;
AbstractMaterial* ShockTower::Material;

ShockTower::ShockTower() : Tower("Shock Tower")
{
	_range = GameController::ShockRange;
	_attSpeed = GameController::ShockAttSpeed;
	_cost = GameController::ShockCost;
	_material = Material;
}

ShockTower::~ShockTower()
{
	//dtor
	Tower::~Tower();
}

void ShockTower::update(float pStep)
{
	//rayCast();

	GameObject::update(pStep);
}

void ShockTower::AddTowerBehaviour()
{

}
