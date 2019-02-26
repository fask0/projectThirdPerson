#include "glm.hpp"
#include "mge/core/GridManager.hpp"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "mge/core/Renderer.hpp"
#include <thread>
#include "mge/materials/TextureGridMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/LitSelectedTextureMaterial.hpp"
#include "mge/materials/LitTextureGridMaterial.hpp"
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Camera.hpp"
#include "mge/config.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/behaviours/FollowMouseOnGridBehaviour.hpp"
#include "glm.hpp"
#include "GameController.hpp"

#include "mge/core/ToasterTower.hpp"
#include "mge/core/HoneyTower.hpp"
#include "mge/core/MouseTrapTower.hpp"
#include "mge/core/ShockTower.hpp"

GridManager::GridManager(std::vector<GameObject*> pGridObjects, sf::RenderWindow* pWindow, World* pWorld) : GameObject("GridManager", glm::vec3(0, 0, 0)), _window(pWindow), _world(pWorld)
{
	for each (GameObject* obj in pGridObjects)
	{
		_gridObjects.push_back(obj);
		std::cout << obj->getName() << std::endl;
	}
	material = dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial());
	selectedMaterial = new LitSelectedTextureMaterial(GameController::Lights[0], Texture::load(config::MGE_TEXTURE_PATH + "diffuse2.jpg"));
	selectedMaterial->SetMixIntensity(0.5f);
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
		float xScale = glm::sqrt(transform[0][0] * transform[0][0] + transform[0][1] * transform[0][1] + transform[0][2] * transform[0][2]);
		float zScale = glm::sqrt(transform[2][0] * transform[2][0] + transform[2][1] * transform[2][1] + transform[2][2] * transform[2][2]);
		if (distance < glm::min(xScale, zScale))
		{
			if (_mouseOverTower != nullptr && _mouseOverTower != _selectedTower)
				_mouseOverTower->ResetMaterial();

			_mouseOverTower = tower;
			_mouseOverTower->setMaterial(selectedMaterial);
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

void GridManager::SpecificTowerSelection(sf::Event pEvent)
{
	FollowMouseOnGridBehaviour* behaviour = new FollowMouseOnGridBehaviour(material);
	Mesh* towerMesh;

	switch (pEvent.key.code)
	{
	case sf::Keyboard::Key::Num1:
		towerMesh = ToasterTower::Mesh;
		_tower = new ToasterTower();
		break;
	case sf::Keyboard::Key::Num2:
		towerMesh = HoneyTower::Mesh;
		_tower = new HoneyTower();
		break;
	case sf::Keyboard::Key::Num3:
		towerMesh = MouseTrapTower::Mesh;
		_tower = new MouseTrapTower();
		break;
	case sf::Keyboard::Key::Num4:
		towerMesh = ShockTower::Mesh;
		_tower = new ShockTower();
		break;
	}

	//After tower has been specified
	if (_gridObjects.size() > 0)
	{
		dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial())->setRange(_tower->GetRange());
	}
	_tower->scale(glm::vec3(0.5f, 0.5f, 0.5f));
	_tower->setMesh(towerMesh);
	_tower->setMaterial(selectedMaterial);
	_tower->addBehaviour(behaviour);
	_world->add(_tower);
}

void GridManager::TowerPlacementControls(sf::Event pEvent)
{
	//Check for keyboard input
	if (pEvent.type == sf::Event::KeyPressed)
	{
		//Check wether player is trying to place a tower
		if (pEvent.key.code == sf::Keyboard::Key::Num1 ||
			pEvent.key.code == sf::Keyboard::Key::Num2 ||
			pEvent.key.code == sf::Keyboard::Key::Num3 ||
			pEvent.key.code == sf::Keyboard::Key::Num4)
		{
			if (_tower != nullptr)
			{
				_world->remove(_tower);
				delete(_tower);
			}
			else
			{
				if (_gridObjects.size() > 0)
				{
					dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial())->setGrid(true);
					dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial())->setRangeShowing(true);
					std::cout << "Toggled Grid" << std::endl;
				}
			}
			ResetMouseOverAndSelected();
			SpecificTowerSelection(pEvent);
		}

		switch (pEvent.key.code)
		{
		case sf::Keyboard::Key::Escape:
			if (_tower != nullptr)
			{
				_world->remove(_tower);
				delete(_tower);
				_tower = nullptr;

				if (_gridObjects.size() > 0)
				{
					dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial())->setGrid(false);
					dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial())->setRangeShowing(false);
					dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial())->setColliding(false);
					selectedMaterial->SetColliding(false);
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

			if (_gridObjects.size() > 0)
			{
				dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial())->setGrid(false);
				dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial())->setRangeShowing(false);
				dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial())->setColliding(false);
				selectedMaterial->SetColliding(false);
				std::cout << "Toggled Grid" << std::endl;
			}
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (_tower != nullptr && !_tower->isColliding)
		{
			//_tower->removeBehaviour(_tower->getBehaviours()[1]);
			std::vector<AbstractBehaviour*> list = _tower->getBehaviours();
			_tower->removeBehaviourAtIndex(1);
			_tower->ResetMaterial();
			_placedTowers.push_back(_tower);
			_tower->AddTowerBehaviour();
			_tower = nullptr;

			if (_gridObjects.size() > 0)
			{
				dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial())->setGrid(false);
				dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial())->setRangeShowing(false);
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
			if (_gridObjects.size() > 0)
			{
				dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial())->setRangeShowing(false);
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
			if (_gridObjects.size() > 0)
			{
				dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial())->setRange(_selectedTower->GetRange());
				dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial())->setRangeShowing(true);
				dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial())->SetTowerPos(_selectedTower->getLocalPosition());
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

void GridManager::GridControls(sf::Event pEvent)
{
	if (GameController::Debug)
	{
		switch (pEvent.type)
		{
		case sf::Event::KeyPressed:
			switch (pEvent.key.code)
			{
			case sf::Keyboard::Key::G:
				if (_gridObjects.size() > 0)
				{
					dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial())->toggleGrid();
					std::cout << "Toggled Grid" << std::endl;
				}
				break;
			case sf::Keyboard::Key::O:
				if (_gridObjects.size() > 0)
				{
					LitDynamicTextureGridMaterial* material = dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial());
					material->setGridSize(material->getGridSize() + 0.1f);
					std::cout << "Set grid size to: " + std::to_string(material->getGridSize()) << std::endl;
				}
				break;
			case sf::Keyboard::Key::P:
				if (_gridObjects.size() > 0)
				{
					LitDynamicTextureGridMaterial* material = dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial());
					material->setGridSize(material->getGridSize() - 0.1f);
					std::cout << "Set grid size to: " + std::to_string(material->getGridSize()) << std::endl;
				}
				break;
			case sf::Keyboard::Key::K:
				if (_gridObjects.size() > 0)
				{
					LitDynamicTextureGridMaterial* material = dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial());
					material->setLineThiccness(material->getLineThiccness() + 0.01f);
					std::cout << "Set line thiccness to: " + std::to_string(material->getLineThiccness()) << std::endl;
				}
				break;
			case sf::Keyboard::Key::L:
				if (_gridObjects.size() > 0)
				{
					LitDynamicTextureGridMaterial* material = dynamic_cast<LitDynamicTextureGridMaterial*>(_gridObjects[0]->getMaterial());
					material->setLineThiccness(material->getLineThiccness() - 0.01f);
					std::cout << "Set line thiccness to: " + std::to_string(material->getLineThiccness()) << std::endl;
				}
				break;
			}
			break;
		}
	}
}
