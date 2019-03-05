#include <iostream>
#include <vector>

#include "mge/core/ChadRat.hpp"
#include "mge/core/Enemy.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/EffectBehaviour.hpp"
#include "mge/core/ToasterProjectile.hpp"

#include "mge/materials/AbstractMaterial.hpp"

std::vector<Mesh*> ChadRat::Animation;
AbstractMaterial* ChadRat::Material;

ChadRat::ChadRat(std::string pName, glm::vec3 pPosition, Waypoint::Lane pLane, std::string pTag)
	: Enemy(pName, pPosition, pLane, pTag)
{
	_size = GameController::ChadSize;
	_health = GameController::ChadHealth;
	_baseHealth = _health;
	_healthRegen = GameController::ChadHealthRegen;
	_damage = GameController::ChadDamage;
	_speed = GameController::ChadSpeed;
	_effectRecovery = GameController::ChadEffectRecoverySpeed;
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

ChadRat::~ChadRat()
{
	Enemy::~Enemy();
}

void ChadRat::update(float pStep)
{
	Enemy::update(pStep);
}

void ChadRat::OnCollisionEnter(GameObject * pOther)
{
	if (pOther->GetTag().compare("toasterProjectile") == 0)
	{
		TakeDamage(50);
	}
}