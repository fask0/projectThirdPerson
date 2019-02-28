#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/core/Enemy.hpp"

class EffectBehaviour : public AbstractBehaviour
{
	public:
	enum Effect
	{
		SpeedUp,
		SlowDown,
		HealOverTime,
		DamageOverTime
	};

	EffectBehaviour(Effect pEffectType, int pPotency, int pDuration);
	~EffectBehaviour();

	virtual void update(float pStep);

	private:
	Effect _effect;
	Enemy* _enemyOwner;

	int _effectPotency;
	int _duration;
	int _timeElapsed;

	bool _isOwnerAffected;

	void speedUp();
	void slowDown();
	void heal();
	void damage();
};