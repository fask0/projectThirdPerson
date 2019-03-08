#ifndef ABSTRACTGAME_HPP
#define ABSTRACTGAME_HPP

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <string>
#include "mge/core/GridManager.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/materials/LitTextureMaterial.hpp"

class World;
class Renderer;

/**
 * Defines the basic structure for a game, with defaults already filled in.
 * The only item that MUST be overridden/implemented is _initializeScene()
 * where you build up your world, the rest is optional to override (with care/caution).
 */
class AbstractGame
{
public:

	AbstractGame();
	virtual ~AbstractGame();

	//creates a window, initializes glew, a renderer and a world instance
	virtual void initialize();
	virtual void initialize(int _windowWidth, int _windowHeight);
	//run the actual process of updating all objects, rendering them and processing events
	virtual void run();

	void SetGridManager(GridManager* pGridManager);

protected:

	//methods above delegate behaviour to the methods below so that you can override it in a subclass

	//initialize sfml rendering context
	virtual void _initializeWindow();
	virtual void _initializeWindow(int _windowWidth, int _windowHeight);
	//print info about the current driver version etc
	virtual void _printVersionInfo();
	//initialize the extension wrangler
	virtual void _initializeGlew();
	//create our own custom renderer instance
	virtual void _initializeRenderer();
	//create depth map
	virtual void _initializeShadowMap();
	//initialize a scene root to which we can attach/add objects
	virtual void _initializeWorld();

	//initialize the actual scene, HAS to be done by a subclass
	virtual void _initializeScene() = 0;

	//call update on all game objects in the display root
	virtual void _update(float pStep);
	//render all game objects in the display root
	virtual void _render();
	//process any sfml window events (see SystemEventDispatcher/Listener)
	virtual void _processEvents();

	sf::RenderWindow* _window;  //sfml window to render into
	Renderer* _renderer;        //the renderer class to render the world
	World* _world;              //the root game object that represents our scene
	float _fps;                 //stores the real fps

	//Shadow map variables
	const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
	unsigned int depthMapFBO;
	unsigned int depthMap;

private:
	AbstractGame(const AbstractGame&);
	AbstractGame& operator=(const AbstractGame&);
	GridManager* gridManager;

	ShaderProgram* _debugQuadShader;
	ShaderProgram* _shadowMapShader;

	LitTextureMaterial* material;
};

#endif // ABSTRACTGAME_HPP
