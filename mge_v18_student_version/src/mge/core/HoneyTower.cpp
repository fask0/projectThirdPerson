#include "mge/core/HoneyTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/HoneyTowerBehaviour.hpp"
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"

Mesh* HoneyTower::Mesh;
AbstractMaterial* HoneyTower::Material;

HoneyTower::HoneyTower() : Tower("Honey Tower")
{
	_range = GameController::HoneyRange;
	_attSpeed = GameController::HoneyAttSpeed;
	_cost = GameController::HoneyCost;
	_material = new LitDynamicTextureGridMaterial(GameController::Lights[0], true);
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
	addBehaviour(new HoneyTowerBehaviour());
}
