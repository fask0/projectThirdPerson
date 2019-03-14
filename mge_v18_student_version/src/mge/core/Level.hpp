#pragma once

#include <iostream>
#include <vector>

#include "mge/core/GameObject.hpp"
#include "mge/core/EnemySpawner.hpp"
#include "mge/core/Waypoint.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/behaviours/NextWaveButtonBehaviour.hpp"
#include "mge/behaviours/SwitchSpriteOnHoverBehaviour.hpp"
#include "Lua/lua.hpp"

#include "glm.hpp"

class Level : public GameObject
{
public:
	Level(std::string pName = "Level",
		glm::vec3 pPosition = glm::vec3(0, 0, 0),
		int pLayers = 0);
	~Level();
	virtual void update(float pStep) override;

	virtual void Init();
	void reset();

	std::vector<EnemySpawner*> getEnemySpawnPoints() { return _enemySpawnPoints; }
	std::vector<Waypoint*> getWaypoints() { return _waypoints; }
	std::vector<GameObject*> getLayers() { return _layers; }

	void setWave(int pWave) { _currentWave = pWave; }
	int getWave() { return _currentWave; };
	glm::vec4 GetBounds();

protected:
	std::vector<EnemySpawner*> _enemySpawnPoints;
	std::vector<Waypoint*> _waypoints;
	std::vector<GameObject*> _layers;
	int _layerAmount;
	int _currentWave = 0;
	void inintialize2Dobjects();
	float _minX;
	float _maxX;
	float _minZ;
	float _maxZ;

	//Next wave button
	void initializeNextWaveButton();
	void updateNextWaveButton();
	void initLuaVariables();

	float floatFromLua(std::string pVariableName);
	bool boolFromLua(std::string pVariableName);
	int intFromLua(std::string pVariableName);

	AdvancedSprite* _nextWaveButton;

	sf::Texture* _nextWaveButtonTex;
	sf::Texture* _nextWaveButtonSelTex;
	sf::Texture* _waveInProgressButtonTex;
	lua_State* _lua;

	float _lowMusicVolume;
	float _currentMusicVolume;
};
