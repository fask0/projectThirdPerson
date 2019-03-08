#include <iostream>
#include <memory>
#include <vector>

#include "mge/core/CollisionManager.hpp"
#include "mge/core/GameController.hpp"

#include "glm.hpp"

std::vector<CollisionBehaviour*> CollisionManager::projectileCollisions;
std::vector<CollisionBehaviour*> CollisionManager::towerCollisions;

CollisionManager::CollisionManager(const std::string& pName, const glm::vec3& pPosition)
	: GameObject(pName, pPosition)
{
	projectileCollisions.clear();
	towerCollisions.clear();
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::update(float pStep)
{
	//Detect Collision
	//ProjectileCollision
	if (projectileCollisions.size() > 0)
	{
		CollisionBehaviour* colliderP;
		CollisionBehaviour* otherP;

		for (int i = 0; i < projectileCollisions.size(); ++i)
		{
			colliderP = projectileCollisions[i];
			GameObject* colOwner = colliderP->getOwner();
			if (colOwner->SkipCollisionCheck()) continue;

			glm::vec3 colliderMax = colliderP->GetMax();
			glm::vec3 colliderMin = colliderP->GetMin();
			glm::vec3 colliderPos = colliderP->GetPosition();

			switch (colliderP->colliderType)
			{
				case CollisionBehaviour::BoxCollider:
				{
					for (int j = 0; j < projectileCollisions.size(); ++j)
					{
						otherP = projectileCollisions[j];
						GameObject* oOwner = otherP->getOwner();
						if (colliderP == otherP ||
							colOwner->IgnoreCollision(oOwner) ||
							oOwner->IgnoreCollision(colOwner)) continue;

						switch (otherP->colliderType)
						{
							case CollisionBehaviour::BoxCollider:
							{
								glm::vec3 otherMax = otherP->GetMax();
								glm::vec3 otherMin = otherP->GetMin();

								if ((colliderMax.x >= otherMin.x && colliderMin.x <= otherMax.x) &&
									(colliderMax.y >= otherMin.y && colliderMin.y <= otherMax.y) &&
									(colliderMax.z >= otherMin.z && colliderMin.z <= otherMax.z))
								{
									colliderP->ResolveCollision(otherP, oOwner, colOwner->getLastPosition());
									otherP->ResolveCollision(colliderP, colOwner, oOwner->getLastPosition());

									if (!colliderP->checkCollision(otherP))
										colliderP->_behavioursInCollision.push_back(otherP);
									if (!otherP->checkCollision(colliderP))
										otherP->_behavioursInCollision.push_back(colliderP);
								}
								else if (colliderP->checkCollision(otherP))
								{
									colOwner->OnCollisionExit(oOwner);
									colliderP->removeCollision(otherP);

									oOwner->OnCollisionExit(colOwner);
									otherP->removeCollision(colliderP);
								}
							}
							break;

							case CollisionBehaviour::SphereCollider:
							{
								glm::vec3 oPos = otherP->GetPosition();

								float x = glm::max(colliderMin.x, glm::min(oPos.x, colliderMax.x));
								float y = glm::max(colliderMin.y, glm::min(oPos.y, colliderMax.y));
								float z = glm::max(colliderMin.z, glm::min(oPos.z, colliderMax.z));

								float distance = (
									(x - oPos.x) * (x - oPos.x) +
									(y - oPos.y) * (y - oPos.y) +
									(z - oPos.z) * (z - oPos.z));

								if (distance <= otherP->GetRadius() * otherP->GetRadius())
								{
									colliderP->ResolveCollision(otherP, oOwner, colOwner->getLastPosition());
									otherP->ResolveCollision(colliderP, colOwner, oOwner->getLastPosition());

									if (!colliderP->checkCollision(otherP))
										colliderP->_behavioursInCollision.push_back(otherP);
									if (!otherP->checkCollision(colliderP))
										otherP->_behavioursInCollision.push_back(colliderP);
								}
								else if (colliderP->checkCollision(otherP))
								{
									colOwner->OnCollisionExit(oOwner);
									colliderP->removeCollision(otherP);

									oOwner->OnCollisionExit(colOwner);
									otherP->removeCollision(colliderP);
								}
							}
							break;
						}
					}
				}
				break;

				case CollisionBehaviour::SphereCollider:
				{
					for (int j = 0; j < projectileCollisions.size(); ++j)
					{
						otherP = projectileCollisions[j];
						GameObject* oOwner = otherP->getOwner();

						if (colliderP == otherP ||
							colOwner->IgnoreCollision(oOwner) ||
							oOwner->IgnoreCollision(colOwner)) continue;

						switch (otherP->colliderType)
						{
							case CollisionBehaviour::BoxCollider:
							{
								glm::vec3 otherMax = otherP->GetMax();
								glm::vec3 otherMin = otherP->GetMin();

								float x = glm::max(otherMin.x, glm::min(colliderPos.x, otherMax.x));
								float y = glm::max(otherMin.y, glm::min(colliderPos.y, otherMax.y));
								float z = glm::max(otherMin.z, glm::min(colliderPos.z, otherMax.z));

								float distance = (
									(x - colliderPos.x) * (x - colliderPos.x) +
									(y - colliderPos.y) * (y - colliderPos.y) +
									(z - colliderPos.z) * (z - colliderPos.z));

								if (distance <= colliderP->GetRadius() * colliderP->GetRadius())
								{
									colliderP->ResolveCollision(otherP, oOwner, colOwner->getLastPosition());
									otherP->ResolveCollision(colliderP, colOwner, oOwner->getLastPosition());

									if (!colliderP->checkCollision(otherP))
										colliderP->_behavioursInCollision.push_back(otherP);
									if (!otherP->checkCollision(colliderP))
										otherP->_behavioursInCollision.push_back(colliderP);
								}
								else if (colliderP->checkCollision(otherP))
								{
									colOwner->OnCollisionExit(oOwner);
									colliderP->removeCollision(otherP);

									oOwner->OnCollisionExit(colOwner);
									otherP->removeCollision(colliderP);
								}
							}
							break;

							case CollisionBehaviour::SphereCollider:
							{
								glm::vec3 oPos = otherP->GetPosition();

								float distance = (
									(colliderPos.x - oPos.x) * (colliderPos.x - oPos.x) +
									(colliderPos.y - oPos.y) * (colliderPos.y - oPos.y) +
									(colliderPos.z - oPos.z) * (colliderPos.z - oPos.z));

								if (distance <= (colliderP->GetRadius() * colliderP->GetRadius()) + (otherP->GetRadius() * otherP->GetRadius()))
								{
									colliderP->ResolveCollision(otherP, oOwner, colOwner->getLastPosition());
									otherP->ResolveCollision(colliderP, colOwner, oOwner->getLastPosition());

									if (!colliderP->checkCollision(otherP))
										colliderP->_behavioursInCollision.push_back(otherP);
									if (!otherP->checkCollision(colliderP))
										otherP->_behavioursInCollision.push_back(colliderP);
								}
								else if (colliderP->checkCollision(otherP))
								{
									colOwner->OnCollisionExit(oOwner);
									colliderP->removeCollision(otherP);

									oOwner->OnCollisionExit(colOwner);
									otherP->removeCollision(colliderP);
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

	//TowerCollision
	if (towerCollisions.size() <= 0) return;
	if (!dynamic_cast<LitDynamicTextureGridMaterial*>(GameController::CurrentLevel->getLayers()[0]->getMaterial())->isGridShowing()) return;

	CollisionBehaviour* colliderT;
	CollisionBehaviour* otherT;

	for (int i = 0; i < towerCollisions.size(); ++i)
	{
		colliderT = towerCollisions[i];
		GameObject* colOwner = colliderT->getOwner();
		if (colOwner->SkipCollisionCheck()) continue;

		glm::vec3 colliderMax = colliderT->GetMax();
		glm::vec3 colliderMin = colliderT->GetMin();
		glm::vec3 colliderPos = colliderT->GetPosition();

		switch (colliderT->colliderType)
		{
			case CollisionBehaviour::BoxCollider:
			{
				for (int j = 0; j < towerCollisions.size(); ++j)
				{
					otherT = towerCollisions[j];
					GameObject* oOwner = otherT->getOwner();
					if (colliderT == otherT ||
						colOwner->IgnoreCollision(oOwner) ||
						oOwner->IgnoreCollision(colOwner)) continue;

					switch (otherT->colliderType)
					{
						case CollisionBehaviour::BoxCollider:
						{
							glm::vec3 otherMax = otherT->GetMax();
							glm::vec3 otherMin = otherT->GetMin();

							if ((colliderMax.x >= otherMin.x && colliderMin.x <= otherMax.x) &&
								(colliderMax.y >= otherMin.y && colliderMin.y <= otherMax.y) &&
								(colliderMax.z >= otherMin.z && colliderMin.z <= otherMax.z))
							{
								colliderT->ResolveCollision(otherT, oOwner, colOwner->getLastPosition());
								otherT->ResolveCollision(colliderT, colOwner, oOwner->getLastPosition());

								if (!colliderT->checkCollision(otherT))
									colliderT->_behavioursInCollision.push_back(otherT);
								if (!otherT->checkCollision(colliderT))
									otherT->_behavioursInCollision.push_back(colliderT);
							}
							else if (colliderT->checkCollision(otherT))
							{
								colOwner->OnCollisionExit(oOwner);
								colliderT->removeCollision(otherT);

								oOwner->OnCollisionExit(colOwner);
								otherT->removeCollision(colliderT);
							}
						}
						break;

						case CollisionBehaviour::SphereCollider:
						{
							glm::vec3 oPos = otherT->GetPosition();

							float x = glm::max(colliderMin.x, glm::min(oPos.x, colliderMax.x));
							float y = glm::max(colliderMin.y, glm::min(oPos.y, colliderMax.y));
							float z = glm::max(colliderMin.z, glm::min(oPos.z, colliderMax.z));

							float distance = (
								(x - oPos.x) * (x - oPos.x) +
								(y - oPos.y) * (y - oPos.y) +
								(z - oPos.z) * (z - oPos.z));

							if (distance <= otherT->GetRadius() * otherT->GetRadius())
							{
								colliderT->ResolveCollision(otherT, oOwner, colOwner->getLastPosition());
								otherT->ResolveCollision(colliderT, colOwner, oOwner->getLastPosition());

								if (!colliderT->checkCollision(otherT))
									colliderT->_behavioursInCollision.push_back(otherT);
								if (!otherT->checkCollision(colliderT))
									otherT->_behavioursInCollision.push_back(colliderT);
							}
							else if (colliderT->checkCollision(otherT))
							{
								colOwner->OnCollisionExit(oOwner);
								colliderT->removeCollision(otherT);

								oOwner->OnCollisionExit(colOwner);
								otherT->removeCollision(colliderT);
							}
						}
						break;
					}
				}
			}
			break;

			case CollisionBehaviour::SphereCollider:
			{
				for (int j = 0; j < towerCollisions.size(); ++j)
				{
					otherT = towerCollisions[j];
					GameObject* oOwner = otherT->getOwner();

					if (colliderT == otherT ||
						colOwner->IgnoreCollision(oOwner) ||
						oOwner->IgnoreCollision(colOwner)) continue;

					switch (otherT->colliderType)
					{
						case CollisionBehaviour::BoxCollider:
						{
							glm::vec3 otherMax = otherT->GetMax();
							glm::vec3 otherMin = otherT->GetMin();

							float x = glm::max(otherMin.x, glm::min(colliderPos.x, otherMax.x));
							float y = glm::max(otherMin.y, glm::min(colliderPos.y, otherMax.y));
							float z = glm::max(otherMin.z, glm::min(colliderPos.z, otherMax.z));

							float distance = (
								(x - colliderPos.x) * (x - colliderPos.x) +
								(y - colliderPos.y) * (y - colliderPos.y) +
								(z - colliderPos.z) * (z - colliderPos.z));

							if (distance <= colliderT->GetRadius() * colliderT->GetRadius())
							{
								colliderT->ResolveCollision(otherT, oOwner, colOwner->getLastPosition());
								otherT->ResolveCollision(colliderT, colOwner, oOwner->getLastPosition());

								if (!colliderT->checkCollision(otherT))
									colliderT->_behavioursInCollision.push_back(otherT);
								if (!otherT->checkCollision(colliderT))
									otherT->_behavioursInCollision.push_back(colliderT);
							}
							else if (colliderT->checkCollision(otherT))
							{
								colOwner->OnCollisionExit(oOwner);
								colliderT->removeCollision(otherT);

								oOwner->OnCollisionExit(colOwner);
								otherT->removeCollision(colliderT);
							}
						}
						break;

						case CollisionBehaviour::SphereCollider:
						{
							glm::vec3 oPos = otherT->GetPosition();

							float distance = (
								(colliderPos.x - oPos.x) * (colliderPos.x - oPos.x) +
								(colliderPos.y - oPos.y) * (colliderPos.y - oPos.y) +
								(colliderPos.z - oPos.z) * (colliderPos.z - oPos.z));

							if (distance <= (colliderT->GetRadius() * colliderT->GetRadius()) + (otherT->GetRadius() * otherT->GetRadius()))
							{
								colliderT->ResolveCollision(otherT, oOwner, colOwner->getLastPosition());
								otherT->ResolveCollision(colliderT, colOwner, oOwner->getLastPosition());

								if (!colliderT->checkCollision(otherT))
									colliderT->_behavioursInCollision.push_back(otherT);
								if (!otherT->checkCollision(colliderT))
									otherT->_behavioursInCollision.push_back(colliderT);
							}
							else if (colliderT->checkCollision(otherT))
							{
								colOwner->OnCollisionExit(oOwner);
								colliderT->removeCollision(otherT);

								oOwner->OnCollisionExit(colOwner);
								otherT->removeCollision(colliderT);
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
