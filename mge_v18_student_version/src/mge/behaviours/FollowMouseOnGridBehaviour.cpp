#include "mge/behaviours/FollowMouseOnGridBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/materials/LitTextureGridMaterial.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "glm.hpp"


FollowMouseOnGridBehaviour::FollowMouseOnGridBehaviour(LitTextureGridMaterial* pMaterial) : AbstractBehaviour(), _material(pMaterial)
{

}

FollowMouseOnGridBehaviour::~FollowMouseOnGridBehaviour()
{
	//dtor
}

void FollowMouseOnGridBehaviour::update(float pstep)
{
	float gSize = _material->getGridSize();
	glm::vec3 pos = (glm::floor(_material->getMousePos() / gSize) * gSize) + glm::vec3(gSize / 2, _owner->getTransform()[3].length() / 2, gSize / 2);
	_owner->setLocalPosition(pos);
	_material->SetTowerPos(pos);
}
