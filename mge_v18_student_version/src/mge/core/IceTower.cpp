#include "mge/core/IceTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/IceTowerBehaviour.hpp"
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"
#include "mge/core/SoundEffects.hpp"
#include "mge/Behaviours/CollisionBehaviour.hpp"

Mesh* IceTower::MainMesh;
Mesh* IceTower::MouseMesh;
AbstractMaterial* IceTower::MainMaterial;
AbstractMaterial* IceTower::MouseMaterial;
std::vector<SoundEffect*> IceTower::SFX;

IceTower::IceTower() : Tower("Ice Tower")
{
	_range = GameController::IceRange;
	_attSpeed = GameController::IceAttSpeed;
	_cost = GameController::IceCost;
	_material = MainMaterial;

	removeAllBehaviours();

	float xScale = glm::sqrt(getTransform()[0][0] * getTransform()[0][0] + getTransform()[0][1] * getTransform()[0][1] + getTransform()[0][2] * getTransform()[0][2]);
	float yScale = glm::sqrt(getTransform()[1][0] * getTransform()[1][0] + getTransform()[1][1] * getTransform()[1][1] + getTransform()[1][2] * getTransform()[1][2]);
	float zScale = glm::sqrt(getTransform()[2][0] * getTransform()[2][0] + getTransform()[2][1] * getTransform()[2][1] + getTransform()[2][2] * getTransform()[2][2]);

	addBehaviour(new CollisionBehaviour(CollisionBehaviour::Tower, glm::vec3(xScale * 1.5f, yScale, zScale * 1.5f), true, glm::vec3(0, yScale / 2, 0)));
}

IceTower::~IceTower()
{
	//dtor
	if (_mouse != nullptr)
		_mouse->Kill();
}

void IceTower::update(float pStep)
{
	//rayCast();
	if (isPlaced)
	{
		if (!_isMouseInit)
		{
			_mouse = new GameObject("iceMouse", getLocalPosition());
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

void IceTower::AddTowerBehaviour()
{
	addBehaviour(new IceTowerBehaviour());
}

void IceTower::PlayAttackSound()
{
	for (int i = 0; i < SFX.size(); ++i)
	{
		if (SFX[i]->GetSound().getStatus() != sf::Sound::Playing)
		{
			SFX[i]->Play();
			break;
		}
	}
}
