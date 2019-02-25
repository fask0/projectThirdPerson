#include "mge/behaviours/FollowMouseOnGridBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/materials/LitTextureGridMaterial.hpp"
#include "mge/materials/LitSelectedTextureMaterial.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "glm.hpp"


FollowMouseOnGridBehaviour::FollowMouseOnGridBehaviour(LitTextureGridMaterial* pMaterial) : AbstractBehaviour(), _material(pMaterial)
{

}

FollowMouseOnGridBehaviour::FollowMouseOnGridBehaviour(LitDynamicTextureGridMaterial* pMaterial) : AbstractBehaviour(), _materialDynamic(pMaterial)
{

}

FollowMouseOnGridBehaviour::~FollowMouseOnGridBehaviour()
{
	//dtor
}

void FollowMouseOnGridBehaviour::update(float pstep)
{
	float yScale = glm::sqrt(_owner->getTransform()[1][0] * _owner->getTransform()[1][0] + _owner->getTransform()[1][1] * _owner->getTransform()[1][1] + _owner->getTransform()[1][2] * _owner->getTransform()[1][2]);
	if (_material != nullptr)
	{
		float gSize = _material->getGridSize();
		glm::vec3 pos = (glm::floor(_material->getMousePos() / gSize) * gSize) + glm::vec3(gSize / 2, yScale / 2, gSize / 2);
		_owner->setLocalPosition(pos);
		_material->SetTowerPos(pos);
	}
	else
	{
		float gSize = _materialDynamic->getGridSize();
		glm::vec3 pos = (glm::floor(_materialDynamic->getMousePos() / gSize) * gSize) + glm::vec3(gSize / 2, yScale / 2, gSize / 2);
		_owner->setLocalPosition(pos);
		_materialDynamic->SetTowerPos(pos);
		_materialDynamic->setColliding(_owner->isColliding);
	}

	dynamic_cast<LitSelectedTextureMaterial*>(_owner->getMaterial())->SetColliding(_owner->isColliding);
}
