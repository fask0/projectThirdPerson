#include <iostream>
#include <vector>

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"

#include "mge/core/Level.hpp"
#include "mge/core/EnemySpawner.hpp"
#include "mge/core/Waypoint.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/GridManager.hpp"

#include "glm.hpp"
#include "mge/config.hpp"

Level::Level(std::string pName, glm::vec3 pPosition, int pLayers)
	: GameObject(pName, pPosition), _layerAmount(pLayers)
{
	GameController::Levels.push_back(this);
}

Level::~Level()
{
	GameObject::~GameObject();
}

void Level::update(float pStep)
{
	GameObject::update(pStep);
}

void Level::Init()
{
	_enemySpawnPoints.clear();
	_waypoints.clear();
	_layers.clear();
	GameController::GridObjects.clear();
	for (int i = 0; i < _layerAmount; ++i)
	{
		GameObject* o = new GameObject("layer" + std::to_string(i), glm::vec3(0, 0, 0));
		_layers.push_back(o);
	}

	for (int i = 0; i < _layers.size(); ++i)
	{
		_layers[i]->setMesh(Mesh::load(config::MGE_MODEL_PATH + "/Levels/" + _name + "/layer" + std::to_string(i)));

		if (i == 0)
		{
			LitDynamicTextureGridMaterial* mat = new LitDynamicTextureGridMaterial(GameController::Lights[0]);
			_layers[i]->setMaterial(mat);
			GameController::GridObjects.push_back(_layers[i]);
			GameController::MainPlane = _layers[i];
			GameController::MainPlaneMaterial = mat;
		}
		else
		{
			LitDynamicTextureGridMaterial* mat = new LitDynamicTextureGridMaterial(GameController::Lights[0], true);
			_layers[i]->setMaterial(mat);
		}

		if (_layers[i]->getMesh()->collidersInMesh.size() > 0)
		{
			for (auto &obj : _layers[i]->getMesh()->collidersInMesh)
			{
				if (dynamic_cast<EnemySpawner*>(obj))
					_enemySpawnPoints.push_back(dynamic_cast<EnemySpawner*>(obj));
				else if (dynamic_cast<Waypoint*>(obj))
					_waypoints.push_back(dynamic_cast<Waypoint*>(obj));

				this->add(obj);
			}
		}

		this->add(_layers[i]);
	}

	GridManager* gridManager = new GridManager(GameController::GridObjects, GameController::Window, this);
	this->add(gridManager);
	GameController::TowerDefenseScene->SetGridManager(gridManager);
}

void Level::reset()
{
	while (_children.size() > 0)
	{
		GameObject* child = _children[0];
		remove(child);
		delete child;
	}
	_parent->remove(this);
}
