#include "glm.hpp"

#include "LitTextureGridMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"

ShaderProgram* LitTextureGridMaterial::_shader = NULL;

LitTextureGridMaterial::LitTextureGridMaterial(Light *light, Texture* pDiffuseTexture) :_diffuseTexture(pDiffuseTexture), _light(light)
{
	//every time we create an instance of LitMaterial we check if the corresponding shader has already been loaded
	_lazyInitializeShader();
}

void LitTextureGridMaterial::_lazyInitializeShader()
{
	//this shader contains everything the material can do (it can render something in 3d using a single color)
	if (!_shader)
	{
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "litTextureGrid.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "litTextureGrid.fs");
		_shader->finalize();
	}
}

LitTextureGridMaterial::~LitTextureGridMaterial()
{
	//dtor
}


void LitTextureGridMaterial::setDiffuseTexture(Texture* pDiffuseTexture)
{
	_diffuseTexture = pDiffuseTexture;
}

void LitTextureGridMaterial::AddLight(Light * light)
{
	_lights.push_back(light);
}

void LitTextureGridMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
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

	//Grid stuff
	glUniform1i(_shader->getUniformLocation("gridVisible"), _gridShowing);
	glUniform1i(_shader->getUniformLocation("showRange"), _showRange);
	glUniform1f(_shader->getUniformLocation("gridSize"), _gridSize);
	glUniform1f(_shader->getUniformLocation("range"), _range);
	glUniform1f(_shader->getUniformLocation("lineThiccness"), _lineThiccness);
	glUniform3fv(_shader->getUniformLocation("mousePos"), 1, glm::value_ptr(_mousePos));
	glUniform3fv(_shader->getUniformLocation("towerPos"), 1, glm::value_ptr(_towerPos));

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(
		_shader->getAttribLocation("vertex"),
		_shader->getAttribLocation("normal"),
		_shader->getAttribLocation("uv")
	);

}

void LitTextureGridMaterial::setHighlightArea(glm::vec3 mousePos)
{
	_mousePos = mousePos;
}

void LitTextureGridMaterial::toggleGrid()
{
	if (_gridShowing)
	{
		_gridShowing = false;
	}
	else
	{
		_gridShowing = true;
	}
}

void LitTextureGridMaterial::setGrid(bool showGrid)
{
	_gridShowing = showGrid;
}

void LitTextureGridMaterial::toggleRangeShowing()
{
	if (_showRange)
	{
		_showRange = false;
	}
	else
	{
		_showRange = true;
	}
}

void LitTextureGridMaterial::setRangeShowing(bool showRange)
{
	_showRange = showRange;
}

void LitTextureGridMaterial::setGridSize(float size)
{
	_gridSize = size;
}

float LitTextureGridMaterial::getGridSize()
{
	return _gridSize;
}

void LitTextureGridMaterial::setLineThiccness(float thiccness)
{
	_lineThiccness = thiccness;
}

float LitTextureGridMaterial::getLineThiccness()
{
	return _lineThiccness;
}

glm::vec3 LitTextureGridMaterial::getMousePos()
{
	return _mousePos;
}

void LitTextureGridMaterial::setRange(float range)
{
	_range = range;
}

float LitTextureGridMaterial::getRange()
{
	return _range;
}

void LitTextureGridMaterial::SetTowerPos(glm::vec3 pTowerPosition)
{
	_towerPos = pTowerPosition;
}

glm::vec3 LitTextureGridMaterial::getTowerPos()
{
	return _towerPos;
}
