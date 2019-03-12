#include <iostream>
#include <vector>
#include <time.h>

#include "mge/core/ShockTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/ToasterTowerBehaviour.hpp"
#include "mge/behaviours/ShockTowerBehaviour.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/core/SoundEffects.hpp"

#include "mge/config.hpp"

Mesh* ShockTower::MainMesh;
std::vector<Mesh*> ShockTower::Animations;
AbstractMaterial* ShockTower::AnimationMaterial;
std::vector<SoundEffect*> ShockTower::SFX;

ShockTower::ShockTower() : Tower("Shock Tower")
{
	_range = GameController::ShockRange;
	_attSpeed = GameController::ShockAttSpeed;
	_cost = GameController::ShockCost;
	_material = new LitDynamicTextureGridMaterial(GameController::Lights[0], true);
	_aoeModel = new GameObject("ShockTowerAoE", glm::vec3(0, 0, 0));
	_aoeModel->setMaterial(AnimationMaterial);
	add(_aoeModel);
}

ShockTower::~ShockTower()
{
	//dtor
}

void ShockTower::update(float pStep)
{
	//rayCast();
	GameObject::update(pStep);

	if (_shouldDie || !isPlaced) return;
	if (clock() >= _timer + 0.1f * CLOCKS_PER_SEC)
	{
		_aoeModel->setMesh(Animations[_currentFrame]);
		_currentFrame++;
		if (_currentFrame == Animations.size())
			_currentFrame = 0;
		_timer = clock();
	}
}

void ShockTower::AddTowerBehaviour()
{
	addBehaviour(new ShockTowerBehaviour());
}

void ShockTower::PlayAttackSound()
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
