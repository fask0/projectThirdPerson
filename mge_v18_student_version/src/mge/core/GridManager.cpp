#include "glm.hpp"
#include "mge/core/GridManager.hpp"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "mge/core/Renderer.hpp"
#include <thread>
#include "mge/materials/TextureGridMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Camera.hpp"
#include "mge/config.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/behaviours/FollowMouseOnGridBehaviour.hpp"
#include "glm.hpp"

GridManager::GridManager(std::vector<GameObject*> pGridObjects, sf::RenderWindow* pWindow, World* pWorld) : GameObject("GridManager", glm::vec3(0, 0, 0)), _window(pWindow), _world(pWorld)
{
	for each (GameObject* obj in pGridObjects)
	{
		_gridObjects.push_back(obj);
		std::cout << obj->getName() << std::endl;
	}
}

GridManager::~GridManager()
{
	//dtor
}

void GridManager::update(float pStep)
{
	if (_tower == nullptr)
		CheckIfMouseOverTower();

	GameObject::update(pStep);
}

void GridManager::CheckIfMouseOverTower()
{
	bool mousingOverTower = false;
	for each (Tower* tower in _placedTowers)
	{
		Camera* _camera = _world->getMainCamera();
		glm::vec3 normalizedDiff = _camera->rayCastNormalizedDiffVec();

		glm::vec3 cameraToPlane = tower->getWorldPosition() - _camera->getWorldPosition();
		glm::vec3 parallel = glm::dot(cameraToPlane, normalizedDiff) * normalizedDiff;
		glm::vec3 perpendicular = cameraToPlane - parallel;

		float distance = glm::length(perpendicular);

		glm::mat4 transform = tower->getTransform();
		if (distance < glm::min(transform[0].length(), transform[2].length()))
		{
			if (_mouseOverTower != nullptr && _mouseOverTower != _selectedTower)
				_mouseOverTower->ResetMaterial();

			_mouseOverTower = tower;
			_mouseOverTower->setMaterial(new ColorMaterial(glm::vec4(0, 0, 1, 1.0f)));
			mousingOverTower = true;
		}
	}

	if (!mousingOverTower)
	{
		if (_mouseOverTower != nullptr  && _mouseOverTower != _selectedTower)
			_mouseOverTower->ResetMaterial();

		_mouseOverTower = nullptr;
	}
}

void GridManager::InputDetection(sf::Event pEvent)
{
	GridControls(pEvent);
	TowerPlacementControls(pEvent);
	TowerSelectionControls(pEvent);
}

void GridManager::GridControls(sf::Event pEvent)
{
	switch (pEvent.type)
	{
	case sf::Event::KeyPressed:
		switch (pEvent.key.code)
		{
		case sf::Keyboard::Key::G:
			for each (GameObject* obj in _gridObjects)
			{
				dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->toggleGrid();
				std::cout << "Toggled Grid" << std::endl;
			}
			break;
		case sf::Keyboard::Key::O:
			for each (GameObject* obj in _gridObjects)
			{
				TextureGridMaterial* material = dynamic_cast<TextureGridMaterial*>(obj->getMaterial());
				material->setGridSize(material->getGridSize() + 0.5f);
				std::cout << "Set grid size to: " + std::to_string(material->getGridSize()) << std::endl;
			}
			break;
		case sf::Keyboard::Key::P:
			for each (GameObject* obj in _gridObjects)
			{
				TextureGridMaterial* material = dynamic_cast<TextureGridMaterial*>(obj->getMaterial());
				material->setGridSize(material->getGridSize() - 0.5f);
				std::cout << "Set grid size to: " + std::to_string(material->getGridSize()) << std::endl;
			}
			break;
		case sf::Keyboard::Key::K:
			for each (GameObject* obj in _gridObjects)
			{
				TextureGridMaterial* material = dynamic_cast<TextureGridMaterial*>(obj->getMaterial());
				material->setLineThiccness(material->getLineThiccness() + 0.05f);
				std::cout << "Set line thiccness to: " + std::to_string(material->getLineThiccness()) << std::endl;
			}
			break;
		case sf::Keyboard::Key::L:
			for each (GameObject* obj in _gridObjects)
			{
				TextureGridMaterial* material = dynamic_cast<TextureGridMaterial*>(obj->getMaterial());
				material->setLineThiccness(material->getLineThiccness() - 0.05f);
				std::cout << "Set line thiccness to: " + std::to_string(material->getLineThiccness()) << std::endl;
			}
			break;
		}
		break;
	}
}

