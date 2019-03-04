#include "mge/core/MouseTrapTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/ToasterTower.hpp"
#include "mge/core/MouseTrapTower.hpp"
#include "mge/core/HoneyTower.hpp"
#include "mge/core/ShockTower.hpp"

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

void MouseTrapTower::AddTowerBehaviour()
{

}
