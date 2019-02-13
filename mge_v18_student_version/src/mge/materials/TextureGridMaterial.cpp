#include "glm.hpp"

#include "TextureGridMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"

ShaderProgram* TextureGridMaterial::_shader = NULL;

GLint TextureGridMaterial::_uMVPMatrix = 0;
GLint TextureGridMaterial::_uModelMatrix = 0;
GLint TextureGridMaterial::_uDiffuseTexture = 0;
GLint TextureGridMaterial::_uMousePos = 0;
GLint TextureGridMaterial::_uGridVisible = 0;
GLint TextureGridMaterial::_uLineThiccness = 0;
GLint TextureGridMaterial::_uGridSize = 0;

GLint TextureGridMaterial::_aVertex = 0;
GLint TextureGridMaterial::_aNormal = 0;
GLint TextureGridMaterial::_aUV = 0;

TextureGridMaterial::TextureGridMaterial(Texture * pDiffuseTexture) :_diffuseTexture(pDiffuseTexture), _gridShowing(true)
{
	_lazyInitializeShader();
}

TextureGridMaterial::~TextureGridMaterial() {}

void TextureGridMaterial::_lazyInitializeShader()
{
	if (!_shader)
	{
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "textureGrid.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "textureGrid.fs");
		_shader->finalize();

		//cache all the uniform and attribute indexes
		_uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
		_uModelMatrix = _shader->getUniformLocation("modelMatrix");
		_uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");
		_uMousePos = _shader->getUniformLocation("mousePos");
		_uGridVisible = _shader->getUniformLocation("gridVisible");
		_uLineThiccness = _shader->getUniformLocation("lineThiccness");
		_uGridSize = _shader->getUniformLocation("gridSize");

		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
		_aUV = _shader->getAttribLocation("uv");
	}
}

void TextureGridMaterial::setDiffuseTexture(Texture* pDiffuseTexture)
{
	_diffuseTexture = pDiffuseTexture;
}

void TextureGridMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	if (!_diffuseTexture) return;

	_shader->use();

	//Print the number of lights in the scene and the position of the first light.
	//It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
	//if (pWorld->getLightCount() > 0) {
	//    std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
	//}

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
	//tell the shader the texture slot for the diffuse texture is slot 0
	glUniform1i(_uDiffuseTexture, 0);

	//pass in a precalculate mvp matrix (see texture material for the opposite)
	glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
	glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	glUniformMatrix4fv(_uModelMatrix, 1, GL_FALSE, glm::value_ptr(pModelMatrix));
	glUniform1i(_uGridVisible, _gridShowing);
	glUniform1f(_uGridSize, _gridSize);
	glUniform1f(_uLineThiccness, _lineThiccness);
	glUniform3fv(_uMousePos, 1, glm::value_ptr(_mousePos));

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}

void TextureGridMaterial::setHighlightArea(glm::vec3 mousePos)
{
	_mousePos = mousePos;
}

void TextureGridMaterial::toggleGrid()
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

void TextureGridMaterial::setGridSize(float size)
{
	_gridSize = size;
}

float TextureGridMaterial::getGridSize()
{
	return _gridSize;
}

void TextureGridMaterial::setLineThiccness(float thiccness)
{
	_lineThiccness = thiccness;
}

float TextureGridMaterial::getLineThiccness()
{
	return _lineThiccness;
}
