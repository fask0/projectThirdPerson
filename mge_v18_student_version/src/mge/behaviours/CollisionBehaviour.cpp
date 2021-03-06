#include "mge/behaviours/CollisionBehaviour.hpp"
#include "mge/core/CollisionManager.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include <iostream>
#include <vector>
#include <string>

Mesh* CollisionBehaviour::BoxMesh;
Mesh* CollisionBehaviour::SphereMesh;

CollisionBehaviour::CollisionBehaviour(EntityRelation pRelation, glm::vec3 pBoundaries, bool pIsTrigger, glm::vec3 pOffset)
	: AbstractBehaviour()
{
	if (pRelation == EntityRelation::Tower)
		CollisionManager::towerCollisions.push_back(this);
	else
		CollisionManager::projectileCollisions.push_back(this);

	entityRelation = pRelation;
	colliderType = BoxCollider;
	_boundaries = pBoundaries;
	isTrigger = pIsTrigger;

	_collider = new GameObject("col", pOffset);
	_material = new ColorMaterial(glm::vec4(0, 1, 0, 0.25f));
	_mesh = BoxMesh;
}

CollisionBehaviour::CollisionBehaviour(EntityRelation pRelation, float pRadius, bool pIsTrigger, glm::vec3 pOffset)
	: AbstractBehaviour()
{
	if (pRelation == EntityRelation::Tower)
		CollisionManager::towerCollisions.push_back(this);
	else
		CollisionManager::projectileCollisions.push_back(this);
	entityRelation = pRelation;
	colliderType = SphereCollider;
	_radius = pRadius;
	isTrigger = pIsTrigger;

	_collider = new GameObject("col", pOffset);
	_material = new ColorMaterial(glm::vec4(0, 1, 0, 0.25f));
	_mesh = SphereMesh;
}

CollisionBehaviour::~CollisionBehaviour()
{
	if (entityRelation == EntityRelation::Tower)
	{
		for (int i = 0; i < CollisionManager::towerCollisions.size(); i++)
		{
			if (CollisionManager::towerCollisions[i] == this)
			{
				CollisionManager::towerCollisions.erase(CollisionManager::towerCollisions.begin() + i);
				for (int j = 0; j < _behavioursInCollision.size(); ++j)
				{
					for (int k = 0; k < _behavioursInCollision[j]->_behavioursInCollision.size(); ++k)
					{
						if (_behavioursInCollision[j]->_behavioursInCollision[k] == this)
						{
							_behavioursInCollision[j]->_behavioursInCollision.erase(_behavioursInCollision[j]->_behavioursInCollision.begin() + k);
						}
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < CollisionManager::projectileCollisions.size(); i++)
		{
			if (CollisionManager::projectileCollisions[i] == this)
			{
				CollisionManager::projectileCollisions.erase(CollisionManager::projectileCollisions.begin() + i);
				for (int j = 0; j < _behavioursInCollision.size(); ++j)
				{
					for (int k = 0; k < _behavioursInCollision[j]->_behavioursInCollision.size(); ++k)
					{
						if (_behavioursInCollision[j]->_behavioursInCollision[k] == this)
						{
							_behavioursInCollision[j]->_behavioursInCollision.erase(_behavioursInCollision[j]->_behavioursInCollision.begin() + k);
						}
					}
				}
			}
		}
	}

	_collider = nullptr;
	_material = nullptr;
	_mesh = nullptr;
}

void CollisionBehaviour::update(float pStep)
{
	if (_behavioursInCollision.size() == 0)
		_owner->isColliding = false;
	else
		_owner->isColliding = true;
}

void CollisionBehaviour::ResolveCollision(CollisionBehaviour* pOtherCollider, GameObject* pOtherOwner, glm::vec3 pLastPos)
{
	switch (colliderType)
	{
	case BoxCollider:
	{
		if (!checkCollision(pOtherCollider))
			_owner->OnCollisionEnter(pOtherOwner);
		if (_owner == NULL)
			_owner->OnCollisionStay(pOtherOwner);

		if (_owner == NULL || isTrigger || pOtherCollider->isTrigger) return;

		_owner->setLocalPosition(pLastPos);
	}
	break;

	case SphereCollider:
	{
		if (!checkCollision(pOtherCollider))
			_owner->OnCollisionEnter(pOtherOwner);
		if (_owner == NULL)
			_owner->OnCollisionStay(pOtherOwner);

		if (_owner == NULL || isTrigger || pOtherCollider->isTrigger) return;

		_owner->setLocalPosition(pLastPos);
	}
	break;
	}
}

glm::vec3 CollisionBehaviour::GetPosition()
{
	return _owner->getWorldPosition();
}

glm::vec3 CollisionBehaviour::GetMax()
{
	return (_boundaries * 0.5f) + _owner->getWorldPosition();
}

glm::vec3 CollisionBehaviour::GetMin()
{
	return (-_boundaries * 0.5f) + _owner->getWorldPosition();
}

float CollisionBehaviour::GetRadius()
{
	return _radius;
}

void CollisionBehaviour::ScaleCollider(float pScaler)
{
	_boundaries *= pScaler;
	_radius *= pScaler;
}

void CollisionBehaviour::DrawCollider()
{
	switch (colliderType)
	{
	case CollisionBehaviour::BoxCollider:
	{
		_collider->scale(_boundaries * 0.5f);
	}
	break;

	case CollisionBehaviour::SphereCollider:
	{
		_collider->scale(glm::vec3(1, 1, 1) * _radius);
	}
	break;
	}

	_collider->setMesh(_mesh);
	_collider->setMaterial(_material);
	_owner->add(_collider);
}

std::vector<CollisionBehaviour*> CollisionBehaviour::getCollisions()
{
	return _behavioursInCollision;
}

bool CollisionBehaviour::checkCollision(CollisionBehaviour* pOther)
{
	if (_behavioursInCollision.size() == 0) return false;

	for (int i = 0; i < _behavioursInCollision.size(); ++i)
	{
		if (_behavioursInCollision[i] == pOther)
		{
			return true;
		}
	}
	return false;
}

void CollisionBehaviour::removeCollision(CollisionBehaviour* pOther)
{
	if (_behavioursInCollision.size() == 0) return;

	for (int i = 0; i < _behavioursInCollision.size(); ++i)
	{
		if (_behavioursInCollision[i] == pOther)
		{
			_behavioursInCollision.erase(_behavioursInCollision.begin() + i);
			return;
		}
	}
}
