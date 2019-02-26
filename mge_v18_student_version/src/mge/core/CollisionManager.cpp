#include <iostream>
#include <vector>

#include "mge/core/CollisionManager.hpp"

#include "glm.hpp"

std::vector<CollisionBehaviour*> CollisionManager::collisionBehaviours;

CollisionManager::CollisionManager(const std::string& pName, const glm::vec3& pPosition)
	: GameObject(pName, pPosition)
{
	collisionBehaviours.clear();
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::update(float pStep)
{
	//Detect Collision
	if (collisionBehaviours.size() <= 0) return;

	CollisionBehaviour* collider;
	CollisionBehaviour* other;

	for (int i = 0; i < collisionBehaviours.size();++i)
	{
		collider = collisionBehaviours[i];

		for (int j = i + 1;j < collisionBehaviours.size();++j)
		{
			other = collisionBehaviours[j];

			switch (collider->colliderType)
			{
				case CollisionBehaviour::BoxCollider:
				{
					switch (other->colliderType)
					{
						case CollisionBehaviour::BoxCollider:
						{
							if ((collider->GetMax().x >= other->GetMin().x && collider->GetMin().x <= other->GetMax().x) &&
								(collider->GetMax().y >= other->GetMin().y && collider->GetMin().y <= other->GetMax().y) &&
								(collider->GetMax().z >= other->GetMin().z && collider->GetMin().z <= other->GetMax().z))
							{
								collider->ResolveCollision(other, other->getOwner(), collider->getOwner()->getLastPosition());

								if (!collider->checkCollision(other))
									collider->getCollisions()->push_back(other);
								if (!other->checkCollision(collider))
									other->getCollisions()->push_back(collider);
							}
							else if (collider->checkCollision(other))
							{
								collider->getOwner()->OnCollisionExit(other->getOwner());
								collider->removeCollision(other);
								if (other->checkCollision(collider))
									other->removeCollision(collider);
							}
						}
						break;

						case CollisionBehaviour::SphereCollider:
						{
							float x = glm::max(collider->GetMin().x, glm::min(other->GetPosition().x, collider->GetMax().x));
							float y = glm::max(collider->GetMin().y, glm::min(other->GetPosition().y, collider->GetMax().y));
							float z = glm::max(collider->GetMin().z, glm::min(other->GetPosition().z, collider->GetMax().z));

							float distance = glm::sqrt(
								(x - other->GetPosition().x) * (x - other->GetPosition().x) +
								(y - other->GetPosition().y) * (y - other->GetPosition().y) +
								(z - other->GetPosition().z) * (z - other->GetPosition().z));

							if (distance <= other->GetRadius())
							{
								collider->ResolveCollision(other, other->getOwner(), collider->getOwner()->getLastPosition());

								if (!collider->checkCollision(other))
									collider->getCollisions()->push_back(other);
								if (!other->checkCollision(collider))
									other->getCollisions()->push_back(collider);
							}
							else if (collider->checkCollision(other))
							{
								collider->getOwner()->OnCollisionExit(other->getOwner());
								collider->removeCollision(other);
								if (other->checkCollision(collider))
									other->removeCollision(collider);
							}
						}
						break;
					}
				}
				break;

				case CollisionBehaviour::SphereCollider:
				{
					switch (other->colliderType)
					{
						case CollisionBehaviour::BoxCollider:
						{
							float x = glm::max(other->GetMin().x, glm::min(collider->GetPosition().x, other->GetMax().x));
							float y = glm::max(other->GetMin().y, glm::min(collider->GetPosition().y, other->GetMax().y));
							float z = glm::max(other->GetMin().z, glm::min(collider->GetPosition().z, other->GetMax().z));

							float distance = glm::sqrt(
								(x - collider->GetPosition().x) * (x - collider->GetPosition().x) +
								(y - collider->GetPosition().y) * (y - collider->GetPosition().y) +
								(z - collider->GetPosition().z) * (z - collider->GetPosition().z));

							if (distance <= collider->GetRadius())
							{
								collider->ResolveCollision(other, other->getOwner(), collider->getOwner()->getLastPosition());

								if (!collider->checkCollision(other))
									collider->getCollisions()->push_back(other);
								if (!other->checkCollision(collider))
									other->getCollisions()->push_back(collider);
							}
							else if (collider->checkCollision(other))
							{
								collider->getOwner()->OnCollisionExit(other->getOwner());
								collider->removeCollision(other);
								if (other->checkCollision(collider))
									other->removeCollision(collider);
							}
						}
						break;

						case CollisionBehaviour::SphereCollider:
						{
							float distance = glm::sqrt(
								(collider->GetPosition().x - other->GetPosition().x) * (collider->GetPosition().x - other->GetPosition().x) +
								(collider->GetPosition().y - other->GetPosition().y) * (collider->GetPosition().y - other->GetPosition().y) +
								(collider->GetPosition().z - other->GetPosition().z) * (collider->GetPosition().z - other->GetPosition().z));

							if (distance <= collider->GetRadius() + other->GetRadius())
							{
								collider->ResolveCollision(other, other->getOwner(), collider->getOwner()->getLastPosition());

								if (!collider->checkCollision(other))
									collider->getCollisions()->push_back(other);
								if (!other->checkCollision(collider))
									other->getCollisions()->push_back(collider);
							}
							else if (collider->checkCollision(other))
							{
								collider->getOwner()->OnCollisionExit(other->getOwner());
								collider->removeCollision(other);
								if (other->checkCollision(collider))
									other->removeCollision(collider);
							}
						}
						break;
					}
				}
				break;
			}
		}
	}
}
