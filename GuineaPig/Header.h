#pragma once
/*
// some intialization crap
//============================================================================
SDL_Init(SDL_INIT_EVERYTHING);
SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

SDL_Window* _sdlwindow = SDL_CreateWindow("Guinea Pig", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
SDL_GLContext glContext = SDL_GL_CreateContext(_sdlwindow);
GLenum error = glewInit();
printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));
SDL_GL_SetSwapInterval(1);

glClearDepth(1.0);
glClearColor(0, 0, 0, 1.0f);
//=============================================================================
SDL_GL_SwapWindow(_sdlwindow);
*/