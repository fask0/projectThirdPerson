#include "mge/core/SniperTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/SniperTowerBehaviour.hpp"
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"
#include "mge/core/SoundEffects.hpp"

Mesh* SniperTower::MainMesh;
Mesh* SniperTower::MouseMesh;
AbstractMaterial* SniperTower::MainMaterial;
std::vector<SoundEffect*> SniperTower::SFX;

SniperTower::SniperTower() : Tower("Sniper Tower")
{
	_range = GameController::SniperRange;
	_attSpeed = GameController::SniperAttSpeed;
	_cost = GameController::SniperCost;
	_material = MainMaterial;
}

SniperTower::~SniperTower()
{
	//dtor
	if (_mouse != nullptr)
		_mouse->Kill();
}

void SniperTower::update(float pStep)
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
			_mouse->setMaterial(new LitDynamicTextureGridMaterial(GameController::Lights[0], true));
			GameController::CurrentLevel->add(_mouse);
			_isMouseInit = true;
		}
		else
		{
			_mouse->setLocalPosition(getLocalPosition());
		}
	}
	GameObject::update(pStep);
}

void SniperTower::AddTowerBehaviour()
{
	addBehaviour(new SniperTowerBehaviour());
}

void SniperTower::PlayAttackSound()
{
	for (int i = 0; i < SFX.size(); ++i)
	{
		if (SFX[i]->GetSound().getStatus() != sf::Sound::Playing)
		{
			SFX[i]->PlaySoundEffect();
			break;
		}
	}
}
