#include "glm.hpp"

#include "LitSelectedTextureMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"

ShaderProgram* LitSelectedTextureMaterial::_shader = NULL;

LitSelectedTextureMaterial::LitSelectedTextureMaterial(Light *light, Texture* pDiffuseTexture) :_diffuseTexture(pDiffuseTexture), _light(light), _mixIntesity(0.0f)
{
	//every time we create an instance of LitMaterial we check if the corresponding shader has already been loaded
	_lazyInitializeShader();
}

void LitSelectedTextureMaterial::_lazyInitializeShader()
{
	//this shader contains everything the material can do (it can render something in 3d using a single color)
	if (!_shader)
	{
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "litSelectedTexture.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "litSelectedTexture.fs");
		_shader->finalize();
	}
}

LitSelectedTextureMaterial::~LitSelectedTextureMaterial()
{
	//dtor
}


void LitSelectedTextureMaterial::setDiffuseTexture(Texture* pDiffuseTexture)
{
	_diffuseTexture = pDiffuseTexture;
}

void LitSelectedTextureMaterial::AddLight(Light * light)
{
	_lights.push_back(light);
}

void LitSelectedTextureMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	_shader->use();

	//set the diffuse texture
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
	//tell the shader the texture slot for the diffuse texture is slot 0
	glUniform1i(_shader->getUniformLocation("diffuseTexture"), 0);

	//pass in all MVP matrices separately
	glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));

	//Light stuff 2
	glUniform3fv(_shader->getUniformLocation("dirLight.lightCol"), 1, glm::value_ptr(_light->_color));
	glUniform3fv(_shader->getUniformLocation("dirLight.lightRot"), 1, glm::value_ptr(_light->getTransform()[1]));

	////Light stuff
	for (int i = 0; i < _lights.size(); i++)
	{
		if (_lights[i]->_lightType == _light->Spotlight)
		{
			glUniform3fv(_shader->getUniformLocation("spotLights[" + std::to_string(i) + "].lightCol"), 1, glm::value_ptr(_lights[i]->_color));
			glUniform3fv(_shader->getUniformLocation("spotLights[" + std::to_string(i) + "].lightPos"), 1, glm::value_ptr(_lights[i]->getWorldPosition()));
			glUniform3fv(_shader->getUniformLocation("spotLights[" + std::to_string(i) + "].lightRot"), 1, glm::value_ptr(_lights[i]->getTransform()[1]));
			glUniform1f(_shader->getUniformLocation("spotLights[" + std::to_string(i) + "].cutOff"), glm::cos(glm::radians(_lights[i]->_startCutOff)));
			glUniform1f(_shader->getUniformLocation("spotLights[" + std::to_string(i) + "].outerCutOff"), glm::cos(glm::radians(_lights[i]->_endCutOff)));
		}
	}

	//Mix intensity
	glUniform1f(_shader->getUniformLocation("mixIntensity"), _mixIntesity);

	//Collision
	glUniform1f(_shader->getUniformLocation("isColliding"), _isColliding);

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(
		_shader->getAttribLocation("vertex"),
		_shader->getAttribLocation("normal"),
		_shader->getAttribLocation("uv")
	);

}

void LitSelectedTextureMaterial::SetMixIntensity(float pIntensity)
{
	_mixIntesity = pIntensity;
}

void LitSelectedTextureMaterial::SetColliding(bool pIsColliding)
{
	_isColliding = pIsColliding;
}
