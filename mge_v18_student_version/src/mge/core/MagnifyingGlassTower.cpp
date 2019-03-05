#include "mge/core/MagnifyingGlassTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/MagnifyingGlassTowerBehaviour.hpp"

Mesh* MagnifyingGlassTower::Mesh;
AbstractMaterial* MagnifyingGlassTower::Material;

MagnifyingGlassTower::MagnifyingGlassTower() : Tower("Magnifying Glass Tower")
{
	_range = GameController::MagnifyingRange;
	_attSpeed = 0;
	_cost = GameController::MagnifyingCost;
	_material = Material;
}

MagnifyingGlassTower::~MagnifyingGlassTower()
{
	//dtor
	Tower::~Tower();
}

void MagnifyingGlassTower::update(float pStep)
{
	//rayCast();

	GameObject::update(pStep);
}

void MagnifyingGlassTower::AddTowerBehaviour()
{
	//addBehaviour(new MagnifyingGlassTowerBehaviour());
}
