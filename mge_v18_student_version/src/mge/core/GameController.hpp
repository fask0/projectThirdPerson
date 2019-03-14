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
#include "mge/core/Level.hpp"
#include "mge/core/UIManager.hpp"
#include "mge/core/EnemySpawner.hpp"
#include "mge/core/GridManager.hpp"
#include "mge/TowerDefenseScene.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/MenuManager.hpp"
#include "mge/core/EnemySpawner.hpp"
#include "mge/core/SoundEffects.hpp"

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
	static std::vector<Level*> Levels;
	static std::vector<Enemy*> Enemies;
	static std::vector<GameObject*> GameObjects;
	static std::vector<GameObject*> GridObjects;
	static std::vector<EnemySpawner*> SpawnPoints;
	static std::vector<Waypoint*> Waypoints;

	static TowerDefenseScene* TowerDefenseScene;
	static Camera* MainCamera;
	static CameraMovementBehaviour* CameraBehaviour;
	static World* World;
	static sf::RenderWindow* Window;
	static UIManager* UIManager;
	static GridManager* GridManager;
	static MenuManager* MenuManager;
	static Level* CurrentLevel;
	static GameObject* MainPlane;
	static LitDynamicTextureGridMaterial* MainPlaneMaterial;
	static SoundEffect* MainMenuMusic;
	static SoundEffect* GameplayMusic;

	static glm::mat4 InitialCameraTransform;

	static int WindowWidth;
	static int WindowHeight;
	static float MaxMusicVolume;
	static float MaxSFXVolume;

	static bool IsGamePaused;

	//--Health bar
	static Mesh* HealthBarMesh;
	static AbstractMaterial* HealthBarMaterial;

	//--Lua variables
	static bool Debug;
	static bool DrawColliders;
	static int MaxHealth;
	static int CurrentHealth;

	//Level
	//Spawners and Scaling
	//Lane A
	static int LaneOneNormieFromWave;
	static int LaneOneSanicFromWave;
	static int LaneOneChadFromWave;
	static int LaneOneBaseSize;
	static int LaneOneSizeGrowthFrequency;
	static int LaneOneEnemyScalingPercentage;
	static float LaneOneDelayBetweenEnemies;
	//Lane B
	static int LaneTwoNormieFromWave;
	static int LaneTwoSanicFromWave;
	static int LaneTwoChadFromWave;
	static int LaneTwoBaseSize;
	static int LaneTwoSizeGrowthFrequency;
	static int LaneTwoEnemyScalingPercentage;
	static float LaneTwoDelayBetweenEnemies;
	//Lane C
	static int LaneTreeNormieFromWave;
	static int LaneTreeSanicFromWave;
	static int LaneTreeChadFromWave;
	static int LaneThreeBaseSize;
	static int LaneThreeSizeGrowthFrequency;
	static int LaneThreeEnemyScalingPercentage;
	static float LaneThreeDelayBetweenEnemies;
	//Lane D
	static int LaneFourNormieFromWave;
	static int LaneFourSanicFromWave;
	static int LaneFourChadFromWave;
	static int LaneFourBaseSize;
	static int LaneFourSizeGrowthFrequency;
	static int LaneFourEnemyScalingPercentage;
	static float LaneFourDelayBetweenEnemies;

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
	//ChadRat
	static int ChadSize;
	static int ChadHealth;
	static int ChadHealthRegen;
	static int ChadDamage;
	static float ChadSpeed;
	static float ChadEffectRecoverySpeed;
	//SanicRat
	static int SanicSize;
	static int SanicHealth;
	static int SanicHealthRegen;
	static int SanicDamage;
	static float SanicSpeed;
	static float SanicEffectRecoverySpeed;
	//--End of Lua variables

	static void LoadLevel(int pLevel);
	static void LoadNextLevel();
	static void ReplayLevel();

	static void SetUpLevels();
	//Testing vars
	static glm::mat4* lightSpaceMatrix;
	static unsigned int shadowMap;

	private:
	GameController(const GameController&);
	GameController& operator= (const GameController&);

	void SetTowerVariables();
	void SetUpEnemies();
};

#endif // GAMECONTROLLER_HPP
