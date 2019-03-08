#include "glm.hpp"

#include "mge/materials/ShadowMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/GameController.hpp"

ShaderProgram* LitDynamicTextureGridMaterial::_shader = NULL;

ShadowMaterial::ShadowMaterial(Light * light, Texture * pDiffuseTexture)
	: _diffuseTexture(pDiffuseTexture), _light(light)
{
	_lazyInitializeShader();
}

void ShadowMaterial::_lazyInitializeShader()
{
	if (!_shader)
	{
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "shadowMapGenerator.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "shadowMapGenerator.fs");
		_shader->finalize();
	}
}

ShadowMaterial::~ShadowMaterial()
{
}

void ShadowMaterial::render(World * pWorld, Mesh * pMesh, const glm::mat4 & pModelMatrix, const glm::mat4 & pViewMatrix, const glm::mat4 & pProjectionMatrix)
{
	//_shader->use();
}