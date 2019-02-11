#include "mge/behaviours/WasdBehaviour.hpp"
#include "mge/core/GameObject.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
}
