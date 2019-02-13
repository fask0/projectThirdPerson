#include <iostream>
#include <vector>
#include <string>

#include "mge/core/Mesh.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"

#include "mge/behaviours/CollisionBehaviour.hpp"

#include "mge/core/CollisionManager.hpp"

#include "mge/config.hpp"

CollisionBehaviour::CollisionBehaviour(glm::vec3 pBoundaries)
	: AbstractBehaviour()
{
	CollisionManager::_collisionBehaviours.push_back(this);
	colliderType = BoxCollider;
	_boundaries = pBoundaries;

	_collider = new GameObject("col");
	_material = new ColorMaterial(glm::vec4(0, 1, 0, 0.25f));
	_mesh = Mesh::load(config::MGE_MODEL_PATH + "cube_smooth.obj");
}

CollisionBehaviour::CollisionBehaviour(float pRadius)
	: AbstractBehaviour()
{
	CollisionManager::_collisionBehaviours.push_back(this);
	colliderType = SphereCollider;
	_radius = pRadius;

	_collider = new GameObject("col");
	_material = new ColorMaterial(glm::vec4(0, 1, 0, 0.25f));
	_mesh = Mesh::load(config::MGE_MODEL_PATH + "sphere4.obj");
}

CollisionBehaviour::~CollisionBehaviour()
{
	for (unsigned i = 0; i < CollisionManager::_collisionBehaviours.size(); i++)
	{
		if (CollisionManager::_collisionBehaviours[i] == this)
		{
			CollisionManager::_collisionBehaviours.erase(CollisionManager::_collisionBehaviours.begin() + i);
			return;
		}
	}
}

void CollisionBehaviour::update(float pStep)
{
}

void CollisionBehaviour::ResolveCollision(std::string pOtherName)
{
	switch (colliderType)
	{
		case BoxCollider:
		{
			std::cout << "Object: " + _owner->getName() + " is colliding with " + pOtherName + "\n";
			_owner->OnCollisionStay(pOtherName);

		}
		break;

		case SphereCollider:
		{
			std::cout << "Object: " + _owner->getName() + " is colliding with " + pOtherName + "\n";
			_owner->OnCollisionStay(pOtherName);

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