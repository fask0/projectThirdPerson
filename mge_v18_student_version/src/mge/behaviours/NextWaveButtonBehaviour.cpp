#include "mge/behaviours/NextWaveButtonBehaviour.hpp"
#include "mge/core/AdvancedSprite.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>
#include "mge/core/EnemySpawner.hpp"

NextWaveButtonBehaviour::NextWaveButtonBehaviour() : AbstractBehaviour()
{
	//ctor
}

NextWaveButtonBehaviour::~NextWaveButtonBehaviour()
{
	//dtor
}

void NextWaveButtonBehaviour::update(float pstep)
{
}

void NextWaveButtonBehaviour::On2DMouseClick()
{
	for each (EnemySpawner* enemySpawner in GameController::SpawnPoints)
	{
		enemySpawner->initializeWave();
	}
}