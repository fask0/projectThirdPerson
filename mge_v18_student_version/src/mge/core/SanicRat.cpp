#include <iostream>
#include <vector>
#include <time.h>

#include "mge/core/SanicRat.hpp"
#include "mge/core/Enemy.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/EffectBehaviour.hpp"
#include "mge/core/ToasterProjectile.hpp"

#include "mge/materials/AbstractMaterial.hpp"

std::vector<Mesh*> SanicRat::Animation;
AbstractMaterial* SanicRat::Material;

SanicRat::SanicRat(std::string pName, glm::vec3 pPosition, Waypoint::Lane pLane, std::string pTag)
	: Enemy(pName, pPosition, pLane, pTag)
{
	_size = GameController::SanicSize;
	_health = GameController::SanicHealth;
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

	if (_healthRegen > 0)
		addBehaviour(new EffectBehaviour(EffectBehaviour::HealOverTime, _healthRegen, -1));
}

SanicRat::~SanicRat()
{
	Enemy::~Enemy();
}

void SanicRat::update(float pStep)
{
	Enemy::update(pStep);
}

void SanicRat::OnCollisionEnter(GameObject * pOther)
{
	if (pOther->GetTag().compare("toasterProjectile") == 0)
	{
		TakeDamage(50);
	}
}