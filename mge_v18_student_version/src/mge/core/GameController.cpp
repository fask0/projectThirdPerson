#include <iostream>
#include <string>

#include "glm.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/behaviours/CameraMovementBehaviour.hpp"
#include "mge/behaviours/CollisionBehaviour.hpp"
#include "mge/config.hpp"
#include "mge/core/Texture.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"

#include "mge/core/ToasterTower.hpp"
#include "mge/core/HoneyTower.hpp"
#include "mge/core/ShockTower.hpp"
#include "mge/core/IceTower.hpp"
#include "mge/core/MagnifyingGlassTower.hpp"
#include "mge/core/SniperTower.hpp"

#include "mge/core/ToasterProjectile.hpp"
#include "mge/core/HoneyProjectile.hpp"
#include "mge/core/IceProjectile.hpp"

#include "mge/core/Level.hpp"
#include "mge/core/TableLevel.hpp"
#include "mge/core/TutorialLevel.hpp"
#include "mge/core/FridgeLevel.hpp"

#include "mge/TowerDefenseScene.hpp"

#include "mge/core/Waypoint.hpp"
#include "mge/core/EnemySpawner.hpp"

#include "mge/core/Enemy.hpp"
#include "mge/core/Rat.hpp"
#include "mge/core/ChadRat.hpp"
#include "mge/core/SanicRat.hpp"
#include "mge/core/Light.hpp"

std::vector<Light*> GameController::Lights;
std::vector<Level*> GameController::Levels;
std::vector<Enemy*> GameController::Enemies;
std::vector<GameObject*> GameController::GameObjects;
std::vector<GameObject*> GameController::GridObjects;
std::vector<EnemySpawner*> GameController::SpawnPoints;
std::vector<Waypoint*> GameController::Waypoints;

TowerDefenseScene* GameController::TowerDefenseScene;
Camera* GameController::MainCamera;
CameraMovementBehaviour* GameController::CameraBehaviour;
World* GameController::World;
sf::RenderWindow* GameController::Window;
UIManager* GameController::UIManager;
GridManager* GameController::GridManager;
Level* GameController::CurrentLevel;
GameObject* GameController::MainPlane;
LitDynamicTextureGridMaterial* GameController::MainPlaneMaterial;

int GameController::WindowWidth;
int GameController::WindowHeight;

bool GameController::IsGamePaused;

//--Healthbars
Mesh* GameController::HealthBarMesh;
AbstractMaterial* GameController::HealthBarMaterial;

//--Lua variables
bool GameController::Debug = false;
bool GameController::DrawColliders;
int GameController::MaxHealth;
int GameController::CurrentHealth;

//Level
//Spawners and Scaling
//Lane A
int GameController::LaneOneBaseSize;
int GameController::LaneOneSizeGrowthFrequency;
int GameController::LaneOneEnemyScalingPercentage;
float GameController::LaneOneDelayBetweenEnemies;
//Lane B
int GameController::LaneTwoBaseSize;
int GameController::LaneTwoSizeGrowthFrequency;
int GameController::LaneTwoEnemyScalingPercentage;
float GameController::LaneTwoDelayBetweenEnemies;
//Lane C
int GameController::LaneThreeBaseSize;
int GameController::LaneThreeSizeGrowthFrequency;
int GameController::LaneThreeEnemyScalingPercentage;
float GameController::LaneThreeDelayBetweenEnemies;
//Lane D
int GameController::LaneFourBaseSize;
int GameController::LaneFourSizeGrowthFrequency;
int GameController::LaneFourEnemyScalingPercentage;
float GameController::LaneFourDelayBetweenEnemies;

