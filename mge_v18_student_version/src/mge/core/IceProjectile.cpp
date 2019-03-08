#include "glm.hpp"
#include "mge/core/IceProjectile.hpp"
#include "mge/behaviours/IceProjectileBehaviour.hpp"
#include "mge/behaviours/CollisionBehaviour.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/GameController.hpp"
#include "mge/config.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/behaviours/EffectBehaviour.hpp"
#include <time.h>

Mesh* IceProjectile::Mesh;
Texture* IceProjectile::Texture;

IceProjectile::IceProjectile(glm::mat4 pTransform) : GameObject("IceProjectile")
{
	_tag = "projectile";

	_ignoreTags.push_back(_tag);
	_ignoreTags.push_back("tower");
	_ignoreTags.push_back("emptyCollider");

	CollisionBehaviour* colBehaviour = new CollisionBehaviour(1, true);
	addBehaviour(colBehaviour);
	if (GameController::DrawColliders)
		colBehaviour->DrawCollider();

	setTransform(pTransform);

	addBehaviour(new IceProjectileBehaviour());
	setMesh(Mesh);
	setMaterial(new LitTextureMaterial(Texture));

	_spawnTime = clock();
	_spawnPos = getLocalPosition();
}

IceProjectile::~IceProjectile()
{
	//dtor
	GameObject::~GameObject();
}

void IceProjectile::update(float pStep)
{
	//rayCast();
	GameObject::update(pStep);

	if (_shouldDie) return;
	if (clock() >= _spawnTime + 1 * CLOCKS_PER_SEC)
	{
		delete(this);
	}
}

void IceProjectile::OnCollisionEnter(GameObject * pOther)
{
	if (!_hasHitEnemy)
	{
		if (dynamic_cast<Enemy*>(pOther))
		{
			pOther->addBehaviour(new EffectBehaviour(EffectBehaviour::Effect::SlowDown, 100, GameController::IceFreezeTime));
			dynamic_cast<Enemy*>(pOther)->TakeDamage(GameController::IceDamage);
		}
		Kill();
		_hasHitEnemy = true;
	}
}

bool IceProjectile::SkipCollisionCheck()
{
	return false;
}
