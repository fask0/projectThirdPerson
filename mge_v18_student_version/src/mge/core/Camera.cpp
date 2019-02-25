#include "glm.hpp"
#include "mge/core/Camera.hpp"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "mge/core/GameController.hpp"

Camera::Camera(sf::RenderWindow* pWindow, std::string pName, glm::vec3 pPosition, glm::mat4 pProjectionMatrix)
	: GameObject(pName, pPosition), _projection(pProjectionMatrix), _window(pWindow)
{
	GameController::MainCamera = this;
}

Camera::~Camera()
{
	//dtor
}

glm::mat4& Camera::getProjection()
{
	return _projection;
}

void Camera::update(float pStep)
{
	//rayCast();

	GameObject::update(pStep);
}

glm::vec3 Camera::rayCastNormalizedDiffVec()
{
	float dist = std::abs((_window->getSize().y / 2.0f) / std::tan(glm::radians(60.0f / 2.0f)));

	glm::vec2 mousePosRelativeToScreenCenter = glm::vec2(
		(float)(sf::Mouse::getPosition(*_window).x) - (_window->getSize().x / 2),
		(float)(-sf::Mouse::getPosition(*_window).y) + (_window->getSize().y / 2)
	);

	glm::vec3 startRayPos = this->getWorldPosition();
	glm::vec4 endRayPos = glm::vec4(
		mousePosRelativeToScreenCenter.x,
		mousePosRelativeToScreenCenter.y,
		-dist,
		0
	);

	glm::vec3 rayWorld = glm::vec3(getWorldTransform() * endRayPos);
	glm::vec3 norm = glm::normalize(rayWorld);

	return norm;
}

