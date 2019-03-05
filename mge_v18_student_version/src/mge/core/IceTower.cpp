#include "mge/core/IceTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/IceTowerBehaviour.hpp"

Mesh* IceTower::Mesh;
AbstractMaterial* IceTower::Material;

IceTower::IceTower() : Tower("Ice Tower")
{
	_range = GameController::IceRange;
	_attSpeed = GameController::IceAttSpeed;
	_cost = GameController::IceCost;
	_material = Material;
}

IceTower::~IceTower()
{
	//dtor
	Tower::~Tower();
}

void IceTower::update(float pStep)
{
	//rayCast();

	GameObject::update(pStep);
}

void IceTower::AddTowerBehaviour()
{
	addBehaviour(new IceTowerBehaviour());
}