//Towers
int GameController::StartingMoney;
//Toaster tower
float GameController::ToasterRange;
float GameController::ToasterAttSpeed;
int GameController::ToasterCost;
int GameController::ToasterDamage;
//Honey tower
float GameController::HoneyRange;
float GameController::HoneyAttSpeed;
int GameController::HoneyCost;
int GameController::HoneySlowAmount;
//Shock tower
float GameController::ShockRange;
float GameController::ShockAttSpeed;
int GameController::ShockCost;
float GameController::ShockDamage;
//Ice tower
float GameController::IceRange;
float GameController::IceAttSpeed;
float GameController::IceFreezeTime;
int GameController::IceCost;
int GameController::IceDamage;
//Magnifying glass tower
float GameController::MagnifyingRange;
float GameController::MagnifyingFireDamage;
float GameController::MagnifyingFireRate;
float GameController::MagnifyingFireDuration;
int GameController::MagnifyingCost;
//Sniper tower
float GameController::SniperRange;
float GameController::SniperAttSpeed;
int GameController::SniperCost;
int GameController::SniperDamage;

//Enemies
//Rat
int GameController::RatSize;
int GameController::RatHealth;
int GameController::RatHealthRegen;
int GameController::RatDamage;
float GameController::RatSpeed;
float GameController::RatEffectRecoverySpeed;
//ChadRat
int GameController::ChadSize;
int GameController::ChadHealth;
int GameController::ChadHealthRegen;
int GameController::ChadDamage;
float GameController::ChadSpeed;
float GameController::ChadEffectRecoverySpeed;
//SanicRat
int GameController::SanicSize;
int GameController::SanicHealth;
int GameController::SanicHealthRegen;
int GameController::SanicDamage;
float GameController::SanicSpeed;
float GameController::SanicEffectRecoverySpeed;
//--End of Lua variables

unsigned int GameController::shadowMap;
glm::mat4* GameController::lightSpaceMatrix;

GameController::GameController() : GameObject("GameController", glm::vec3(0.0f, 0.0f, 0.0f))
{
}

GameController::~GameController()
{
}

void GameController::Init()
{
	SetUpLevels();
	SetTowerVariables();
	SetUpEnemies();
}

void GameController::LoadLevel(int pLevel)
{
	CurrentLevel->reset();
	CurrentLevel = nullptr;
	if (pLevel >= Levels.size())
	{
		//Load win level/screen
		return;
	}
	CurrentLevel = Levels[pLevel];
	CurrentLevel->Init();
	World->add(CurrentLevel);
}

void GameController::LoadNextLevel()
{
	if (CurrentLevel == nullptr)
	{
		CurrentLevel = Levels[0];
		std::cout << "Loading level: " + CurrentLevel->getName() + "...\n";
		CurrentLevel->Init();
		World->add(CurrentLevel);
		return;
	}

	for (int i = 0; i < Levels.size(); ++i)
	{
		if (Levels[i] == CurrentLevel)
		{
			CurrentLevel->reset();
			if (i + 1 < Levels.size())
			{
				CurrentLevel = Levels[i + 1];
				std::cout << "Loading level: " + CurrentLevel->getName() + "...\n";
				CurrentLevel->Init();
				World->add(CurrentLevel);
				return;
			}
			else
			{
				//Load win level/screen
				CurrentLevel = Levels[0];
				std::cout << "Congratz! You've gone through all the levels\nResetting...\nLoading level: " + CurrentLevel->getName() + "...\n";
				CurrentLevel->Init();
				World->add(CurrentLevel);
				return;
			}
		}
	}
}

void GameController::ReplayLevel()
{
	for (int i = 0; i < Levels.size(); ++i)
	{
		if (Levels[i] == CurrentLevel)
		{
			CurrentLevel->reset();
			CurrentLevel = nullptr;
			CurrentLevel = Levels[i];
			CurrentLevel->Init();
			World->add(CurrentLevel);
			return;
		}
	}
}

void GameController::SetUpLevels()
{
	FridgeLevel* l2 = new FridgeLevel("FridgeLevel", glm::vec3(0, 0, 0), 4);
	TutorialLevel* l0 = new TutorialLevel("TutotialLevel", glm::vec3(0, 0, 0), 2);
	TableLevel* l1 = new TableLevel("TableLevel", glm::vec3(0, 0, 0), 4);
}

