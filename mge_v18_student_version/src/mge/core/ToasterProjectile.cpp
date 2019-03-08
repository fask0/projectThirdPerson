#include "glm.hpp"
#include "mge/core/ToasterProjectile.hpp"
#include "mge/behaviours/ToasterProjectileBehaviour.hpp"
#include "mge/behaviours/CollisionBehaviour.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/GameController.hpp"
#include "mge/config.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include <time.h>

Mesh* ToasterProjectile::Mesh;
Texture* ToasterProjectile::Texture;

ToasterProjectile::ToasterProjectile(glm::mat4 pTransform) : GameObject("ToasterProjectile")
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

	addBehaviour(new ToasterProjectileBehaviour());
	setMesh(Mesh);
	setMaterial(new LitTextureMaterial(Texture));

	_spawnTime = clock();
	_spawnPos = getLocalPosition();
	_isShooting = false;
}

ToasterProjectile::~ToasterProjectile()
{
	//dtor
	GameObject::~GameObject();
}

void ToasterProjectile::update(float pStep)
{
	if (!_isShooting) return;
	//rayCast();
	GameObject::update(pStep);

	if (_shouldDie) return;
	if (clock() >= _spawnTime + 3 * CLOCKS_PER_SEC)
	{
		delete(this);
	}
}

void ToasterProjectile::OnCollisionEnter(GameObject * pOther)
{
	if (dynamic_cast<Enemy*>(pOther))
	{
		dynamic_cast<Enemy*>(pOther)->TakeDamage(GameController::ToasterDamage);
	}
	Kill();
}

bool ToasterProjectile::SkipCollisionCheck()
{
	return false;
}

void ToasterProjectile::Shoot()
{
	_isShooting = true;
}