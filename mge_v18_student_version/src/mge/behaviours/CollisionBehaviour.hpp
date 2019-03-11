#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/core/Mesh.hpp"
#include "glm.hpp"
#include <iostream>
#include <vector>

class CollisionBehaviour : public AbstractBehaviour
{
public:
	enum ColliderType
	{
		BoxCollider,
		SphereCollider
	};
	enum EntityRelation
	{
		Projectile,
		Tower
	};

	static Mesh* BoxMesh;
	static Mesh* SphereMesh;

	CollisionBehaviour(EntityRelation pRelation, glm::vec3 pBoundaries, bool pIsTrigger = false, glm::vec3 pOffset = glm::vec3(0, 0, 0));
	CollisionBehaviour(EntityRelation pRelation, float pRadius, bool pIsTrigger = false, glm::vec3 pOffset = glm::vec3(0, 0, 0));
	virtual ~CollisionBehaviour();
	virtual void update(float pStep);

	glm::vec3 GetPosition();
	glm::vec3 GetMax();
	glm::vec3 GetMin();

	float GetRadius();

	void ScaleCollider(float pScaler);
	void ResolveCollision(CollisionBehaviour* pOtherCollider, GameObject* pOtherOwner, glm::vec3 pLastPos);
	void DrawCollider();

	bool isTrigger;
	ColliderType colliderType;
	EntityRelation entityRelation;

	std::vector<CollisionBehaviour*> getCollisions();
	bool checkCollision(CollisionBehaviour* pOther);
	void removeCollision(CollisionBehaviour* pOther);
	std::vector<CollisionBehaviour*> _behavioursInCollision;

protected:
	glm::vec3 _boundaries;
	float _radius;
	GameObject* _collider;
	AbstractMaterial* _material;
	Mesh* _mesh;
};