#pragma once

#include <Engine\Window.h>
#include <Engine\GLSLProgram.h>
#include <Engine\Camera2D.h>
#include <Engine\InputManager.h>


class MainGame
{
public:
    MainGame();
    ~MainGame();

    /// Runs the game
    void run();

private:
    /// Initializes the core systems
    void initSystems();
    /// Initializes the shaders
    void initShaders();

    /// Main game loop for the program
    void gameLoop();
    /// Handles input processing
    void processInput();
    /// Renders the game
    void drawGame();

private:
    /// Member Variables
    Engine::Window _window; ///< The game window
	Engine::GLSLProgram _textureProgram; ///< The shader program
	Engine::InputManager _inputManager; ///< Handles input
    Engine::Camera2D _camera; ///< Main Camera
};

