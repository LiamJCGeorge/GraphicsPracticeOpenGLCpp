#include "MainGame.h"

#include <Engine/GLTexture.h>
#include <Engine/ResourceManager.h>
#include <Engine/Errors.h>
#include <iostream>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>








MainGame::MainGame() :
	_screenWidth(1024), //1024
	_screenHeight(768), //768
	_gameState(GameState::PLAY),
	_maxFPS(120.0f)
{ _cam2D.init(_screenWidth, _screenHeight); }


MainGame::~MainGame()
{
}

void MainGame::initSystems()
{
	Engine::init();
	_window.create("Game", _screenWidth, _screenHeight, Engine::RESIZABLE);
	initShaders();
	_spriteBatch.init();
	_fpsLimiter.init(_maxFPS);
}

void MainGame::initShaders() {
	glEnable(GL_DEPTH_TEST);

	// Ben shader
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
	_colorProgram.use();
	_colorProgram.setInt("box", 0); //texture
	_colorProgram.unuse();

	//Liam shader
	_solidProgram.compileShaders("Shaders/solidShading.vert", "Shaders/solidShading.frag");
	_solidProgram.addAttribute("vertexPosition");
	_solidProgram.addAttribute("vertexColor");
	_solidProgram.addAttribute("vertexUV");
	_solidProgram.linkShaders();
	_solidProgram.use();
	_solidProgram.setInt("box", 0); //texture
	_proj = glm::perspective(glm::radians(45.0f), (float)(_screenWidth / _screenHeight), 0.1f, 1000.0f);
	glUniformMatrix4fv(_solidProgram.projLocation, 1, GL_FALSE, &_proj[0][0]);
	_model = glm::mat4();
	glUniformMatrix4fv(_solidProgram.modelLocation, 1, GL_FALSE, &_model[0][0]);
	_solidProgram.unuse();
}

void MainGame::initMisc() {
	cubePositions[0] = glm::vec3(0.0f, 0.0f, 0.0f);
	cubePositions[1] = glm::vec3(2.0f, 5.0f, -15.0f);
	cubePositions[2] = glm::vec3(-1.5f, -2.2f, -2.5f);
	cubePositions[3] = glm::vec3(-3.8f, -2.0f, -12.3f);
	cubePositions[4] = glm::vec3(2.4f, -0.4f, -3.5f);
	cubePositions[5] = glm::vec3(-1.7f, 3.0f, -7.5f);
	cubePositions[6] = glm::vec3(1.3f, -2.0f, -2.5f);
	cubePositions[7] = glm::vec3(1.5f, 2.0f, -2.5f);
	cubePositions[8] = glm::vec3(1.5f, 0.2f, -1.5f);
	cubePositions[9] = glm::vec3(-1.3f, 1.0f, -1.5f);
}

void MainGame::run()
{
	initSystems();
	_solids.init();
	initMisc();
	gameLoop();
}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
	
		_fpsLimiter.begin();

		_cam.updateCamera(0.016f);
		_cam2D.update();
		
		for (int i = 0; i < _bullets.size();) {
			if (_bullets[i].update()) {
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else {
				i++;
			}
		}

		drawGame();
		
		_cam.reset(_fpsLimiter.getDeltaTime());
		processInput();

		_fps = _fpsLimiter.end();

		// limit fps printing
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter >= 100) {
			//std::cout << _fps << std::endl;
			frameCounter = 0;
		}

	}
}

void MainGame::drawGame() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Ben
	_colorProgram.use();

	GLint camLocation = glGetUniformLocation(_colorProgram.programID, "cam");
	glm::mat4 cameraMatrix = _cam2D.getCameraMatrix();
	glUniformMatrix4fv(camLocation,1, GL_FALSE, &(cameraMatrix[0][0]));

	// draw all sprites in scene
	_spriteBatch.begin();
	glm::vec4 pos(0.0f,0.0f,50.0f,50.0f);
	glm::vec4 uv(0.0f,0.0f,1.0f,1.0f);
	static Engine::GLTexture texture = Engine::ResourceManager::getTexture("resources/textures/box.png");
	Engine::Color color; color.r = 255; color.g = 255; color.b = 255; color.a = 255;

	_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);

	for (int i = 0; i < _bullets.size(); i++) {
		_bullets[i].draw(_spriteBatch);
	}

	_spriteBatch.end();
	_spriteBatch.renderBatch();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();

	
	//Liam
	_solidProgram.use();
		_cam.updateProgram(_solidProgram);
		for (int i = 0; i < 10; i++) {
			_model = glm::translate(glm::mat4(), cubePositions[i]);
			glUniformMatrix4fv(_solidProgram.modelLocation, 1, GL_FALSE, &_model[0][0]);
				_solids.cube->draw();
		}
	_solidProgram.unuse();
	
	_window.swapBuffer();

}

