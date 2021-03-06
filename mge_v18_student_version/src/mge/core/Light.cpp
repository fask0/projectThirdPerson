#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/GameController.hpp"

Light::Light(const std::string& pName, const glm::vec3& pPosition, glm::vec3 color, float startCutOff, float endCutOff, LightType lightType)
	:GameObject(pName, pPosition), _color(color), _startCutOff(startCutOff), _endCutOff(endCutOff), _lightType(lightType)
{
	GameController::Lights.push_back(this);
}

Light::~Light()
{
}

//Override setWorldRecursively to make sure we are registered
//to the world we are a part of.
void Light::_setWorldRecursively(World* pWorld)
{

	//store the previous and new world before and after storing the given world
	World* previousWorld = _world;
	GameObject::_setWorldRecursively(pWorld);
	World* newWorld = _world;

	//check whether we need to register or unregister
	if (previousWorld != nullptr) previousWorld->unregisterLight(this);
	if (newWorld != nullptr) newWorld->registerLight(this);

}

