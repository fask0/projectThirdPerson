#ifndef CAMERAMOVEMENTBEHAVIOUR_HPP
#define CAMERAMOVEMENTBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class CameraMovementBehaviour : public AbstractBehaviour
{
	public:
	CameraMovementBehaviour(float pXMinLockPos, float pXMaxLockPos, float pZMinLockPos, float pZMaxLockPos, float pMinHeight, float pMaxHeight, sf::RenderWindow* pWindow, glm::vec3 pStartPos = glm::vec3(0, 0, 0), float pMinMovementSpeed = 5, float pMaxMovementSpeed = 20);
	virtual ~CameraMovementBehaviour();

	virtual void update(float pstep);
	void Move(float pStep);
	void Scroll(sf::Event pEvent);

	private:
	//Contructor variables
	sf::RenderWindow* _renderWindow;
	glm::vec3 _startPos;
	float _xMinLockPos;
	float _xMaxLockPos;
	float _zMinLockPos;
	float _zMaxLockPos;
	float _minHeight;
	float _maxHeight;
	float _minMovementSpeed;
	float _maxMovementSpeed;

	//Logic variables
	glm::vec2 _relativeMousePos;
	glm::vec2 _windowSize;
	glm::vec3 _ownerPosition;

	//Camera locking variables
	float _camMinX;
	float _camMaxX;
	float _camMinZ;
	float _camMaxZ;
	void CalcLockVars();
};

#endif // ROTATINGBEHAVIOUR_HPP
