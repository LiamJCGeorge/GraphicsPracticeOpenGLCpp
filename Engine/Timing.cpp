#include "Timing.h"
#include <SDL/SDL.h>

namespace Engine {

	FpsLimiter::FpsLimiter() : _deltaTime(0.0f)
	{}

	void FpsLimiter::init(float maxFPS) {
		setMaxFPS(maxFPS);
	}
	
	void FpsLimiter::begin() {
		_startTicks = SDL_GetTicks();
	}

	float FpsLimiter::end() {
		float frameTime = SDL_GetTicks() - _startTicks;
		calculateFPS();

		// force a delay to maintain _maxFPS
		if ((1000.0f / _maxFPS) > frameTime) {
			SDL_Delay((1000.0f / _maxFPS) - frameTime); // SDL_Delay may not always work (Windows specific)
		}

		_deltaTime = SDL_GetTicks() - _startTicks;
		return _fps;
	}

	void FpsLimiter::setMaxFPS(float maxFPS) {
		_maxFPS = maxFPS;
	}

	float FpsLimiter::getDeltaTime() {
		return _deltaTime;
	}

	void FpsLimiter::calculateFPS() {
			static const int NUM_SAMPLES = 10;
			static float frameTimes[NUM_SAMPLES];
			static int currentFrame = 0;

			frameTimes[currentFrame % NUM_SAMPLES] = _deltaTime;


			currentFrame++;
			int count;

			if (currentFrame < NUM_SAMPLES) {
				count = currentFrame;
			}
			else
			{
				count = NUM_SAMPLES;
			}

			float frameTimeAverage = 0;
			for (int i = 0; i < count; i++) {
				frameTimeAverage += frameTimes[i];
			}
			frameTimeAverage /= count;

			if (frameTimeAverage > 0) {
				_fps = 1000.0f / frameTimeAverage;
			}
			else
			{
				_fps = 60.0f;
			}
	}
}