#include "mge/behaviours/CameraOrbitBehaviour.hpp"
#include "mge/core/GameObject.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Mouse.hpp>

CameraOrbitBehaviour::CameraOrbitBehaviour(GameObject * target, float distance, float maxTiltAngle, float rotationSpeed) : AbstractBehaviour()
{
	_target = target->getTransform();
	_distance = distance;
	_maxTiltAngle = maxTiltAngle;
	_rotationSpeed = rotationSpeed;
}

CameraOrbitBehaviour::~CameraOrbitBehaviour()
{
	//dtor
}

void CameraOrbitBehaviour::update(float pstep)
{
	//Copy target transform
	_owner->setTransform(_target);


	//Change x rotation based on mouse position and rotation speed
	sf::Vector2i input = sf::Mouse::getPosition();
	if (input.x > 1920 / 2)
	{

		_xRotation += ((input.x - (1920 / 2)) * pstep * _rotationSpeed) / 1000;
	}
	else
	{
		_xRotation -= (((1920 / 2) - input.x) * pstep * _rotationSpeed) / 1000;
	}
	//Change y rotation based on mouse position and rotation speed
	if (input.y > 1080 / 2)
	{
		_yRotation += ((input.y - (1080 / 2)) * pstep * _rotationSpeed) / 1000;
	}
	else
	{
		_yRotation -= (((1080 / 2) - input.y) * pstep * _rotationSpeed) / 1000;
	}

	//Clamp y rotation
	_yRotation = std::min(_maxTiltAngle * (3.14f / 180), _yRotation);
	_yRotation = std::max(-_maxTiltAngle * (3.14f / 180), _yRotation);

	//Set the rotation of the gameobject
	_owner->rotate(_xRotation, glm::vec3(0, 1, 0));
	_owner->rotate(_yRotation, glm::vec3(1, 0, 0));

	//Move camera away from target
	glm::mat4 translation = glm::translate(glm::mat4(), glm::vec3(0, 0, _distance));
	_owner->setTransform(_owner->getTransform() * translation);
}
