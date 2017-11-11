#pragma once
namespace Engine {

class FpsLimiter {
public:
	FpsLimiter();
	void init(float maxFPS);

	

	void begin();
	float end(); // end returns the current fps

	float getDeltaTime();
	
private:
	void setMaxFPS(float maxFPS);
	void calculateFPS();
	
	unsigned int _startTicks;
	float _maxFPS;
	float _fps;
	float _deltaTime;

};


}