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
#include "mge/behaviours/WASDBehaviour.hpp"

Tower::Tower(std::string pName, glm::vec3 pPosition, float pRange, AbstractMaterial* pMaterial)
	: GameObject(pName, pPosition), _range(pRange), _material(pMaterial), isPlaced(false)
{
	_tag = "tower";
	rotate(glm::radians(180.0f), glm::vec3(0, 1, 0));
	if (dynamic_cast<LitSelectedTextureMaterial*>(_material))
	{
		for (int i = 1; i < GameController::Lights.size(); i++)
		{
			dynamic_cast<LitSelectedTextureMaterial*>(_material)->AddLight(GameController::Lights[1]);
		}
	}
	setMaterial(_material);
	if (dynamic_cast<LitSelectedTextureMaterial*>(_material))
		dynamic_cast<LitSelectedTextureMaterial*>(_material)->SetMixIntensity(0.0f);

	float xScale = glm::sqrt(getTransform()[0][0] * getTransform()[0][0] + getTransform()[0][1] * getTransform()[0][1] + getTransform()[0][2] * getTransform()[0][2]);
	float yScale = glm::sqrt(getTransform()[1][0] * getTransform()[1][0] + getTransform()[1][1] * getTransform()[1][1] + getTransform()[1][2] * getTransform()[1][2]);
	float zScale = glm::sqrt(getTransform()[2][0] * getTransform()[2][0] + getTransform()[2][1] * getTransform()[2][1] + getTransform()[2][2] * getTransform()[2][2]);

	addBehaviour(new CollisionBehaviour(CollisionBehaviour::Tower, glm::vec3(xScale * 1.25f, yScale, zScale * 1.25f), true, glm::vec3(0, yScale / 2, 0)));
	std::cout << _name << " " << _tag << " spawn" << std::endl;
}

Tower::~Tower()
{
	//dtor
}

void Tower::OnCollisionEnter(GameObject* pOther)
{
}

void Tower::OnCollisionExit(GameObject* pOther)
{
}

bool Tower::SkipCollisionCheck()
{
	return isPlaced;
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

void Tower::AddTowerBehaviour()
{
}