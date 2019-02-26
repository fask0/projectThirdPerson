#include "glm.hpp"
#include "mge/core/ToasterProjectile.hpp"
#include "mge/behaviours/ToasterProjectileBehaviour.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"
#include "mge/config.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include <time.h>

Mesh* ToasterProjectile::Mesh;
AbstractMaterial* ToasterProjectile::Material;

ToasterProjectile::ToasterProjectile(glm::mat4 pTransform) : GameObject("ToasterProjectile")
{
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

	if (float(clock() - _spawnTime) / CLOCKS_PER_SEC >= 3)
	{
		removeAllBehaviours();
		_parent->remove(this);
		delete(this);
	}
}