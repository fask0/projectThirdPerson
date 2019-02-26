#include "glm.hpp"
#include "mge/core/Tower.hpp"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/LitSelectedTextureMaterial.hpp"
#include "mge/core/GameController.hpp"
#include "mge/config.hpp"
#include "mge/behaviours/CollisionBehaviour.hpp"

Tower::Tower(std::string pName, glm::vec3 pPosition, float pRange, AbstractMaterial* pMaterial)
	: GameObject(pName, pPosition), _range(pRange), _material(pMaterial)
{
	_material = new LitSelectedTextureMaterial(GameController::Lights[0], Texture::load(config::MGE_TEXTURE_PATH + "diffuse2.jpg"));
	for (int i = 1; i < GameController::Lights.size(); i++)
	{
		dynamic_cast<LitSelectedTextureMaterial*>(_material)->AddLight(GameController::Lights[1]);
	}
	setMaterial(_material);
	dynamic_cast<LitSelectedTextureMaterial*>(_material)->SetMixIntensity(0.0f);

	float xScale = glm::sqrt(getTransform()[0][0] * getTransform()[0][0] + getTransform()[0][1] * getTransform()[0][1] + getTransform()[0][2] * getTransform()[0][2]);
	float yScale = glm::sqrt(getTransform()[1][0] * getTransform()[1][0] + getTransform()[1][1] * getTransform()[1][1] + getTransform()[1][2] * getTransform()[1][2]);
	float zScale = glm::sqrt(getTransform()[2][0] * getTransform()[2][0] + getTransform()[2][1] * getTransform()[2][1] + getTransform()[2][2] * getTransform()[2][2]);

	addBehaviour(new CollisionBehaviour(glm::vec3(xScale * 0.99f, yScale, zScale * 0.99f), true));
	std::cout << _name << " spawn" << std::endl;
}

Tower::~Tower()
{
	//dtor
	GameObject::~GameObject();
}

void Tower::OnCollisionEnter(GameObject* pOther)
{
	std::cout << "hit lel" << std::endl;
}

void Tower::OnCollisionExit(GameObject* pOther)
{
	std::cout << "stop lel" << std::endl;
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

float Tower::GetAttSpeed()
{
	return _attSpeed;
}

int Tower::GetCost()
{
	return _cost;
}