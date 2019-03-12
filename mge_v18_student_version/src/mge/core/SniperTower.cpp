#include "mge/core/SniperTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/SniperTowerBehaviour.hpp"
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"

Mesh* SniperTower::Mesh;
AbstractMaterial* SniperTower::Material;

SniperTower::SniperTower() : Tower("Sniper Tower")
{
	_range = GameController::SniperRange;
	_attSpeed = GameController::SniperAttSpeed;
	_cost = GameController::SniperCost;
	_material = new LitDynamicTextureGridMaterial(GameController::Lights[0], true);
}

SniperTower::~SniperTower()
{
	//dtor
}

void SniperTower::update(float pStep)
{
	//rayCast();
	GameObject::update(pStep);
}

void SniperTower::AddTowerBehaviour()
{
	addBehaviour(new SniperTowerBehaviour());
}
