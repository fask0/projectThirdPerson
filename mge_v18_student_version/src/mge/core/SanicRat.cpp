#include <iostream>
#include <vector>
#include <time.h>

#include "mge/behaviours/EffectBehaviour.hpp"

#include "mge/core/SanicRat.hpp"
#include "mge/core/Enemy.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/ToasterProjectile.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/SoundEffects.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/LitTextureMaterial.hpp"

std::vector<SoundEffect*> SanicRat::SFX;
std::vector<Mesh*> SanicRat::Animation;
LitTextureMaterial* SanicRat::Material;
Texture* SanicRat::Texture;

SanicRat::SanicRat(std::string pName, glm::vec3 pPosition, Waypoint::Lane pLane, std::string pTag)
	: Enemy(pName, pPosition, pLane, pTag)
{
	_size = GameController::SanicSize;
	if (GameController::SpawnPoints[0]->_currentWave == 0)
		_health = GameController::SanicHealth;
	else
		_health = GameController::SanicHealth + (GameController::SanicHealth * GameController::SpawnPoints[0]->_currentWave) * 0.1f;
	_baseHealth = _health;
	_healthRegen = GameController::SanicHealthRegen;
	_damage = GameController::SanicDamage;
	_speed = GameController::SanicSpeed;
	_effectRecovery = GameController::SanicEffectRecoverySpeed;
	_baseSpeed = _speed;
	_speedUp = 0;
	_slowDown = 0;

	_animation = Animation;
	_currentFrame = std::rand() % _animation.size();
	setMesh(_animation[0]);
	setMaterial(Material);

	_deathSFX = SFX;

	if (_healthRegen > 0)
		addBehaviour(new EffectBehaviour(EffectBehaviour::HealOverTime, _healthRegen, -1));
}

SanicRat::~SanicRat()
{
}

void SanicRat::update(float pStep)
{
	Enemy::update(pStep);
}
