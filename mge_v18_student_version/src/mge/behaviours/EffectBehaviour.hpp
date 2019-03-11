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

	EffectBehaviour(Effect pEffectType, int pPotency, int pDuration, float pDotRate = 1.0f);
	~EffectBehaviour();

	virtual void update(float pStep);
	Effect _effect;

private:
	Enemy* _enemyOwner;

	int _effectPotency;
	int _duration;
	int _timeElapsed;
	float _dotRate;

	bool _isOwnerAffected;

	void speedUp();
	void slowDown();
	void heal();
	void damage();
};