#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <iostream>
#include <vector>

#include "mge/behaviours/CollisionBehaviour.hpp"
#include "mge/core/GameObject.hpp"

#include "glm.hpp"

class CollisionManager : public GameObject
{
	public:
	static std::vector<CollisionBehaviour*> collisionBehaviours;

	CollisionManager(const std::string& aName = nullptr, const glm::vec3& aPosition = glm::vec3(0, 0, 0));
	virtual ~CollisionManager();

	void update(float pStep);
};

#endif // !COLLIDER_HPP
