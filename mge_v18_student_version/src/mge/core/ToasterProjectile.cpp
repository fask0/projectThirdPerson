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
}

ToasterProjectile::~ToasterProjectile()
{
	//dtor
	GameObject::~GameObject();
}

void ToasterProjectile::update(float pStep)
{
	//rayCast();
	GameObject::update(pStep);

	if (_shouldDie) return;
	if (float(clock() - _spawnTime) / CLOCKS_PER_SEC >= 3)
	{
		delete(this);
	}
}

void ToasterProjectile::OnCollisionEnter(GameObject * pOther)
{
	Kill();
}