void GameController::SetTowerVariables()
{
	ToasterProjectile::Mesh = Mesh::load(config::MGE_MODEL_PATH + "Towers/KnifeProjectile");
	ToasterProjectile::Material = new  LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "knife.png"));
	HoneyProjectile::Mesh = Mesh::load(config::MGE_MODEL_PATH + "Towers/KnifeProjectile");
	HoneyProjectile::Material = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "knife.png"));
	IceProjectile::Mesh = Mesh::load(config::MGE_MODEL_PATH + "Towers/KnifeProjectile");
	IceProjectile::Material = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "knife.png"));

	//Slingshot tower
	ToasterTower::Mesh = Mesh::load(config::MGE_MODEL_PATH + "Towers/ToasterTower");
	ToasterTower::Material = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "toaster.png"));
	//Honey tower
	HoneyTower::MainMesh = Mesh::load(config::MGE_MODEL_PATH + "Towers/HoneyTower");
	HoneyTower::MouseMesh = Mesh::load(config::MGE_MODEL_PATH + "Towers/HoneyTowerMouse");
	HoneyTower::MainMaterial = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "HoneyPot.png"));
	HoneyTower::MouseMaterial = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "MouseTexture.png"));
	//Shock tower
	ShockTower::MainMesh = Mesh::load(config::MGE_MODEL_PATH + "Towers/AoETower");
	ShockTower::Animations.push_back(Mesh::load(config::MGE_MODEL_PATH + "Towers/AoETowerAnimations0"));
	ShockTower::Animations.push_back(Mesh::load(config::MGE_MODEL_PATH + "Towers/AoETowerAnimations1"));
	ShockTower::Animations.push_back(Mesh::load(config::MGE_MODEL_PATH + "Towers/AoETowerAnimations2"));
	ShockTower::Animations.push_back(Mesh::load(config::MGE_MODEL_PATH + "Towers/AoETowerAnimations3"));
	ShockTower::AnimationMaterial = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "AoEBattery.png"));
	//Ice tower
	IceTower::Mesh = Mesh::load(config::MGE_MODEL_PATH + "Towers/IceTower");
	//Magnifying glass tower
	MagnifyingGlassTower::Mesh = Mesh::load(config::MGE_MODEL_PATH + "Towers/MagnifyingGlassTower");
	//Sniper tower
	SniperTower::Mesh = Mesh::load(config::MGE_MODEL_PATH + "Towers/SniperTower");
}

void GameController::SetUpEnemies()
{
	//Collider Mesh
	CollisionBehaviour::BoxMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_smooth");
	CollisionBehaviour::SphereMesh = Mesh::load(config::MGE_MODEL_PATH + "sphere4");

	//Rat
	Rat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Normie/normie0"));
	Rat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Normie/normie1"));
	Rat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Normie/normie2"));
	Rat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Normie/normie3"));
	Rat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Normie/normie4"));
	Rat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Normie/normie5"));
	Rat::Texture = Texture::load(config::MGE_TEXTURE_PATH + "Normie.png");
	Rat::Material = new LitTextureMaterial(Rat::Texture);
	//ChadRat
	ChadRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Chad/chad0"));
	ChadRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Chad/chad1"));
	ChadRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Chad/chad2"));
	ChadRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Chad/chad3"));
	ChadRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Chad/chad4"));
	ChadRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Chad/chad5"));
	ChadRat::Texture = Texture::load(config::MGE_TEXTURE_PATH + "ChadTexture.png");
	ChadRat::Material = new LitTextureMaterial(ChadRat::Texture);
	//SanicRat
	//SanicRat::Mesh = Mesh::load(config::MGE_MODEL_PATH + "Enemies/fastboi");
	SanicRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/FastBoi/fastboi0"));
	SanicRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/FastBoi/fastboi1"));
	SanicRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/FastBoi/fastboi2"));
	SanicRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/FastBoi/fastboi3"));
	SanicRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/FastBoi/fastboi4"));
	SanicRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/FastBoi/fastboi5"));
	SanicRat::Texture = Texture::load(config::MGE_TEXTURE_PATH + "FastBoi.png");
	SanicRat::Material = new LitTextureMaterial(SanicRat::Texture);
}