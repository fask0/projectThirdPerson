#include "glm.hpp"

#include "TerrainMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"

ShaderProgram* TerrainMaterial::_shader = NULL;

GLint TerrainMaterial::_uMVPMatrix = 0;
GLint TerrainMaterial::_uHeightMap = 0;
GLint TerrainMaterial::_uTerrainHeight = 0;

GLint TerrainMaterial::_uSplatMap = 0;
GLint TerrainMaterial::_uDiffuseTexture0 = 0;
GLint TerrainMaterial::_uDiffuseTexture1 = 0;
GLint TerrainMaterial::_uDiffuseTexture2 = 0;
GLint TerrainMaterial::_uDiffuseTexture3 = 0;

GLint TerrainMaterial::_uTime = 0;

GLint TerrainMaterial::_aVertex = 0;
GLint TerrainMaterial::_aNormal = 0;
GLint TerrainMaterial::_aUV = 0;

TerrainMaterial::TerrainMaterial(Texture* pSplatMap, Texture* pDiffuseTexture0, Texture* pDiffuseTexture1, Texture* pDiffuseTexture2, Texture* pDiffuseTexture3, Texture* pHeightMap, float pTerrainHeight):_splatMap(pSplatMap), _diffuseTexture0(pDiffuseTexture0), _diffuseTexture1(pDiffuseTexture1), _diffuseTexture2(pDiffuseTexture2), _diffuseTexture3(pDiffuseTexture3), _heightMap(pHeightMap), _terrainHeight(pTerrainHeight) {
    _lazyInitializeShader();
}

TerrainMaterial::~TerrainMaterial() {}

void TerrainMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"terrain.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"terrain.fs");
        _shader->finalize();

        //cache all the uniform and attribute indexes
        _uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
		_uHeightMap = _shader->getUniformLocation("heightMap");
		_uTerrainHeight = _shader->getUniformLocation("terrainHeight");

		_uSplatMap = _shader->getUniformLocation("splatMap");
		_uDiffuseTexture0 = _shader->getUniformLocation("diffuseTexture0");
		_uDiffuseTexture1 = _shader->getUniformLocation("diffuseTexture1");
		_uDiffuseTexture2 = _shader->getUniformLocation("diffuseTexture2");
		_uDiffuseTexture3 = _shader->getUniformLocation("diffuseTexture3");

		_uTime = _shader->getUniformLocation("time");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV =     _shader->getAttribLocation("uv");
    }
}

void TerrainMaterial::setDiffuseTexture (Texture* pDiffuseTexture) {
    _diffuseTexture0 = pDiffuseTexture;
}

void TerrainMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    if (!_diffuseTexture0) return;

    _shader->use();

    //Print the number of lights in the scene and the position of the first light.
    //It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
    //if (pWorld->getLightCount() > 0) {
    //    std::cout << "TerrainMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
    //}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _heightMap->getId());
	glUniform1i(_uHeightMap, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _splatMap->getId());
	glUniform1i(_uSplatMap, 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture0->getId());
    glUniform1i (_uDiffuseTexture0, 2);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture1->getId());
	glUniform1i(_uDiffuseTexture1, 3);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture2->getId());
	glUniform1i(_uDiffuseTexture2, 4);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture3->getId());
	glUniform1i(_uDiffuseTexture3, 5);

	glUniform1f(_uTime, clock() / 5000.0f);

	glUniform1f(_uTerrainHeight, _terrainHeight);

    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
	glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
