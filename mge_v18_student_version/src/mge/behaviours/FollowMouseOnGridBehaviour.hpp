#ifndef FOLLOWMOUSEONGRIDBEHAVIOUR_HPP
#define FOLLOWMOUSEONGRIDBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/materials/LitTextureGridMaterial.hpp"
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"
#include "glm.hpp"

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
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

#endif // ROTATINGBEHAVIOUR_HPP
