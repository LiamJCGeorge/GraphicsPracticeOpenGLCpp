#pragma once

#include <vector>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <Engine/Engine.h>
#include <Engine/InputManager.h>
#include <Engine/Sprite.h>
#include <Engine/PrimitiveData.h>
#include <Engine/GLSLProgram.h>
#include <Engine/GLTexture.h>
#include <Engine/Camera.h>
#include <Engine/Camera2D.h>
#include <Engine/Window.h>
#include <Engine/SpriteBatch.h>
#include <Engine/Timing.h>

#include "Bullet2D.h"


enum class GameState {PLAY, EXIT};


class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();

	Engine::Window _window;
	int _screenWidth;
	int _screenHeight;

	GameState _gameState;

	float _maxFPS;
	float _fps;

	Engine::GLSLProgram _colorProgram;
	Engine::Camera2D _cam2D;
	Engine::InputManager _inputManager;
	Engine::SpriteBatch _spriteBatch;
	Engine::FpsLimiter _fpsLimiter;

	std::vector<Bullet2D> _bullets;

	//liam stuff
	glm::mat4 _model;
	glm::mat4 _proj;
	Engine::Camera _cam;

	Engine::GLSLProgram _solidProgram;
	Engine::PrimitiveData _solids;

	void initMisc();
	glm::vec3 cubePositions[10];

};

