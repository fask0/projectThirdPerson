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
		GameObject* colOwner = collider->getOwner();

		glm::vec3 colliderMax = collider->GetMax();
		glm::vec3 colliderMin = collider->GetMin();
		glm::vec3 colliderPos = collider->GetPosition();

		switch (collider->colliderType)
		{
			case CollisionBehaviour::BoxCollider:
			{
				for (int j = i + 1; j < collisionBehaviours.size(); ++j)
				{
					other = collisionBehaviours[j];
					GameObject* oOwner = other->getOwner();

					if (oOwner->SkipCollisionCheck() ||
						colOwner->IgnoreCollision(oOwner) ||
						oOwner->IgnoreCollision(colOwner)) continue;

					switch (other->colliderType)
					{
						case CollisionBehaviour::BoxCollider:
						{
							glm::vec3 otherMax = other->GetMax();
							glm::vec3 otherMin = other->GetMin();

							if ((colliderMax.x >= otherMin.x && colliderMin.x <= otherMax.x) &&
								(colliderMax.y >= otherMin.y && colliderMin.y <= otherMax.y) &&
								(colliderMax.z >= otherMin.z && colliderMin.z <= otherMax.z))
							{
								collider->ResolveCollision(other, oOwner, colOwner->getLastPosition());
								other->ResolveCollision(collider, colOwner, oOwner->getLastPosition());

								if (!collider->checkCollision(other))
									collider->getCollisions()->push_back(other);
								if (!other->checkCollision(collider))
									other->getCollisions()->push_back(collider);
							}
							else if (collider->checkCollision(other))
							{
								colOwner->OnCollisionExit(oOwner);
								collider->removeCollision(other);

								oOwner->OnCollisionExit(colOwner);
								other->removeCollision(collider);
							}
						}
						break;

						case CollisionBehaviour::SphereCollider:
						{
							glm::vec3 oPos = other->GetPosition();

							float x = glm::max(colliderMin.x, glm::min(oPos.x, colliderMax.x));
							float y = glm::max(colliderMin.y, glm::min(oPos.y, colliderMax.y));
							float z = glm::max(colliderMin.z, glm::min(oPos.z, colliderMax.z));

							float distance = (
								(x - oPos.x) * (x - oPos.x) +
								(y - oPos.y) * (y - oPos.y) +
								(z - oPos.z) * (z - oPos.z));

							if (distance <= other->GetRadius() * other->GetRadius())
							{
								collider->ResolveCollision(other, oOwner, colOwner->getLastPosition());
								other->ResolveCollision(collider, colOwner, oOwner->getLastPosition());

								if (!collider->checkCollision(other))
									collider->getCollisions()->push_back(other);
								if (!other->checkCollision(collider))
									other->getCollisions()->push_back(collider);
							}
							else if (collider->checkCollision(other))
							{
								colOwner->OnCollisionExit(oOwner);
								collider->removeCollision(other);

								oOwner->OnCollisionExit(colOwner);
								other->removeCollision(collider);
							}
						}
						break;
					}
				}
			}
			break;

			case CollisionBehaviour::SphereCollider:
			{
				for (int j = i + 1;j < collisionBehaviours.size(); ++j)
				{
					other = collisionBehaviours[j];
					GameObject* oOwner = other->getOwner();

					if (oOwner->SkipCollisionCheck() ||
						colOwner->IgnoreCollision(oOwner) ||
						oOwner->IgnoreCollision(colOwner)) continue;

					switch (other->colliderType)
					{
						case CollisionBehaviour::BoxCollider:
						{
							glm::vec3 otherMax = other->GetMax();
							glm::vec3 otherMin = other->GetMin();

							float x = glm::max(otherMin.x, glm::min(colliderPos.x, otherMax.x));
							float y = glm::max(otherMin.y, glm::min(colliderPos.y, otherMax.y));
							float z = glm::max(otherMin.z, glm::min(colliderPos.z, otherMax.z));

							float distance = (
								(x - colliderPos.x) * (x - colliderPos.x) +
								(y - colliderPos.y) * (y - colliderPos.y) +
								(z - colliderPos.z) * (z - colliderPos.z));

							if (distance <= collider->GetRadius() * collider->GetRadius())
							{
								collider->ResolveCollision(other, oOwner, colOwner->getLastPosition());
								other->ResolveCollision(collider, colOwner, oOwner->getLastPosition());

								if (!collider->checkCollision(other))
									collider->getCollisions()->push_back(other);
								if (!other->checkCollision(collider))
									other->getCollisions()->push_back(collider);
							}
							else if (collider->checkCollision(other))
							{
								colOwner->OnCollisionExit(oOwner);
								collider->removeCollision(other);

								oOwner->OnCollisionExit(colOwner);
								other->removeCollision(collider);
							}
						}
						break;

						case CollisionBehaviour::SphereCollider:
						{
							glm::vec3 oPos = other->GetPosition();

							float distance = (
								(colliderPos.x - oPos.x) * (colliderPos.x - oPos.x) +
								(colliderPos.y - oPos.y) * (colliderPos.y - oPos.y) +
								(colliderPos.z - oPos.z) * (colliderPos.z - oPos.z));

							if (distance <= (collider->GetRadius() * collider->GetRadius()) + (other->GetRadius() * other->GetRadius()))
							{
								collider->ResolveCollision(other, oOwner, colOwner->getLastPosition());
								other->ResolveCollision(collider, colOwner, oOwner->getLastPosition());

								if (!collider->checkCollision(other))
									collider->getCollisions()->push_back(other);
								if (!other->checkCollision(collider))
									other->getCollisions()->push_back(collider);
							}
							else if (collider->checkCollision(other))
							{
								colOwner->OnCollisionExit(oOwner);
								collider->removeCollision(other);

								oOwner->OnCollisionExit(colOwner);
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