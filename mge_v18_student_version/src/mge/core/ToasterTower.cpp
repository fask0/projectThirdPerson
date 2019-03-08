#include "mge/core/ToasterTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/ToasterTowerBehaviour.hpp"
#include "mge/materials/LitTextureMaterial.hpp"

Mesh* ToasterTower::Mesh;
Texture* ToasterTower::Texture;

ToasterTower::ToasterTower() : Tower("Toaster Tower")
{
	_range = GameController::ToasterRange;
	_attSpeed = GameController::ToasterAttSpeed;
	_cost = GameController::ToasterCost;
	_material = new LitTextureMaterial(Texture);
	rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
}

ToasterTower::~ToasterTower()
{
	//dtor
	if (primedProjectile != nullptr)
	{
		delete(primedProjectile);
	}
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
