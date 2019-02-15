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
	CameraMovementBehaviour(float pXDistance, float pZDistance, float pMinHeight, float pMaxHeight, sf::RenderWindow* pWindow, glm::vec3 pStartPos = glm::vec3(0, 0, 0));
	virtual ~CameraMovementBehaviour();

	virtual void update(float pstep);
	void Move();
	void Scroll();

private:
	//Contructor variables
	sf::RenderWindow* _renderWindow;
	glm::vec3 _startPos;
	float _xDistance;
	float _zDistance;
	float _minHeight;
	float _maxHeight;

	//Logic variables
	glm::vec2 _relativeMousePos;
	glm::vec2 _windowSize;
	glm::vec3 _ownerPosition;
};

#endif // ROTATINGBEHAVIOUR_HPP
