#include "glm.hpp"

#include "LitTextureMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/GameController.hpp"

LitTextureMaterial::LitTextureMaterial(Texture* pDiffuseTexture) :_diffuseTexture(pDiffuseTexture)
{
	//every time we create an instance of LitMaterial we check if the corresponding shader has already been loaded
	initShader();
}

void LitTextureMaterial::initShader()
{
	//this shader contains everything the material can do (it can render something in 3d using a single color)
	_shader = new ShaderProgram();
	_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "litTexture.vs");
	_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "litTexture.fs");
	_shader->finalize();
}

LitTextureMaterial::~LitTextureMaterial()
{
	//dtor
	delete _shader;
}


void LitTextureMaterial::setDiffuseTexture(Texture* pDiffuseTexture)
{
	_diffuseTexture = pDiffuseTexture;
}

void LitTextureMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	_shader->use();

	if (!_settingDiffuseTextureManually)
	{
		//set the diffuse texture
		glActiveTexture(GL_TEXTURE0);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
		//tell the shader the texture slot for the diffuse texture is slot 0
		glUniform1i(_shader->getUniformLocation("diffuseTexture"), 0);
	}
	else
	{
		//set the diffuse texture
		glActiveTexture(GL_TEXTURE0);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, _depthMap);
		//tell the shader the texture slot for the diffuse texture is slot 0
		GLuint depthMapLocation = _shader->getUniformLocation("diffuseTexture");
		glUniform1i(depthMapLocation, 0);
		//glUniform1f(_shader->getUniformLocation("near_plane"), 0.1f);
		//glUniform1f(_shader->getUniformLocation("far_plane"), 1000.0f);

	}

	//pass in all MVP matrices separately
	glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));

	//Light stuff 2
	glUniform3fv(_shader->getUniformLocation("dirLight.lightCol"), 1, glm::value_ptr(GameController::Lights[0]->_color));
	glUniform3fv(_shader->getUniformLocation("dirLight.lightRot"), 1, glm::value_ptr(GameController::Lights[0]->getTransform()[1]));

	////Light stuff
	for (int i = 1; i < GameController::Lights.size(); i++)
	{
		if (GameController::Lights[i]->_lightType == 0)
		{
			glUniform3fv(_shader->getUniformLocation("spotLights[" + std::to_string(i) + "].lightCol"), 1, glm::value_ptr(GameController::Lights[i]->_color));
			glUniform3fv(_shader->getUniformLocation("spotLights[" + std::to_string(i) + "].lightPos"), 1, glm::value_ptr(GameController::Lights[i]->getWorldPosition()));
			glUniform3fv(_shader->getUniformLocation("spotLights[" + std::to_string(i) + "].lightRot"), 1, glm::value_ptr(GameController::Lights[i]->getTransform()[1]));
			glUniform1f(_shader->getUniformLocation("spotLights[" + std::to_string(i) + "].cutOff"), glm::cos(glm::radians(GameController::Lights[i]->_startCutOff)));
			glUniform1f(_shader->getUniformLocation("spotLights[" + std::to_string(i) + "].outerCutOff"), glm::cos(glm::radians(GameController::Lights[i]->_endCutOff)));
		}
	}

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(
		_shader->getAttribLocation("vertex"),
		_shader->getAttribLocation("normal"),
		_shader->getAttribLocation("uv")
	);
}

DebugTextureMaterial::DebugTextureMaterial(Texture* pDiffuseTexture) : LitTextureMaterial(pDiffuseTexture)
{
	m_shader = new ShaderProgram();
	m_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "DebugQuadDepth.vs");
	m_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "DebugQuadDepth.fs");
	m_shader->finalize();
}

void DebugTextureMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	m_shader->use();

	//set the diffuse texture
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _depthMap);
	//tell the shader the texture slot for the diffuse texture is slot 0
	GLuint depthMapLocation = m_shader->getUniformLocation("depthMap");
	glUniform1i(depthMapLocation, 0);
	glUniform1f(m_shader->getUniformLocation("near_plane"), _nearPlane);
	glUniform1f(m_shader->getUniformLocation("far_plane"), _farPlane);

	//pass in all MVP matrices separately
	glUniformMatrix4fv(m_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(m_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(m_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(
		m_shader->getAttribLocation("aPos"),
		m_shader->getAttribLocation("aNormal"),
		m_shader->getAttribLocation("aTexCoords")
	);
}
