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
	if (glm::vec3(_spawnPos - getLocalPosition()).length() > GameController::ToasterRange)
	{
		delete(this);
	}
}

void ToasterProjectile::OnCollisionEnter(GameObject * pOther)
{
	Kill();
}

void ToasterProjectile::Shoot()
{
	_isShooting = true;
}