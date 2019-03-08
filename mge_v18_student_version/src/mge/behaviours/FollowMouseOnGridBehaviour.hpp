#pragma once
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"
#include "mge/materials/LitTextureGridMaterial.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm.hpp"

class FollowMouseOnGridBehaviour : public AbstractBehaviour
{
public:
	FollowMouseOnGridBehaviour(LitTextureGridMaterial* pMaterial);
	FollowMouseOnGridBehaviour(LitDynamicTextureGridMaterial* pMaterial);
	virtual ~FollowMouseOnGridBehaviour();

	virtual void update(float pstep);

private:
	LitTextureGridMaterial* _material = nullptr;
	LitDynamicTextureGridMaterial* _materialDynamic = nullptr;
};
