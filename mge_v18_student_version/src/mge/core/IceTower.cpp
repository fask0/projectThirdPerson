#include "mge/core/IceTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/IceTowerBehaviour.hpp"
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"
#include "mge/core/SoundEffects.hpp"

Mesh* IceTower::Mesh;
AbstractMaterial* IceTower::Material;
std::vector<SoundEffect*> IceTower::SFX;

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

void IceTower::PlayAttackSound()
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
