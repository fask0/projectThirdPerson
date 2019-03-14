#ifndef GRIDMANAGER_HPP
#define GRIDMANAGER_HPP

#include <string>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>
#include "mge/core/Renderer.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Tower.hpp"
#include "mge/core/Level.hpp"
#include "mge/materials/LitSelectedTextureMaterial.hpp"
#include "mge/materials/TextureGridMaterial.hpp"
#include "mge/materials/LitTextureGridMaterial.hpp"
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include <time.h>

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world-to-view matrix by taking the inverse of the camera transform.
 * The camera's perspective matrix is used in the MVP matrix creation.
 */
class GridManager : public GameObject
{
public:
	GridManager(std::vector<GameObject*> pGridObjects, sf::RenderWindow* pWindow, Level* pLevel);

	virtual ~GridManager();

	void update(float pStep) override;
	void InputDetection(sf::Event pEvent);

	int _currentMoney;

	void PauseTowerPlacement();
	void SelectTower(int pTowerNumber);
	void SellSelectedTower();

private:
	std::vector<GameObject*> _gridObjects;
	sf::RenderWindow* _window;
	Level* _level;

	//Tower variables
	LitSelectedTextureMaterial* selectedMaterial;
	LitDynamicTextureGridMaterial* material;
	std::vector<Tower*> _placedTowers;
	Tower* _tower = nullptr;
	Tower* _mouseOverTower = nullptr;
	Tower* _selectedTower = nullptr;

	//Input handling
	void CheckIfMouseOverTower();
	void GridControls(sf::Event pEvent);
	void TowerPlacementControls(sf::Event pEvent);
	void TowerSelectionControls(sf::Event pEvent);
	void ResetMouseOverAndSelected();
	void ResetAllTowerMaterials();

	void InitializeUIElements();
	void ShowSelectedTowerUIElements();
	void HideSelectedTowerUIElements();

	AdvancedSprite* _sellButton;

	GridManager(const GridManager&);
	GridManager& operator= (const GridManager&);

	void SpecificTowerSelection(sf::Event pEvent);

	//Pausing placement
	bool _canPlaceTower = true;
	clock_t _startPauseTime;
};

#endif // CAMERA_HPP
