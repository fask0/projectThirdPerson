#include "mge/core/IceTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/IceTowerBehaviour.hpp"
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"

Mesh* IceTower::Mesh;
AbstractMaterial* IceTower::Material;

IceTower::IceTower() : Tower("Ice Tower")
{
	_range = GameController::IceRange;
	_attSpeed = GameController::IceAttSpeed;
	_cost = GameController::IceCost;
	_material = new LitDynamicTextureGridMaterial(GameController::Lights[0], true);
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
