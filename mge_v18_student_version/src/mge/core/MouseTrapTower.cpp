#include "mge/core/MouseTrapTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"

Mesh* MouseTrapTower::Mesh;
AbstractMaterial* MouseTrapTower::Material;

MouseTrapTower::MouseTrapTower() : Tower("MouseTrap Tower")
{
	_range = GameController::MouseTrapRange;
	_attSpeed = 0;
	_cost = GameController::MouseTrapCost;
	_material = Material;
}

MouseTrapTower::~MouseTrapTower()
{
	//dtor
	Tower::~Tower();
}

void MouseTrapTower::update(float pStep)
{
	//rayCast();

	GameObject::update(pStep);
}
