#include "mge/core/ToasterTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/ToasterTowerBehaviour.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/core/SoundEffects.hpp"

Mesh* ToasterTower::Mesh;
LitTextureMaterial* ToasterTower::Material;
std::vector<SoundEffect*> ToasterTower::SFX;

ToasterTower::ToasterTower() : Tower("Toaster Tower")
{
	_range = GameController::ToasterRange;
	_attSpeed = GameController::ToasterAttSpeed;
	_cost = GameController::ToasterCost;
	_material = Material;
	rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
}

ToasterTower::~ToasterTower()
{
	//dtor
	if (primedProjectile != nullptr)
	{
		delete(primedProjectile);
	}
}

void ToasterTower::update(float pStep)
{
	//rayCast();
	Tower::update(pStep);
}

void ToasterTower::AddTowerBehaviour()
{
	addBehaviour(new ToasterTowerBehaviour());
}

void ToasterTower::PlayAttackSound()
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
