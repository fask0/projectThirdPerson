#include <memory>
#include <vector>

#include "mge/core/MagnifyingGlassTower.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/MagnifyingGlassTowerBehaviour.hpp"
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"
#include "mge/behaviours/CollisionBehaviour.hpp"
#include "mge/behaviours/EffectBehaviour.hpp"
#include "mge/core/SoundEffects.hpp"
#include "mge/materials/LitTextureMaterial.hpp"

Mesh* MagnifyingGlassTower::Mesh;
AbstractMaterial* MagnifyingGlassTower::Material;
std::vector<SoundEffect*> MagnifyingGlassTower::SFX;

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
}

void MagnifyingGlassTower::update(float pStep)
{
	//rayCast();

	GameObject::update(pStep);
}

void MagnifyingGlassTower::AddTowerBehaviour()
{
	MagnifyingGlassHitBox* hitBox = new MagnifyingGlassHitBox();
	hitBox->setLocalPosition(glm::vec3(0, 0.2f, -3.2));
	this->add(hitBox);
}

///MAGNIFYING GLASS HIT BOX
std::vector<Mesh*> MagnifyingGlassHitBox::Animations;
LitTextureMaterial* MagnifyingGlassHitBox::Material;

MagnifyingGlassHitBox::MagnifyingGlassHitBox() : GameObject("MagnifyingGlassHitBox")
{
	_tag = "magnifyingGlassHitBox";
	_ignoreTags.push_back(_tag);
	_ignoreTags.push_back("honeyProjectile");
	_ignoreTags.push_back("iceProjectile");
	_ignoreTags.push_back("toasterProjectile");

	CollisionBehaviour* behaviour = new CollisionBehaviour(CollisionBehaviour::Projectile, 2, true);
	addBehaviour(behaviour);
	if (GameController::DrawColliders)
		behaviour->DrawCollider();
	setMaterial(Material);
}

MagnifyingGlassHitBox::~MagnifyingGlassHitBox()
{
}

void MagnifyingGlassHitBox::update(float pStep)
{
	GameObject::update(pStep);

	if (_shouldDie) return;
	if (_objectsInRange.size() > 0)
	{
		if (_material == nullptr)
			setMaterial(Material);

		if (clock() >= _timer + 0.075f * CLOCKS_PER_SEC)
		{
			if (!_goBack)
			{
				setMesh(Animations[_currentFrame]);
				_currentFrame++;
				if (_currentFrame == Animations.size())
				{
					_currentFrame--;
					_goBack = true;
				}
			}
			else
			{
				setMesh(Animations[_currentFrame]);
				_currentFrame--;
				if (_currentFrame == -1)
				{
					_currentFrame++;
					_goBack = false;
				}
			}
			_timer = clock();
		}
	}
	else
	{
		removeMaterial();
	}
}

void MagnifyingGlassHitBox::OnCollisionEnter(GameObject * pOther)
{
	if (dynamic_cast<Enemy*>(pOther))
	{
		_objectsInRange.push_back(pOther);
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
			pOther->addBehaviour(
				new EffectBehaviour(EffectBehaviour::Effect::DamageOverTime,
									GameController::MagnifyingFireDamage,
									GameController::MagnifyingFireDuration,
									GameController::MagnifyingFireRate));
	}
}

void MagnifyingGlassHitBox::OnCollisionExit(GameObject * pOther)
{
	if (dynamic_cast<Enemy*>(pOther))
		for (int i = 0; i < _objectsInRange.size(); ++i)
			if (pOther == _objectsInRange[i])
				_objectsInRange.erase(_objectsInRange.begin() + i);
}

bool MagnifyingGlassHitBox::SkipCollisionCheck()
{
	return false;
}
