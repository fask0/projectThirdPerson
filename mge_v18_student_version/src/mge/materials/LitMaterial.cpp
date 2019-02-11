#include "glm.hpp"

#include "LitMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"

ShaderProgram* LitMaterial::_shader = NULL;

LitMaterial::LitMaterial(Light *light, glm::vec3 pDiffuseColor) :_diffuseColor(pDiffuseColor), _light(light)
{
	//every time we create an instance of LitMaterial we check if the corresponding shader has already been loaded
	_lazyInitializeShader();
}

void LitMaterial::_lazyInitializeShader()
{
	//this shader contains everything the material can do (it can render something in 3d using a single color)
	if (!_shader)
	{
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "lit.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "lit.fs");
		_shader->finalize();
	}
}

LitMaterial::~LitMaterial()
{
	//dtor
}

void LitMaterial::setDiffuseColor(glm::vec3 pDiffuseColor)
{
	_diffuseColor = pDiffuseColor;
}

void LitMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	_shader->use();

	//set the material color
	glUniform3fv(_shader->getUniformLocation("diffuseColor"), 1, glm::value_ptr(_diffuseColor));

	//pass in all MVP matrices separately
	glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));

	//Light stuff
	glUniform3fv(_shader->getUniformLocation("lightCol"), 1, glm::value_ptr(_light->_color));
	glUniform3fv(_shader->getUniformLocation("lightPos"), 1, glm::value_ptr(_light->getWorldPosition()));
	glUniform3fv(_shader->getUniformLocation("lightRot"), 1, glm::value_ptr(_light->getTransform()[1]));
	glUniform1f(_shader->getUniformLocation("cutOff"), glm::cos(glm::radians(_light->_startCutOff)));
	glUniform1f(_shader->getUniformLocation("outerCutOff"), glm::cos(glm::radians(_light->_endCutOff)));
	if (_light->_lightType == Light::Directional) 
	{
		glUniform1i(_shader->getUniformLocation("isSpotlight"), false);
	}
	else 
	{
		glUniform1i(_shader->getUniformLocation("isSpotlight"), true);
	}

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(
		_shader->getAttribLocation("vertex"),
		_shader->getAttribLocation("normal"),
		_shader->getAttribLocation("uv")
	);

}
