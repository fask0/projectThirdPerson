#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm.hpp"
#include "mge/core/GameObject.hpp"

/**
 * Exercise for the student: implement the Light class...
 * Imagine things like setLightType, setLightIntensity, setFalloffAngle etc, see the corresponding lectures
 */
class Light : public GameObject
{
	public:
	enum LightType
	{
		Spotlight,
		Directional
	};

	Light(const std::string& aName = nullptr, const glm::vec3& aPosition = glm::vec3(2.0f, 10.0f, 5.0f), glm::vec3 color = glm::vec3(0.5f, 1.0f, 0.0f), float startCutOff = 10, float endCutOff = 30, LightType lightType = Directional);
	virtual ~Light();

	glm::vec3 _color;
	float _startCutOff;
	float _endCutOff;
	LightType _lightType;

	//override set parent to register/deregister light...
	virtual void _setWorldRecursively(World* pWorld) override;
};

#endif // LIGHT_HPP
