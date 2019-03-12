#include "mge/behaviours/FollowMouseOnGridBehaviour.hpp"
#include "mge/materials/LitTextureGridMaterial.hpp"
#include "mge/materials/LitSelectedTextureMaterial.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/GameObject.hpp"
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
	glm::mat4 transform = GameController::GridObjects[0]->getWorldTransform();
	glm::vec4 bounds = GameController::CameraBehaviour->GetBounds();
	float yScale = glm::sqrt(_owner->getTransform()[1][0] * _owner->getTransform()[1][0] + _owner->getTransform()[1][1] * _owner->getTransform()[1][1] + _owner->getTransform()[1][2] * _owner->getTransform()[1][2]);

	if (_material != nullptr)
	{
		float gSize = _material->getGridSize();
		glm::vec3 pos = (glm::floor(_material->getMousePos() / gSize) * gSize) + glm::vec3(gSize / 2, 0, gSize / 2);
		pos.y = 0.05f;
		if (pos.x > bounds[0] && pos.x < bounds[1])
		{
			_owner->setLocalPosition(glm::vec3(pos.x, pos.y, _owner->getLocalPosition().z));
			_material->SetTowerPos(glm::vec3(pos.x, pos.y, _owner->getLocalPosition().z));
		}
		if (pos.z > bounds[2] && pos.z < bounds[3])
		{
			_owner->setLocalPosition(glm::vec3(_owner->getLocalPosition().x, pos.y, pos.z));
			_material->SetTowerPos(glm::vec3(_owner->getLocalPosition().x, pos.y, pos.z));
		}
	}
	else
	{
		float gSize = _materialDynamic->getGridSize();
		glm::vec3 pos = (glm::floor(_materialDynamic->getMousePos() / gSize) * gSize) + glm::vec3(gSize / 2, 0, gSize / 2);
		pos.y = 0.05f;
		if (pos.x > bounds[0] && pos.x < bounds[1])
		{
			_owner->setLocalPosition(glm::vec3(pos.x, pos.y, _owner->getLocalPosition().z));
			_materialDynamic->SetTowerPos(glm::vec3(pos.x, pos.y, _owner->getLocalPosition().z));
			_materialDynamic->setColliding(_owner->isColliding);
		}
		if (pos.z > bounds[2] && pos.z < bounds[3])
		{
			_owner->setLocalPosition(glm::vec3(_owner->getLocalPosition().x, pos.y, pos.z));
			_materialDynamic->SetTowerPos(glm::vec3(_owner->getLocalPosition().x, pos.y, pos.z));
			_materialDynamic->setColliding(_owner->isColliding);
		}
	}
	dynamic_cast<LitSelectedTextureMaterial*>(_owner->getMaterial())->SetColliding(_owner->isColliding);

	if (GameController::GridManager->_currentMoney >= dynamic_cast<Tower*>(_owner)->GetCost())
	{
		if (!_owner->isColliding)
		{
			_materialDynamic->setColliding(false);
			dynamic_cast<LitSelectedTextureMaterial*>(_owner->getMaterial())->SetColliding(false);
		}
	}
	else
	{
		_materialDynamic->setColliding(true);
	}
}
