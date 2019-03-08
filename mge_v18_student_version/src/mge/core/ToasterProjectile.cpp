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
AbstractMaterial* ToasterProjectile::Material;

ToasterProjectile::ToasterProjectile(glm::mat4 pTransform) : GameObject("ToasterProjectile")
{
	_tag = "toasterProjectile";

	_ignoreTags.push_back(_tag);
	_ignoreTags.push_back("tower");
	_ignoreTags.push_back("honeyProjectile");

	CollisionBehaviour* colBehaviour = new CollisionBehaviour(1, true);
	addBehaviour(colBehaviour);
	if (GameController::DrawColliders)
		colBehaviour->DrawCollider();

	setTransform(pTransform);

	addBehaviour(new ToasterProjectileBehaviour());
	setMesh(Mesh);
	setMaterial(Material);

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
	glm::vec3 diff = _spawnPos - getLocalPosition();
	if (diff.x * diff.x + diff.y * diff.y + diff.z * diff.z > (GameController::ToasterRange * GameController::ToasterRange) * 3)
	{
		Kill();
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

void ToasterProjectile::Shoot()
{
	_isShooting = true;
}