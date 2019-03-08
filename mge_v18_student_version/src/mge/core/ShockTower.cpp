#include "mge/core/ShockTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/ToasterTowerBehaviour.hpp"
#include "mge/behaviours/ShockTowerBehaviour.hpp"
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"

Mesh* ShockTower::Mesh;
AbstractMaterial* ShockTower::Material;

ShockTower::ShockTower() : Tower("Shock Tower")
{
	_range = GameController::ShockRange;
	_attSpeed = GameController::ShockAttSpeed;
	_cost = GameController::ShockCost;
	_material = new LitDynamicTextureGridMaterial(GameController::Lights[0], true);
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
	addBehaviour(new ShockTowerBehaviour());
}
