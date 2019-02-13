#ifndef COLLISIONBEHAVIOUR_HPP
#define COLLISIONBEHAVIOUR_HPP

#include <iostream>
#include <vector>

#include "mge/core/Mesh.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"

#include "mge/behaviours/AbstractBehaviour.hpp"

#include "glm.hpp"

class CollisionBehaviour : public AbstractBehaviour
{
	public:
	enum ColliderType
	{
		BoxCollider,
		SphereCollider
	};

	CollisionBehaviour(glm::vec3 pBoundaries);
	CollisionBehaviour(float pRadius);
	virtual ~CollisionBehaviour();
	virtual void update(float pStep);

	glm::vec3 GetPosition();
	glm::vec3 GetMax();
	glm::vec3 GetMin();

	float GetRadius();

	void ScaleCollider(float pScaler);
	void ResolveCollision(std::string pOtherName);
	void DrawCollider();

	bool isTrigger;
	ColliderType colliderType;

	protected:
	glm::vec3 _boundaries;
	float _radius;
	GameObject* _collider;
	AbstractMaterial* _material;
	Mesh* _mesh;
};

#endif // !COLLISIONBEHAVIOUR_HPP