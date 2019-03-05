#include <iostream>
#include <vector>

#include "mge/core/Rat.hpp"
#include "mge/core/Enemy.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/EffectBehaviour.hpp"
#include "mge/core/ToasterProjectile.hpp"

#include "mge/materials/AbstractMaterial.hpp"

std::vector<Mesh*> Rat::Animation;
AbstractMaterial* Rat::Material;

Rat::Rat(std::string pName, glm::vec3 pPosition, Waypoint::Lane pLane, std::string pTag)
	: Enemy(pName, pPosition, pLane, pTag)
{
	_size = GameController::RatSize;
	_health = GameController::RatHealth;
	_baseHealth = _health;
	_healthRegen = GameController::RatHealthRegen;
	_damage = GameController::RatDamage;
	_speed = GameController::RatSpeed;
	_effectRecovery = GameController::RatEffectRecoverySpeed;
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

Rat::~Rat()
{
	Enemy::~Enemy();
}

void Rat::update(float pStep)
{
	Enemy::update(pStep);
}