void GridManager::TowerPlacementControls(sf::Event pEvent)
{
	if (pEvent.type == sf::Event::KeyPressed)
	{
		TextureGridMaterial* material = dynamic_cast<TextureGridMaterial*>(_gridObjects[0]->getMaterial());
		ColorMaterial* colorMaterial = new ColorMaterial(glm::vec4(0.4f, 0.4f, 0.9f, 0.7f));

		Mesh* towerMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_smooth.obj");
		FollowMouseOnGridBehaviour* behaviour = new FollowMouseOnGridBehaviour(material);

		float gSize = material->getGridSize();
		std::cout << gSize << std::endl;

		glm::vec3 mousePos = material->getMousePos();
		glm::vec3 pos = (glm::floor(mousePos / gSize) * gSize) + glm::vec3(gSize / 2, 0, gSize / 2);

		switch (pEvent.key.code)
		{
		case sf::Keyboard::Key::Num1:
			if (_tower != nullptr)
			{
				_world->remove(_tower);
				delete(_tower);
			}
			else
			{
				for each (GameObject* obj in _gridObjects)
				{
					dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setGrid(true);
					dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setRangeShowing(true);
					std::cout << "Toggled Grid" << std::endl;
				}
			}

			ResetMouseOverAndSelected();
			_tower = new Tower("Tower1", pos, 8);

			for each (GameObject* obj in _gridObjects)
			{
				dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setRange(8);
			}

			towerMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_smooth.obj");
			_tower->scale(glm::vec3(2.5f, 2.5f, 2.5f));
			_tower->setMesh(towerMesh);
			_tower->setMaterial(colorMaterial);
			_tower->addBehaviour(behaviour);
			_world->add(_tower);
			break;
		case sf::Keyboard::Key::Num2:
			if (_tower != nullptr)
			{
				_world->remove(_tower);
				delete(_tower);
			}
			else
			{
				for each (GameObject* obj in _gridObjects)
				{
					dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setGrid(true);
					dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setRangeShowing(true);
					std::cout << "Toggled Grid" << std::endl;
				}
			}

			ResetMouseOverAndSelected();
			towerMesh = Mesh::load(config::MGE_MODEL_PATH + "cylinder_smooth.obj");
			_tower = new Tower("Tower1", pos, 12);

			for each (GameObject* obj in _gridObjects)
			{
				dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setRange(12);
			}

			_tower->scale(glm::vec3(2.5f, 2.5f, 2.5f));
			_tower->setMesh(towerMesh);
			_tower->setMaterial(colorMaterial);
			_tower->addBehaviour(behaviour);
			_world->add(_tower);
			break;
		case sf::Keyboard::Key::Num3:
			if (_tower != nullptr)
			{
				_world->remove(_tower);
				delete(_tower);
			}
			else
			{
				for each (GameObject* obj in _gridObjects)
				{
					dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setGrid(true);
					dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setRangeShowing(true);
					std::cout << "Toggled Grid" << std::endl;
				}
			}

			ResetMouseOverAndSelected();
			towerMesh = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");
			_tower = new Tower("Tower1", pos, 16);

			for each (GameObject* obj in _gridObjects)
			{
				dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setRange(16);
			}

			_tower->scale(glm::vec3(2.5f, 2.5f, 2.5f));
			_tower->setMesh(towerMesh);
			_tower->setMaterial(colorMaterial);
			_tower->addBehaviour(behaviour);
			_world->add(_tower);
			break;
		case sf::Keyboard::Key::Num4:
			if (_tower != nullptr)
			{
				_world->remove(_tower);
				delete(_tower);
			}
			else
			{
				for each (GameObject* obj in _gridObjects)
				{
					dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setGrid(true);
					dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setRangeShowing(true);
					std::cout << "Toggled Grid" << std::endl;
				}
			}

			ResetMouseOverAndSelected();
			towerMesh = Mesh::load(config::MGE_MODEL_PATH + "teapot_smooth.obj");
			_tower = new Tower("Tower1", pos, 12);

			for each (GameObject* obj in _gridObjects)
			{
				dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setRange(12);
			}

			_tower->scale(glm::vec3(2.5f, 2.5f, 2.5f));
			_tower->setMesh(towerMesh);
			_tower->setMaterial(colorMaterial);
			_tower->addBehaviour(behaviour);
			_world->add(_tower);
			break;

		case sf::Keyboard::Key::Escape:
			if (_tower != nullptr)
			{
				_world->remove(_tower);
				delete(_tower);
				_tower = nullptr;

				for each (GameObject* obj in _gridObjects)
				{
					dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setGrid(false);
					dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setRangeShowing(false);
					std::cout << "Toggled Grid" << std::endl;
				}
			}
			break;
		case sf::Keyboard::Key::R:
			if (_tower != nullptr)
				_tower->Rotate90();
			break;
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		if (_tower != nullptr)
		{
			_world->remove(_tower);
			delete(_tower);
			_tower = nullptr;

			for each (GameObject* obj in _gridObjects)
			{
				dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setGrid(false);
				dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setRangeShowing(false);
				std::cout << "Toggled Grid" << std::endl;
			}
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (_tower != nullptr)
		{
			_tower->removeAllBehaviours();
			_tower->ResetMaterial();
			_placedTowers.push_back(_tower);
			_tower = nullptr;

			for each (GameObject* obj in _gridObjects)
			{
				dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setGrid(false);
				dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setRangeShowing(false);
				std::cout << "Toggled Grid" << std::endl;
			}
		}
	}
}

void GridManager::TowerSelectionControls(sf::Event pEvent)
{
	switch (pEvent.key.code)
	{
	case sf::Keyboard::Key::Escape:
		if (_selectedTower != nullptr)
		{
			for each (GameObject* obj in _gridObjects)
			{
				dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setRangeShowing(false);
			}
			_selectedTower->ResetMaterial();
			_selectedTower = nullptr;
		}
		break;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (_mouseOverTower != nullptr)
		{
			if (_selectedTower != nullptr && _selectedTower != _mouseOverTower)
				_selectedTower->ResetMaterial();
			_selectedTower = _mouseOverTower;
			for each (GameObject* obj in _gridObjects)
			{
				dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setRange(_selectedTower->GetRange());
				dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->setRangeShowing(true);
				dynamic_cast<TextureGridMaterial*>(obj->getMaterial())->SetTowerPos(_selectedTower->getLocalPosition());
			}
		}
	}
}

void GridManager::ResetMouseOverAndSelected()
{
	if (_selectedTower != nullptr)
		_selectedTower->ResetMaterial();
	if (_mouseOverTower != nullptr)
		_mouseOverTower->ResetMaterial();

	_selectedTower = nullptr;
	_mouseOverTower = nullptr;
}

void GridManager::ResetAllTowerMaterials()
{
	for each (Tower* tower in _placedTowers)
	{
		tower->ResetMaterial();
	}
}