void MainGame::processInput() {
	SDL_Event evnt;

	const float TRANSLATE_SPEED = 20.0f;
	const float SCALE_SPEED = 0.05f;

	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			if (evnt.key.keysym.sym == SDLK_TAB) {
				if (_cam.isCursorCaptured) {
					_cam.isCursorCaptured = false;
					SDL_SetRelativeMouseMode(SDL_FALSE);
					SDL_WarpMouseInWindow(_window.getWindow(), int(_screenWidth / 2), int(_screenHeight / 2)); // center mouse
					SDL_FlushEvent(SDL_MOUSEMOTION);
				}
				else {
					_cam.isCursorCaptured = true;
					_cam.firstCaptureFlag = true;
					SDL_SetRelativeMouseMode(SDL_TRUE);
					//SDL_WarpMouseInWindow(_window.getWindow(), int(_screenWidth / 2), int(_screenHeight / 2)); // center mouse
					SDL_FlushEvent(SDL_MOUSEMOTION);
				}
			}
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			if (_cam.isCursorCaptured) {
				int xrel, yrel;
				SDL_GetRelativeMouseState(&xrel, &yrel);
				if (!_cam.firstCaptureFlag) {
					_cam.pitch(-yrel);
					_cam.yaw(xrel);
				}
				else { 
					_cam.firstCaptureFlag = false;
				}
			}
			break				;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		case SDL_MOUSEWHEEL:
			if (evnt.wheel.y == 1) // scroll up
			{
				_cam2D.setScale(_cam2D.getScale() * (1.0f + SCALE_SPEED));
			}
			else if (evnt.wheel.y == -1) // scroll down
			{
				_cam2D.setScale(_cam2D.getScale() * (1.0f - SCALE_SPEED)); // scale can no longer be negative
			}
			break;
		case SDL_WINDOWEVENT_RESIZED:
			SDL_Window* win = SDL_GetWindowFromID(evnt.window.windowID);
			if (win == _window.getWindow())
			{
				_screenWidth = evnt.window.data1;
				_screenHeight = evnt.window.data2;
				glViewport(0, 0, _screenWidth, _screenHeight);

				_solidProgram.use();
				_proj = glm::perspective(glm::radians(45.0f), (float)(_screenWidth / _screenHeight), 0.1f, 1000.0f);
				glUniformMatrix4fv(_solidProgram.projLocation, 1, GL_FALSE, &_proj[0][0]);
				_solidProgram.unuse();
			}
			break;
		}
	}

	if (_inputManager.isKeyPressed(SDLK_w)) {
		_cam2D.setPosition(_cam2D.getPosition() + glm::vec2(0.0f, TRANSLATE_SPEED));
		_cam.moveForward();
	}
	if (_inputManager.isKeyPressed(SDLK_s)) {
		_cam2D.setPosition(_cam2D.getPosition() + glm::vec2(0.0f, -TRANSLATE_SPEED));
		_cam.moveBackward();
	}
	if (_inputManager.isKeyPressed(SDLK_a)) {
		_cam2D.setPosition(_cam2D.getPosition() + glm::vec2(-TRANSLATE_SPEED, 0.0f));
		_cam.strafeLeft();
	}
	if (_inputManager.isKeyPressed(SDLK_d)) {
		_cam2D.setPosition(_cam2D.getPosition() + glm::vec2(TRANSLATE_SPEED, 0.0f));
		_cam.strafeRight();
	}
	if (_inputManager.isKeyPressed(SDLK_LSHIFT)) {
		_cam.moveDown();
	}
	if (_inputManager.isKeyPressed(SDLK_SPACE)) {
		_cam.moveUp();
	}
	if (_inputManager.isKeyPressed(SDLK_ESCAPE)) {
		_gameState = GameState::EXIT;
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _cam2D.convertScreenToWorld(mouseCoords);

		glm::vec2 playerPos(0.0f);
		glm::vec2 direction = mouseCoords - playerPos;
		direction = glm::normalize(direction);
		glm::vec2 size(30.0f,30.0f);

		_bullets.emplace_back(playerPos, direction, 1.0f, size, 1000);
	}
}

