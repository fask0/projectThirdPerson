#include <iostream>
#include <vector>
#include <time.h>

#include "mge/behaviours/WaypointFollowBehaviour.hpp"
#include "mge/behaviours/CollisionBehaviour.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/core/Enemy.hpp"
#include "mge/core/Waypoint.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/SoundEffects.hpp"

std::vector<SoundEffect*> Enemy::CutSFX;
std::vector<SoundEffect*> Enemy::BurnSFX;
std::vector<SoundEffect*> Enemy::FreezeSFX;
std::vector<SoundEffect*> Enemy::HoneySlowSFX;
Mesh* Enemy::HealthBarMesh;
TextureMaterial* Enemy::HealthBarMaterial;
TextureMaterial* Enemy::HealthBarMaterialBG;

#include "mge/materials/TextureMaterial.hpp"

#include "mge/config.hpp"

Enemy::Enemy(std::string pName, glm::vec3 pPosition, Waypoint::Lane pLane, std::string pTag)
	: GameObject(pName, pPosition), _lane(pLane)
{
	_tag = pTag;
	_ignoreTags.push_back(_tag);

	WaypointFollowBehaviour* wpBehaviour = new WaypointFollowBehaviour(pLane);
	addBehaviour(wpBehaviour);
	wpBehaviour->Init();

	CollisionBehaviour* colBehaviour = new CollisionBehaviour(CollisionBehaviour::Projectile, 0.5f, false, glm::vec3(0, 0.25f, 0));
	addBehaviour(colBehaviour);
	if (GameController::DrawColliders)
		colBehaviour->DrawCollider();

	if (pName.compare(""))

		_timer = 0;
	GameController::Enemies.push_back(this);

	_healthBar = new GameObject("HealthBar", glm::vec3(0.2f, 2, 0));
	_healthBar->setMesh(HealthBarMesh);
	_healthBar->scale(glm::vec3(0.1f, 0.03f, 0.75f));
	_healthBarBackground = new GameObject("HealthBarBackground", glm::vec3(0.2f, 1.98f, 0));
	_healthBarBackground->setMesh(HealthBarMesh);
	_healthBarBackground->scale(glm::vec3(0.15f, 0.03f, 0.8f));
	add(_healthBar);
	add(_healthBarBackground);
}

Enemy::~Enemy()
{
	for (int i = 0; i < GameController::Enemies.size(); ++i)
		if (GameController::Enemies[i] == this)
			GameController::Enemies.erase(GameController::Enemies.begin() + i);

	if (_health <= 0)
	{
		int rnd = rand() % _deathSFX.size();
		_deathSFX[rnd]->PlaySoundEffect();
	}
}

void Enemy::update(float pStep)
{
	distanceValue += getSpeed();
	GameObject::update(pStep);
	//Healthbar stuff
	//_healthBar->setTransform(glm::inverse(glm::lookAt(_healthBar->getLocalPosition(), GameController::MainCamera->getLocalPosition(), glm::vec3(0, 1, 0))));

	if (_shouldDie) return;
	if (clock() >= _timer + ((pStep * CLOCKS_PER_SEC) / getSpeed() * 5))
	{
		setMesh(_animation[_currentFrame]);
		_currentFrame++;
		if (_currentFrame == _animation.size())
			_currentFrame = 0;
		_timer = clock();
	}

	if (_shouldShowHealthBar)
	{
		_healthBar->setMaterial(HealthBarMaterial);
		_healthBarBackground->setMaterial(HealthBarMaterialBG);
		if (clock() >= _healthBarTimer + 5 * CLOCKS_PER_SEC)
		{
			_healthBar->removeMaterial();
			_healthBarBackground->removeMaterial();
			_shouldShowHealthBar = false;
		}
	}

	if (_speed == _baseSpeed) return;
	if (_speed + pStep * _effectRecovery <= _baseSpeed)
		_speed += pStep * _effectRecovery;
	else if (_speed - pStep * _effectRecovery >= _baseSpeed)
		_speed -= pStep * _effectRecovery;
}

void Enemy::OnCollisionEnter(GameObject* pOther)
{
	if (pOther->GetTag().compare("toasterProjectile") == 0)
	{
		int rnd = rand() % CutSFX.size();
		if (CutSFX[rnd]->GetSound().getStatus() != sf::Sound::Playing)
			CutSFX[rnd]->PlaySoundEffect();
	}
	else if (pOther->GetTag().compare("iceProjectile") == 0)
	{
		int rnd = rand() % FreezeSFX.size();
		if (FreezeSFX[rnd]->GetSound().getStatus() != sf::Sound::Playing)
			FreezeSFX[rnd]->PlaySoundEffect();
	}
	else if (pOther->GetTag().compare("honeyProjectile") == 0)
	{
		int rnd = rand() % HoneySlowSFX.size();
		if (HoneySlowSFX[rnd]->GetSound().getStatus() != sf::Sound::Playing)
			HoneySlowSFX[rnd]->PlaySoundEffect();
	}
	else if (pOther->GetTag().compare("magnifyingGlassHitBox") == 0)
	{
		int rnd = rand() % BurnSFX.size();
		if (BurnSFX[rnd]->GetSound().getStatus() != sf::Sound::Playing)
			BurnSFX[rnd]->PlaySoundEffect();
	}
}

void Enemy::Knockback(float pForce)
{
	_speed = -pForce * 0.1f;
}

void Enemy::Heal(int pHealth)
{
	_health += pHealth;

	if (_health > _baseHealth)
		_health = _baseHealth;
}

void Enemy::TakeDamage(int pDamage)
{
	float percentage = 1.0f - (float(pDamage) / float(_health));
	_health -= pDamage;

	_healthBar->scale(glm::vec3(1, 1, percentage));
	_healthBarTimer = clock();
	_shouldShowHealthBar = true;
	if (_health > 0) return;
	GameController::GridManager->_currentMoney += KillValue;
	Kill();
}

void Enemy::speedUp(float pSpeedUpPercent)
{
	_speedUp += pSpeedUpPercent;
}

void Enemy::slowDown(float pSlowDownPercent)
{
	_slowDown += pSlowDownPercent;
	if (_slowDown > 100)
		_slowDown = 100;
	if (_slowDown < 0)
		_slowDown = 0;
}

void Enemy::setSlowDown(float pSlowDownPercent)
{
	if (this == nullptr) return;
	_slowDown = pSlowDownPercent;
}

float Enemy::getSpeed()
{
	if (_speed > 0)
		return _speed * (1 + (_speedUp * 0.01f - _slowDown * 0.01f));
	else
		return _speed;
}

int Enemy::getSize()
{
	return _size;
}
