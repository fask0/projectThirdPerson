#pragma once

#include <iostream>
#include <vector>
#include <time.h>

#include "glm.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/core/Waypoint.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/SoundEffects.hpp"

class Enemy : public GameObject
{
	public:
	static std::vector<SoundEffect*> CutSFX;
	static std::vector<SoundEffect*> BurnSFX;
	static std::vector<SoundEffect*> FreezeSFX;
	static std::vector<SoundEffect*> HoneySlowSFX;
	Enemy(
		std::string pName = "Enemy",
		glm::vec3 pPosition = glm::vec3(0, 0, 0),
		Waypoint::Lane pLane = Waypoint::A,
		std::string pTag = "enemy");
	~Enemy();

	virtual void update(float pStep) override;

	void OnCollisionEnter(GameObject* pOther) override;

	void Knockback(float pForce);
	void Heal(int pHealth);
	void TakeDamage(int pDamage);

	void speedUp(float pSpeedUpPercent);
	void slowDown(float pSlowDownPercent);
	void setSlowDown(float pSlowDownPercent);
	float getSpeed();
	int getSize();
	int getDamage() { return _damage; }

	int KillValue = 3;

	protected:
	std::vector<SoundEffect*> _deathSFX;
	Waypoint::Lane _lane;
	int _size;
	int _health;
	int _baseHealth;
	int _healthRegen;
	int _damage;
	float _speed;
	int _effectRecovery;

	float _baseSpeed;
	int _speedUp;
	int _slowDown;

	std::vector<Mesh*> _animation;
	int _currentFrame;
	time_t _timer;
};