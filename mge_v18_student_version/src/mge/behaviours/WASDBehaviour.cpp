#include "mge/behaviours/WasdBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>

WASDBehaviour::WASDBehaviour() :AbstractBehaviour()
{
	//ctor
}

WASDBehaviour::~WASDBehaviour()
{
	//dtor
}

void WASDBehaviour::update(float pstep)
{
	//Move right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_owner->setLocalPosition(_owner->getLocalPosition() + glm::vec3(pstep * 3, 0, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_owner->setLocalPosition(_owner->getLocalPosition() + glm::vec3(-pstep * 3, 0, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_owner->setLocalPosition(_owner->getLocalPosition() + glm::vec3(0, 0, -pstep * 3));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_owner->setLocalPosition(_owner->getLocalPosition() + glm::vec3(0, 0, pstep * 3));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		_owner->setLocalPosition(_owner->getLocalPosition() + glm::vec3(0, pstep * 3, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		_owner->setLocalPosition(_owner->getLocalPosition() + glm::vec3(0, -pstep * 3, 0));
	}
}
