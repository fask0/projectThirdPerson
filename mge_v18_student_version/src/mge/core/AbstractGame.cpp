#include <iostream>

#include "AbstractGame.hpp"
#include "mge/core/Renderer.hpp"
#include "mge/core/World.hpp"
#include "mge/core/GridManager.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Enemy.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"

AbstractGame::AbstractGame() :_window(NULL), _renderer(NULL), _world(NULL), _fps(0)
{
	//ctor
}

AbstractGame::~AbstractGame()
{
	//dtor
	delete _window;
	delete _renderer;
	delete _world;
}

void AbstractGame::initialize()
{
	std::cout << "Initializing engine..." << std::endl << std::endl;
	_initializeWindow();
	_printVersionInfo();
	_initializeGlew();
	_initializeRenderer();
	_initializeShadowMap();
	_initializeWorld();
	_initializeScene();
	std::cout << std::endl << "Engine initialized." << std::endl << std::endl;
}

void AbstractGame::initialize(int _windowWidth, int _windowHeight)
{
	std::cout << "Initializing engine..." << std::endl << std::endl;
	_initializeWindow(_windowWidth, _windowHeight);
	_printVersionInfo();
	_initializeGlew();
	_initializeRenderer();
	_initializeShadowMap();
	_initializeWorld();
	_initializeScene();
	_window->setKeyRepeatEnabled(false);
	std::cout << std::endl << "Engine initialized." << std::endl << std::endl;
}

///SETUP
void AbstractGame::_initializeWindow()
{
	std::cout << "Initializing window..." << std::endl;
	_window = new sf::RenderWindow(sf::VideoMode(800, 600), "yer mum!", sf::Style::Default, sf::ContextSettings(24, 8, 0, 3, 3));
	//_window->setVerticalSyncEnabled(true);
	GameController::Window = _window;
	std::cout << "Window initialized." << std::endl << std::endl;
}

void AbstractGame::_initializeWindow(int _windowWidth, int _windowHeight)
{
	std::cout << "Initializing window..." << std::endl;
	_window = new sf::RenderWindow(sf::VideoMode(_windowWidth, _windowHeight), "My Game!", sf::Style::Default, sf::ContextSettings(24, 8, 4, 3, 3));
	_window->setMouseCursorVisible(false);
	//_window->setVerticalSyncEnabled(true);
	std::cout << "Window initialized." << std::endl << std::endl;
}

void AbstractGame::_printVersionInfo()
{
	std::cout << "Context info:" << std::endl;
	std::cout << "----------------------------------" << std::endl;
	//print some debug stats for whoever cares
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	//nice consistency here in the way OpenGl retrieves values
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	printf("GL Vendor : %s\n", vendor);
	printf("GL Renderer : %s\n", renderer);
	printf("GL Version (string) : %s\n", version);
	printf("GL Version (integer) : %d.%d\n", major, minor);
	printf("GLSL Version : %s\n", glslVersion);

	std::cout << "----------------------------------" << std::endl << std::endl;
}

void AbstractGame::_initializeGlew()
{
	std::cout << "Initializing GLEW..." << std::endl;
	//initialize the opengl extension wrangler
	GLint glewStatus = glewInit();
	std::cout << "Initialized GLEW, status (1 == OK, 0 == FAILED):" << (glewStatus == GLEW_OK) << std::endl << std::endl;
}

void AbstractGame::_initializeRenderer()
{
	//setup our own renderer
	std::cout << "Initializing renderer..." << std::endl;
	_renderer = new Renderer();
	_renderer->setClearColor(0, 0, 0);
	std::cout << "Renderer done." << std::endl << std::endl;
}

void AbstractGame::_initializeShadowMap()
{
	_debugQuadShader = new ShaderProgram();
	_debugQuadShader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "DebugQuadDepth.vs");
	_debugQuadShader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "DebugQuadDepth.fs");
	_debugQuadShader->finalize();

	_shadowMapShader = new ShaderProgram();
	_shadowMapShader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "ShadowMappingDepth.vs");
	_shadowMapShader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "ShadowMappingDepth.fs");
	_shadowMapShader->finalize();

	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//_debugQuadShader->use();
	//glUniform1i(_debugQuadShader->getUniformLocation("depthMap"), 0);

	material = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "bricks.png"));
}

void AbstractGame::_initializeWorld()
{
	//setup the world
	std::cout << "Initializing world..." << std::endl;
	_world = new World();
	std::cout << "World initialized." << std::endl << std::endl;
}

///MAIN GAME LOOP

