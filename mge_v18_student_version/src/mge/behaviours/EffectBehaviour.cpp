#include <iostream>
#include <time.h>

#include "mge/behaviours/EffectBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Enemy.hpp"

EffectBehaviour::EffectBehaviour(Effect pEffectType, int pPotency, int pDuration)
	: AbstractBehaviour(), _effect(pEffectType), _effectPotency(pPotency), _duration(pDuration)
{
	_timeElapsed = 0;
	_isOwnerAffected = false;
}

EffectBehaviour::~EffectBehaviour()
{
	_enemyOwner = nullptr;
}

void EffectBehaviour::update(float pStep)
{
	switch (_effect)
	{
		case EffectBehaviour::SpeedUp:
		speedUp();
		break;
		case EffectBehaviour::SlowDown:
		slowDown();
		break;
		case EffectBehaviour::HealOverTime:
		heal();
		break;
		case EffectBehaviour::DamageOverTime:
		damage();
		break;
	}
}

void EffectBehaviour::speedUp()
{
	if (!_isOwnerAffected)
	{
		dynamic_cast<Enemy*>(_owner)->speedUp(_effectPotency);
		_isOwnerAffected = true;
	}

	if (clock() >= _timeElapsed + _duration * CLOCKS_PER_SEC)
	{
		dynamic_cast<Enemy*>(_owner)->speedUp(-_effectPotency);
		_owner->removeBehaviour(this);
	}
}

void EffectBehaviour::slowDown()
{
	if (!_isOwnerAffected)
	{
		dynamic_cast<Enemy*>(_owner)->slowDown(_effectPotency);
		_isOwnerAffected = true;
	}

	if (clock() >= _timeElapsed + _duration * CLOCKS_PER_SEC)
	{
		dynamic_cast<Enemy*>(_owner)->slowDown(-_effectPotency);
		_owner->removeBehaviour(this);
	}
}

void EffectBehaviour::heal()
{
	if (clock() >= _timeElapsed + CLOCKS_PER_SEC)
	{
		dynamic_cast<Enemy*>(_owner)->Heal(_effectPotency);
		_timeElapsed = clock();
		_duration--;

		if (_duration == 0)
			_owner->removeBehaviour(this);
	}
}

void EffectBehaviour::damage()
{
	if (clock() >= _timeElapsed + CLOCKS_PER_SEC)
	{
		dynamic_cast<Enemy*>(_owner)->TakeDamage(_effectPotency);
		_timeElapsed = clock();
		_duration--;

		if (_duration == 0)
			_owner->removeBehaviour(this);
	}
}
