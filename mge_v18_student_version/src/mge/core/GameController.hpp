#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "mge/behaviours/CameraMovementBehaviour.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Waypoint.hpp"
#include "mge/core/Enemy.hpp"
#include "mge/core/UIManager.hpp"
#include "mge/core/EnemySpawner.hpp"
#include "mge/core/GridManager.hpp"

#include "mge/materials/LitDynamicGridTextureMaterial.hpp"

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world-to-view matrix by taking the inverse of the camera transform.
 * The camera's perspective matrix is used in the MVP matrix creation.
 */
class GameController : public GameObject
{
public:
	GameController();

	virtual ~GameController();

	void Init();

	static std::vector<Light*> Lights;
	static std::vector<Enemy*> Enemies;
	static std::vector<GameObject*> GameObjects;
	static std::vector<GameObject*> GridObjects;
	static std::vector<EnemySpawner*> SpawnPointsInLevel;
	static std::vector<Waypoint*> WaypointsInLevel;

	static Camera* MainCamera;
	static CameraMovementBehaviour* CameraBehaviour;
	static World* World;
	static sf::RenderWindow* Window;
	static UIManager* UIManager;
	static GridManager* GridManager;

	//--Lua variables
	static bool Debug;
	static bool DrawColliders;

	//Level
	//Spawners and Scaling
	//Lane A
	static int GameController::LaneOneBaseSize;
	static int GameController::LaneOneSizeGrowthFrequency;
	static int GameController::LaneOneEnemyScalingPercentage;
	static float GameController::LaneOneDelayBetweenEnemies;
	//Lane B
	static int GameController::LaneTwoBaseSize;
	static int GameController::LaneTwoSizeGrowthFrequency;
	static int GameController::LaneTwoEnemyScalingPercentage;
	static float GameController::LaneTwoDelayBetweenEnemies;
	//Lane C
	static int GameController::LaneThreeBaseSize;
	static int GameController::LaneThreeSizeGrowthFrequency;
	static int GameController::LaneThreeEnemyScalingPercentage;
	static float GameController::LaneThreeDelayBetweenEnemies;
	//Lane D
	static int GameController::LaneFourBaseSize;
	static int GameController::LaneFourSizeGrowthFrequency;
	static int GameController::LaneFourEnemyScalingPercentage;
	static float GameController::LaneFourDelayBetweenEnemies;

	//Towers
	static int StartingMoney;
	//Toaster tower
	static float ToasterRange;
	static float ToasterAttSpeed;
	static int ToasterCost;
	static int ToasterDamage;
	//Honey tower
	static float HoneyRange;
	static float HoneyAttSpeed;
	static int HoneyCost;
	static int HoneySlowAmount;
	//Shock tower
	static float ShockRange;
	static float ShockAttSpeed;
	static int ShockCost;
	static float ShockDamage;
	//Ice tower
	static float IceRange;
	static float IceAttSpeed;
	static float IceFreezeTime;
	static int IceCost;
	static int IceDamage;
	//Magnifying glass tower
	static float MagnifyingRange;
	static float MagnifyingFireDamage;
	static float MagnifyingFireRate;
	static float MagnifyingFireDuration;
	static int MagnifyingCost;
	//Sniper tower
	static float SniperRange;
	static float SniperAttSpeed;
	static int SniperCost;
	static int SniperDamage;

	//Enemies
	//Rat
	static int RatSize;
	static int RatHealth;
	static int RatHealthRegen;
	static int RatDamage;
	static float RatSpeed;
	static float RatEffectRecoverySpeed;
	//--End of Lua variables

private:
	GameController(const GameController&);
	GameController& operator= (const GameController&);

	void SetTowerVariables();
	void SetUpEnemies();
};

#endif // GAMECONTROLLER_HPP
