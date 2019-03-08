#pragma once

#include "GL/glew.h"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"

class ShaderProgram;

class ShadowMaterial : public AbstractMaterial
{
	public:
	ShadowMaterial(Light *light, Texture* pDiffuseTexture);
	virtual ~ShadowMaterial();
	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	private:
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	std::vector<Light*> _lights;

	Texture* _diffuseTexture;
	Light *_light;
};