#pragma once
#include <glm/glm.hpp>
#include <Engine/SpriteBatch.h>

class Bullet2D
{
public:
	Bullet2D(glm::vec2 position, glm::vec2 direction, float speed, glm::vec2 size, int lifeTime);
	~Bullet2D();

	// returns true if bullet object should be destroyed
	bool update();
	void draw(Engine::SpriteBatch& spriteBatch);

private:
	int _lifeTime;
	float _speed;
	glm::vec2  _direction;
	glm::vec2 _position;
	glm::vec2 _size;
};

