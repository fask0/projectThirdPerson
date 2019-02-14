#include "glm.hpp"
#include "mge/core/Tower.hpp"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"

Tower::Tower(std::string pName, glm::vec3 pPosition, float pRange, AbstractMaterial* pMaterial)
	: GameObject(pName, pPosition), _range(pRange), _material(pMaterial)
{
	setMaterial(_material);
}

Tower::~Tower()
{
	//dtor
}

void Tower::update(float pStep)
{
	//rayCast();

	GameObject::update(pStep);
}

void Tower::ResetMaterial()
{
	setMaterial(_material);
}

void Tower::Rotate90()
{
	rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
}

float Tower::GetRange()
{
	return _range;
}

