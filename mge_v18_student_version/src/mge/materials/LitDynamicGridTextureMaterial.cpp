#include "glm.hpp"

#include "mge/materials/LitDynamicGridTextureMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/GameController.hpp"

ShaderProgram* LitDynamicTextureGridMaterial::_shader = NULL;

LitDynamicTextureGridMaterial::LitDynamicTextureGridMaterial(Light *light, Texture * pDiffuseTexture, bool pHideGrid)
	: _diffuseTexture(pDiffuseTexture), _light(light)
{
	//every time we create an instance of LitMaterial we check if the corresponding shader has already been loaded
	_hideGrid = pHideGrid;
	_gridShowing = false;
	_lazyInitializeShader();
}

void LitDynamicTextureGridMaterial::_lazyInitializeShader()
{
	//this shader contains everything the material can do (it can render something in 3d using a single color)
	if (!_shader)
	{
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "litDynamicTextureGrid.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "litDynamicTextureGrid.fs");
		_shader->finalize();
	}
}

LitDynamicTextureGridMaterial::~LitDynamicTextureGridMaterial()
{
	//dtor
}

void LitDynamicTextureGridMaterial::setDiffuseTexture(Texture* pDiffuseTexture)
{
	_diffuseTexture = pDiffuseTexture;
}

void LitDynamicTextureGridMaterial::AddLight(Light * light)
{
	_lights.push_back(light);
}

void LitDynamicTextureGridMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	_shader->use();

	for (int i = 0; i < pMesh->objectTextures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		_diffuseTexture = pMesh->objectTextures[i];
		glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
		glUniform1i(_shader->getUniformLocation("textures[" + std::to_string(i) + "]"), i);
		glUniform1i(_shader->getUniformLocation("splitter[" + std::to_string(i) + "]"), pMesh->objectVertexIndex[i]);
	}

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
	glUniform1i(_shader->getUniformLocation("isColliding"), _isColliding);
	glUniform1f(_shader->getUniformLocation("gridSize"), _gridSize);
	glUniform1f(_shader->getUniformLocation("range"), _range);
	glUniform1f(_shader->getUniformLocation("lineThiccness"), _lineThiccness);
	glUniform3fv(_shader->getUniformLocation("mousePos"), 1, glm::value_ptr(_mousePos));
	glUniform3fv(_shader->getUniformLocation("towerPos"), 1, glm::value_ptr(_towerPos));

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(
		_shader->getAttribLocation("vertex"),
		_shader->getAttribLocation("normal"),
		_shader->getAttribLocation("uv"));
}

void LitDynamicTextureGridMaterial::setHighlightArea(glm::vec3 mousePos)
{
	_mousePos = mousePos;
}

void LitDynamicTextureGridMaterial::toggleGrid()
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

void LitDynamicTextureGridMaterial::setGrid(bool showGrid)
{
	_gridShowing = showGrid;
	if (_hideGrid)
		_gridShowing = false;
}

void LitDynamicTextureGridMaterial::toggleRangeShowing()
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

void LitDynamicTextureGridMaterial::setRangeShowing(bool showRange)
{
	_showRange = showRange;
	if (_hideGrid)
		_showRange = false;
}

void LitDynamicTextureGridMaterial::setGridSize(float size)
{
	_gridSize = size;
}

float LitDynamicTextureGridMaterial::getGridSize()
{
	return _gridSize;
}

void LitDynamicTextureGridMaterial::setLineThiccness(float thiccness)
{
	_lineThiccness = thiccness;
}

float LitDynamicTextureGridMaterial::getLineThiccness()
{
	return _lineThiccness;
}

glm::vec3 LitDynamicTextureGridMaterial::getMousePos()
{
	return _mousePos;
}

void LitDynamicTextureGridMaterial::setRange(float range)
{
	_range = range;
}

float LitDynamicTextureGridMaterial::getRange()
{
	return _range;
}

void LitDynamicTextureGridMaterial::SetTowerPos(glm::vec3 pTowerPosition)
{
	_towerPos = pTowerPosition;
}

glm::vec3 LitDynamicTextureGridMaterial::getTowerPos()
{
	return _towerPos;
}

void LitDynamicTextureGridMaterial::setColliding(bool pIsColliding)
{
	_isColliding = pIsColliding;
}
