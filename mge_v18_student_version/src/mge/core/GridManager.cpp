#include "glm.hpp"
#include "mge/core/GridManager.hpp"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "mge/core/Renderer.hpp"
#include <thread>
#include "mge/materials/TextureGridMaterial.hpp"

GridManager::GridManager(std::vector<GameObject*> pGridObjects, sf::RenderWindow* pWindow) : GameObject("GridManager", glm::vec3(0, 0, 0)), _window(pWindow)
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

	GameObject::update(pStep);
}

void GridManager::InputDetection(sf::Event pEvent)
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
