#include "glm.hpp"
#include "mge/core/HoneyProjectile.hpp"
#include "mge/behaviours/HoneyProjectileBehaviour.hpp"
#include "mge/behaviours/CollisionBehaviour.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/GameController.hpp"
#include "mge/config.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/core/Enemy.hpp"
#include <time.h>

Mesh* HoneyProjectile::Mesh;
Texture* HoneyProjectile::Texture;

HoneyProjectile::HoneyProjectile(glm::mat4 pTransform, float pDiff) : GameObject("HoneyProjectile")
{
	_tag = "projectile";

	_ignoreTags.push_back(_tag);
	_ignoreTags.push_back("tower");
	_ignoreTags.push_back("emptyCollider");

	/*CollisionBehaviour* colBehaviour = new CollisionBehaviour(1, true);
	addBehaviour(colBehaviour);
	if (GameController::DrawColliders)
		colBehaviour->DrawCollider();*/

	setTransform(pTransform);

	addBehaviour(new HoneyProjectileBehaviour(pDiff));
	setMesh(Mesh);
	setMaterial(new LitTextureMaterial(Texture));

	_spawnTime = clock();
	_spawnPos = getLocalPosition();
}

HoneyProjectile::~HoneyProjectile()
{
	//dtor
	GameObject::~GameObject();
}

void HoneyProjectile::update(float pStep)
{
	//rayCast();
	GameObject::update(pStep);
	if (_shouldDie) return;
	if (clock() > _spawnTime + (5 * CLOCKS_PER_SEC))
	{
		for each (Enemy* enemy in enemiesCollidingWith)
		{
			enemy->setSlowDown(0);
		}
		enemiesCollidingWith.clear();
		Kill();
	}
}

void HoneyProjectile::OnCollisionEnter(GameObject * pOther)
{
	dynamic_cast<Enemy*>(pOther)->setSlowDown(50);
	enemiesCollidingWith.push_back(dynamic_cast<Enemy*>(pOther));
}

void HoneyProjectile::OnCollisionExit(GameObject * pOther)
{
	dynamic_cast<Enemy*>(pOther)->setSlowDown(0);
	enemiesCollidingWith.erase(enemiesCollidingWith.begin());
}

bool HoneyProjectile::SkipCollisionCheck()
{
	return false;
}
