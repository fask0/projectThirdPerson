#include "mge/core/MagnifyingGlassTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/MagnifyingGlassTowerBehaviour.hpp"
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"
#include "mge/behaviours/CollisionBehaviour.hpp"
#include "mge/behaviours/EffectBehaviour.hpp"

Mesh* MagnifyingGlassTower::Mesh;
AbstractMaterial* MagnifyingGlassTower::Material;

MagnifyingGlassTower::MagnifyingGlassTower() : Tower("Magnifying Glass Tower")
{
	_range = GameController::MagnifyingRange;
	_attSpeed = 0;
	_cost = GameController::MagnifyingCost;
	_material = new LitDynamicTextureGridMaterial(GameController::Lights[0], true);
_tag = "magnifyingGlassTower";
}

MagnifyingGlassTower::~MagnifyingGlassTower()
{
	//dtor
	Tower::~Tower();
}

void MagnifyingGlassTower::update(float pStep)
{
	//rayCast();

	GameObject::update(pStep);
}

void MagnifyingGlassTower::AddTowerBehaviour()
{
	//addBehaviour(new MagnifyingGlassTowerBehaviour());
	CollisionBehaviour* behaviour = new CollisionBehaviour(glm::vec3(5, 1, 1), true, glm::vec3(5, 0, 0));
	addBehaviour(behaviour);
	if (GameController::DrawColliders)
		behaviour->DrawCollider();
}

void MagnifyingGlassTower::OnCollisionEnter(GameObject* pOther)
{
	if (dynamic_cast<Enemy*>(pOther))
	{
		bool hasEffectBehaviour = false;
		for each (AbstractBehaviour* behaviour in pOther->getBehaviours())
		{
			if (dynamic_cast<EffectBehaviour*>(behaviour))
			{
				if (dynamic_cast<EffectBehaviour*>(behaviour)->_effect == EffectBehaviour::DamageOverTime)
				{
					hasEffectBehaviour = true;
					break;
				}
			}
		}
		if (!hasEffectBehaviour)
			pOther->addBehaviour(new EffectBehaviour(EffectBehaviour::Effect::DamageOverTime, GameController::MagnifyingFireDamage, GameController::MagnifyingFireDuration, GameController::MagnifyingFireRate));
	}
}
