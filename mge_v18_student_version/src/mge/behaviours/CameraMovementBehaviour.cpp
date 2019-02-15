#include "mge/behaviours/CameraMovementBehaviour.hpp"
#include "mge/core/GameObject.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>
#include "mge/core/GameController.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/quaternion.hpp"

CameraMovementBehaviour::CameraMovementBehaviour(float pXMinLockPos, float pXMaxLockPos, float pZMinLockPos, float pZMaxLockPos, float pMinHeight, float pMaxHeight, sf::RenderWindow* pWindow, glm::vec3 pStartPos, float pMinMovementSpeed, float pMaxMovementSpeed)
	: AbstractBehaviour(), _startPos(pStartPos), _renderWindow(pWindow), _xMinLockPos(pXMinLockPos), _xMaxLockPos(pXMaxLockPos), _zMinLockPos(pZMinLockPos), _zMaxLockPos(pZMaxLockPos), _minHeight(pMinHeight), _maxHeight(pMaxHeight), _minMovementSpeed(pMinMovementSpeed), _maxMovementSpeed(pMaxMovementSpeed)
{
	GameController::CameraBehaviour = this;
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

	//Calculate locking variables
	CalcLockVars();

	//Get mouse position relative to the middle of the window
	_relativeMousePos = glm::vec2(
		(float)(sf::Mouse::getPosition(*_renderWindow).x) - (_windowSize.x / 2),
		(float)(-sf::Mouse::getPosition(*_renderWindow).y) + (_windowSize.y / 2)
	);

	//Do the stuff
	Move(pstep);
}

void CameraMovementBehaviour::CalcLockVars()
{
	float t = GameController::MainCamera->getProjection()[0][0];
	float horizontalFOV = glm::atan(1.0f / t) * 2.0f * (180.0f / 3.14f);
	float verticalFOV = 60.0f;

	//Horizontal locking variables
	float xdiff = glm::tan((horizontalFOV / 2) * (3.14f / 180.0f)) * _ownerPosition.y;
	_camMinX = _xMinLockPos + xdiff;
	_camMaxX = _xMaxLockPos - xdiff;

	//Vertical locking variables
	float rot = -72.78f;
	rot = rot + 90;
	float zdiff = glm::tan(rot * (3.14f / 180.0f)) * _ownerPosition.y;
	_camMinZ = _zMinLockPos - zdiff;

	rot = rot + verticalFOV;
	zdiff = glm::tan(rot * (3.14f / 180.0f)) * _ownerPosition.y;
	_camMaxZ = _zMaxLockPos + zdiff * 0.25f;
}

void CameraMovementBehaviour::Move(float pStep)
{
	//Move camera
	if (_relativeMousePos.x < -(_windowSize.x / 4))
	{
		_owner->setLocalPosition(glm::vec3(_owner->getLocalPosition().x - pStep * 10, _owner->getLocalPosition().y, _owner->getLocalPosition().z));
	}
	if (_relativeMousePos.x > _windowSize.x / 4)
	{
		_owner->setLocalPosition(glm::vec3(_owner->getLocalPosition().x + pStep * 10, _owner->getLocalPosition().y, _owner->getLocalPosition().z));
	}
	if (_relativeMousePos.y < -(_windowSize.y / 4))
	{
		_owner->setLocalPosition(glm::vec3(_owner->getLocalPosition().x, _owner->getLocalPosition().y, _owner->getLocalPosition().z + pStep * 10));
	}
	if (_relativeMousePos.y > _windowSize.y / 4)
	{
		_owner->setLocalPosition(glm::vec3(_owner->getLocalPosition().x, _owner->getLocalPosition().y, _owner->getLocalPosition().z - pStep * 10));
	}

	//Clamp camera
	_owner->setLocalPosition(glm::clamp(_owner->getLocalPosition(), glm::vec3(_camMinX, _minHeight, _camMaxZ), glm::vec3(_camMaxX, _maxHeight, _camMinZ)));
	//_owner->setLocalPosition(glm::vec3(_camMinX, _ownerPosition.y, _camMinZ));
	//std::cout << _owner->getLastPosition() << std::endl;
}

void CameraMovementBehaviour::Scroll(sf::Event pEvent)
{
	if (pEvent.type == sf::Event::MouseWheelMoved)
	{
		if (pEvent.mouseWheel.delta > 0)
		{
			if (_ownerPosition.y > _minHeight)
			{
				_owner->translate(glm::vec3(0, 0, -pEvent.mouseWheel.delta));
			}
		}
		else
		{
			if (_ownerPosition.y < _maxHeight)
			{
				_owner->translate(glm::vec3(0, 0, -pEvent.mouseWheel.delta));
			}
		}
	}
}