#ifndef TOWERDEFENSESCENE_HPP
#define TOWERDEFENSESCENE_HPP

#include "mge/core/AbstractGame.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/materials/TextureGridMaterial.hpp"
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"
#include "Lua/lua.hpp"
#include "mge/core/UIManager.hpp"

class DebugHud;

class TowerDefenseScene : public AbstractGame
{

	public:
	TowerDefenseScene();
	virtual ~TowerDefenseScene();

	//override initialize so we can add a DebugHud
	virtual void initialize();

	//Lua global variables
	bool Debug;
	int WindowHeight;
	int WindowWidth;

	protected:
	//override so we can construct the actual scene
	virtual void _initializeScene();

	//override render to render the hud as well.
	virtual void _render();

	private:
	DebugHud* _hud;                   //hud display
	UIManager* _uiManager;
	Camera* _camera;
	GameObject* _plane;
	LitTextureGridMaterial* _mat;
	LitDynamicTextureGridMaterial* _matD;
	lua_State* lua;

	void _updateHud();
	void updateUIElements();
	void initializeLua();

	int intFromLua(std::string pVariableName);
	float floatFromLua(std::string pVariableName);
	bool boolFromLua(std::string pVariableName);

	TowerDefenseScene(const TowerDefenseScene&);
	TowerDefenseScene& operator=(const TowerDefenseScene&);
};

#endif