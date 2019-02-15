#include "mge/behaviours/CameraMovementBehaviour.hpp"
#include "mge/core/GameObject.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

CameraMovementBehaviour::CameraMovementBehaviour(float pXDistance, float pZDistance, float pMinHeight, float pMaxHeight, sf::RenderWindow* pWindow, glm::vec3 pStartPos)
	: AbstractBehaviour(), _startPos(pStartPos), _renderWindow(pWindow), _xDistance(pXDistance), _zDistance(pZDistance), _minHeight(pMinHeight), _maxHeight(pMaxHeight)
{

}

CameraMovementBehaviour::~CameraMovementBehaviour()
{
	//dtor
}

void CameraMovementBehaviour::update(float pstep)
{
	//Get window size
	_windowSize = glm::vec2(_renderWindow->getSize().x, _renderWindow->getSize().y);

	//Get owner local position
	_ownerPosition = _owner->getLocalPosition();

	//Get mouse position relative to the middle of the window
	_relativeMousePos = glm::vec2(
		(float)(sf::Mouse::getPosition(*_renderWindow).x) - (_windowSize.x / 2),
		(float)(-sf::Mouse::getPosition(*_renderWindow).y) + (_windowSize.y / 2)
	);

	//Do the stuff
	Move();
	Scroll();
}

void CameraMovementBehaviour::Move()
{
	if (_relativeMousePos.x > _windowSize.x / 4)
	{
		if (_ownerPosition.x < _xDistance)
		{
			_owner->translate(glm::vec3(1, 0, 0));
		}
		std::cout << "move right" << std::endl;
	}
	if (_relativeMousePos.x < -(_windowSize.x / 4))
	{
		if (_ownerPosition.x > -_xDistance)
		{
			_owner->translate(glm::vec3(-1, 0, 0));
		}
		std::cout << "move left" << std::endl;
	}
	if (_relativeMousePos.y > _windowSize.y / 4)
	{
		if (_ownerPosition.z > -(_zDistance + _startPos.z))
		{
			_owner->setLocalPosition(_owner->getLocalPosition() + glm::vec3(0, 0, -1));
		}
		std::cout << "move up" << std::endl;
		//std::cout << _owner->getLocalPosition() << std::endl;
	}
	if (_relativeMousePos.y < -(_windowSize.y / 4))
	{
		if (_ownerPosition.z < (_zDistance + _startPos.z))
		{
			_owner->setLocalPosition(_owner->getLocalPosition() + glm::vec3(0, 0, 1));
		}
		std::cout << "move down" << std::endl;
	}
}

void CameraMovementBehaviour::Scroll()
{

}