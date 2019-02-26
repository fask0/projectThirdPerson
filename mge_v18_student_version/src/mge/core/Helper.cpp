#include <iostream>
#include "glm.hpp"
#include "mge/core/Helper.hpp"
#include "mge/core/GameObject.hpp"

Helper::Helper()
{
}

Helper::~Helper()
{

}

glm::vec3 Helper::GetRotationFromMatrix(glm::mat4 pMatrix)
{
	if (pMatrix[0][0] == 1.0f)
	{
		return glm::vec3(
			glm::atan(pMatrix[2][0], pMatrix[3][2]),
			0,
			0);
	}
	else if (pMatrix[0][0] == -1.0f)
	{
		return glm::vec3(
			glm::atan(pMatrix[2][0], pMatrix[3][2]),
			0,
			0);
	}
	else
	{
		return glm::vec3(
			glm::atan(pMatrix[0][2], pMatrix[0][0]),
			glm::asin(pMatrix[0][1]),
			glm::atan(-pMatrix[2][1], pMatrix[1][1])
		);
	}
}

void Helper::LookAt(GameObject* pLooker, GameObject* pLookedAtter)
{
	glm::vec3 diff = pLookedAtter->getLocalPosition() - pLooker->getLocalPosition();
	float currentRot = GetRotationFromMatrix(pLooker->getTransform()).x;
	float desiredRot = glm::atan(diff.z / diff.x);
	if (diff.x < 0)
		desiredRot += 3.1415f;
	pLooker->rotate(-(desiredRot - currentRot), glm::vec3(0, 1, 0));
}

