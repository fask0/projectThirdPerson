#include "mge/core/HoneyTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/HoneyTowerBehaviour.hpp"
#include "mge/materials/LitTextureMaterial.hpp"

#include "glm.hpp"
#include "mge/config.hpp"

Mesh* HoneyTower::MainMesh;
Mesh* HoneyTower::MouseMesh;
AbstractMaterial* HoneyTower::MainMaterial;
AbstractMaterial* HoneyTower::MouseMaterial;

HoneyTower::HoneyTower() : Tower("Honey Tower")
{
	_range = GameController::HoneyRange;
	_attSpeed = GameController::HoneyAttSpeed;
	_cost = GameController::HoneyCost;
	_material = MainMaterial;
}

HoneyTower::~HoneyTower()
{
	//dtor
	if (_mouse != nullptr)
		_mouse->Kill();
}

void HoneyTower::update(float pStep)
{
	//rayCast();
	if (isPlaced)
	{
		if (!_isMouseInit)
		{
			_mouse = new GameObject("honeyMouse", getLocalPosition());
			_mouse->scale(glm::vec3(0.5f, 0.5f, 0.5f));
			_mouse->rotate(glm::radians(-90.0f), glm::vec3(0, 1, 0));
			_mouse->setMesh(MouseMesh);
			_mouse->setMaterial(MouseMaterial);
			GameController::CurrentLevel->add(_mouse);
			_isMouseInit = true;
		}
		else
			_mouse->setLocalPosition(getLocalPosition());
	}
	GameObject::update(pStep);
}

void HoneyTower::AddTowerBehaviour()
{
	addBehaviour(new HoneyTowerBehaviour());
}
