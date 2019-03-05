#ifndef HELPER_HPP
#define HELPER_HPP

#include <string>
#include <iostream>

#include "mge/behaviours/CameraMovementBehaviour.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Waypoint.hpp"
#include "mge/core/Enemy.hpp"

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world-to-view matrix by taking the inverse of the camera transform.
 * The camera's perspective matrix is used in the MVP matrix creation.
 */
class Helper
{
	public:
	Helper();
	virtual ~Helper();

	static glm::vec3 GetRotationFromMatrix(glm::mat4);
	static void LookAt(GameObject* pLooker, GameObject* pLookedAtter);
	static void Slerp(GameObject * pSlerper, GameObject * pSlerpatee, float pIncrement);

	private:
	Helper(const Helper&);
	Helper& operator= (const Helper&);
};

#endif // GAMECONTROLLER_HPP
