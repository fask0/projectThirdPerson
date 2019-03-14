#include <iostream>
#include <vector>
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

std::vector<Mesh*> HoneyProjectile::Animation;
LitTextureMaterial* HoneyProjectile::Material;

HoneyProjectile::HoneyProjectile(glm::mat4 pTransform, float pDiff) : GameObject("HoneyProjectile")
{
	_tag = "honeyProjectile";
	_ignoreTags.push_back(_tag);
	_ignoreTags.push_back("toasterProjectile");
	_ignoreTags.push_back("iceProjectile");
	_ignoreTags.push_back("magnifyingGlassHitBox");

	setTransform(pTransform);

	addBehaviour(new HoneyProjectileBehaviour(pDiff));
	setMesh(Animation[0]);
	setMaterial(Material);

	_spawnTime = clock();
	_spawnPos = getLocalPosition();
}

HoneyProjectile::~HoneyProjectile()
{
	//dtor
}

void HoneyProjectile::update(float pStep)
{
	//rayCast();
	GameObject::update(pStep);
	if (_shouldDie) return;
	if (_shouldAnimate && _currentFrame < Animation.size())
	{
		if (clock() >= _timer + 0.05f * CLOCKS_PER_SEC)
		{
			setMesh(Animation[_currentFrame]);
			_currentFrame++;
			_timer = clock();
		}
	}

	if (clock() > _spawnTime + (5 * CLOCKS_PER_SEC))
	{
		for each (Enemy* enemy in enemiesCollidingWith)
		{
			if (enemy != nullptr)
				enemy->setSlowDown(0);
		}
		enemiesCollidingWith.clear();
		Kill();
	}
}

void HoneyProjectile::OnCollisionEnter(GameObject * pOther)
{
	if (pOther == nullptr) return;
	dynamic_cast<Enemy*>(pOther)->setSlowDown(50);
	enemiesCollidingWith.push_back(dynamic_cast<Enemy*>(pOther));
}

void HoneyProjectile::OnCollisionExit(GameObject * pOther)
{
	if (pOther == nullptr) return;
	dynamic_cast<Enemy*>(pOther)->setSlowDown(0);
	if (enemiesCollidingWith.size() != 0)
		enemiesCollidingWith.erase(enemiesCollidingWith.begin());
}

bool HoneyProjectile::SkipCollisionCheck()
{
	return false;
}
