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
AbstractMaterial* IceProjectile::Material;

IceProjectile::IceProjectile(glm::mat4 pTransform) : GameObject("IceProjectile")
{
	_tag = "iceProjectile";

	_ignoreTags.push_back(_tag);
	_ignoreTags.push_back("tower");
	_ignoreTags.push_back("honeyProjectile");
	_ignoreTags.push_back("toasterProjectile");

	CollisionBehaviour* colBehaviour = new CollisionBehaviour(1, true);
	addBehaviour(colBehaviour);
	if (GameController::DrawColliders)
		colBehaviour->DrawCollider();

	setTransform(pTransform);

	addBehaviour(new IceProjectileBehaviour());
	setMesh(Mesh);
	setMaterial(Material);

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
	glm::vec3 diff = _spawnPos - getLocalPosition();
	if (diff.x * diff.x + diff.y * diff.y + diff.z * diff.z > (GameController::IceRange * GameController::IceRange) * 3)
	{
		Kill();
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