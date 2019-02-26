#include "mge/core/ToasterTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/ToasterTowerBehaviour.hpp"

Mesh* ToasterTower::Mesh;
AbstractMaterial* ToasterTower::Material;

ToasterTower::ToasterTower() : Tower("Toaster Tower")
{
	_range = GameController::ToasterRange;
	_attSpeed = GameController::ToasterAttSpeed;
	_cost = GameController::ToasterCost;
	_material = Material;
}

ToasterTower::~ToasterTower()
{
	//dtor
	Tower::~Tower();
}

void ToasterTower::update(float pStep)
{
	//rayCast();

	GameObject::update(pStep);
}

void ToasterTower::AddTowerBehaviour()
{
	addBehaviour(new ToasterTowerBehaviour());
}
