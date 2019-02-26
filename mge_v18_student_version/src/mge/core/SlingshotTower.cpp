#include "mge/core/SlingshotTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"

Mesh* SlingshotTower::Mesh;
AbstractMaterial* SlingshotTower::Material;

SlingshotTower::SlingshotTower() : Tower("Slingshot Tower")
{
	_range = GameController::SlingshotRange;
	_attSpeed = GameController::SlingshotAttSpeed;
	_cost = GameController::SlingshotCost;
	_material = Material;
}

SlingshotTower::~SlingshotTower()
{
	//dtor
	Tower::~Tower();
}

void SlingshotTower::update(float pStep)
{
	//rayCast();

	GameObject::update(pStep);
}
