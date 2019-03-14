#include "mge/core/SniperTowerProjectile.hpp"
#include "mge/core/GameObject.hpp"

#include "glm.hpp"

Mesh* SniperTowerProjectile::Mesh;
LitTextureMaterial* SniperTowerProjectile::Material;

SniperTowerProjectile::SniperTowerProjectile(glm::vec3 pPosition, GameObject * pTarget)
	: GameObject("SniperTowerProjectile", pPosition)
{
	_speed = 100;
	setMesh(Mesh);
	setMaterial(Material);
	_targetPos = new GameObject("pos", pTarget->getLocalPosition());
	_dist = _targetPos->getLocalPosition() - getLocalPosition();
	_dir = glm::normalize(_dist);
}

SniperTowerProjectile::~SniperTowerProjectile()
{
	delete _targetPos;
}

void SniperTowerProjectile::update(float pStep)
{
	_dist = _targetPos->getLocalPosition() - getLocalPosition();
	setLocalPosition(getLocalPosition() + _dir * pStep * _speed);
	if (glm::abs(_dist.x) <= pStep * _speed &&
		glm::abs(_dist.z) <= pStep * _speed)
	{
		Kill();
	}

	GameObject::update(pStep);
}