void AbstractGame::run()
{
	//setting to calculate fps
	sf::Clock renderClock;
	int frameCount = 0;
	float timeSinceLastFPSCalculation = 0;

	//settings to make sure the update loop runs at 60 fps
	sf::Time timePerFrame = sf::seconds(1.0f / 70.0f);
	sf::Clock updateClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (_window->isOpen())
	{
		timeSinceLastUpdate += updateClock.restart();

		if (timeSinceLastUpdate > timePerFrame)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			while (timeSinceLastUpdate > timePerFrame)
			{
				timeSinceLastUpdate -= timePerFrame;
				_update(timePerFrame.asSeconds());
			}

			_render();
			_window->display();

			//fps count is updated once every 1 second
			frameCount++;
			timeSinceLastFPSCalculation += renderClock.restart().asSeconds();
			if (timeSinceLastFPSCalculation > 1)
			{
				_fps = frameCount / timeSinceLastFPSCalculation;
				timeSinceLastFPSCalculation -= 1;
				frameCount = 0;
			}

		}

		//empty the event queue
		_processEvents();
	}
}

void AbstractGame::SetGridManager(GridManager* pGridManager)
{
	gridManager = pGridManager;
}

void AbstractGame::_update(float pStep)
{
	_world->update(pStep);
}

unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
	if (quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void AbstractGame::_render()
{
	//Create shadow depth map
	glm::mat4 lightProjection, lightView, lightModel;
	glm::mat4 lightSpaceMatrix = glm::mat4(1.0);
	Camera* camera = GameController::MainCamera;
	Light* light = GameController::Lights[0];
	float near_plane = 0.25f, far_plane = camera->getLocalPosition().y * 2;

	//Save camera transform
	glm::mat4 transform = camera->getTransform();

	//Translate camera to lights position
	camera->setLocalPosition(light->getLocalPosition());
	camera->setTransform(glm::inverse(glm::lookAt(camera->getLocalPosition(), glm::vec3(), glm::vec3(0, 1, 0))));
	lightSpaceMatrix = camera->getProjection() * glm::inverse(camera->getWorldTransform());
	GameController::lightSpaceMatrix = &lightSpaceMatrix;

	// render scene from light's point of view
	_debugQuadShader->use();
	glUniform1f(_debugQuadShader->getUniformLocation("near_plane"), near_plane);
	glUniform1f(_debugQuadShader->getUniformLocation("far_plane"), far_plane);

	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for each (Enemy* enemy in GameController::Enemies)
	{
		enemy->_children.clear();
	}
	_renderer->render(_world);

	//Reset camera back to original position
	camera->setTransform(transform);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// reset viewport
	glViewport(0, 0, GameController::Window->getSize().x, GameController::Window->getSize().y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render Depth map to quad for visual debugging
	// ---------------------------------------------
	//dynamic_cast<DebugTextureMaterial*>(GameController::plane->getMaterial())->_nearPlane = near_plane;
	//dynamic_cast<DebugTextureMaterial*>(GameController::plane->getMaterial())->_farPlane = far_plane;
	//dynamic_cast<DebugTextureMaterial*>(GameController::plane->getMaterial())->_depthMap = depthMap;
	GameController::shadowMap = depthMap;

	//Render world
	for each (Enemy* enemy in GameController::Enemies)
	{
		enemy->add(enemy->_healthBarBackground);
		enemy->add(enemy->_healthBar);
	}
	_renderer->render(_world);
}

void AbstractGame::_processEvents()
{
	sf::Event event;
	bool exit = false;

	//we must empty the event queue
	while (_window->pollEvent(event))
	{
		//give all system event listeners a chance to handle events
		//optionally to be implemented by you for example you could implement a
		//SystemEventDispatcher / SystemEventListener pair which allows Listeners to
		//register with the dispatcher and then do something like:
		//SystemEventDispatcher::dispatchEvent(event);

		switch (event.type)
		{
		case sf::Event::Closed:
			exit = true;
			break;
		case sf::Event::KeyPressed:
			/*if (event.key.code == sf::Keyboard::Escape)
			{
				exit = true;
			}*/
			break;
		case sf::Event::Resized:
			//would be better to move this to the renderer
			//this version implements nonconstrained match viewport scaling
			glViewport(0, 0, event.size.width, event.size.height);
			break;

		default:
			break;
		}

		if (gridManager != nullptr)
			gridManager->InputDetection(event);
		if (GameController::MenuManager != nullptr)
			GameController::MenuManager->Inputs(event);
		if (GameController::CameraBehaviour)
			GameController::CameraBehaviour->Scroll(event);
	}

	if (exit)
	{
		_window->close();
	}
}



