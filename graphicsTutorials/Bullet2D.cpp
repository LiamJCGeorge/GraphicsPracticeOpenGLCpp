#include "Bullet2D.h"
#include <Engine/ResourceManager.h>


Bullet2D::Bullet2D(glm::vec2 position, glm::vec2 direction, float speed, glm::vec2 size, int lifeTime):
_position(position),
_direction(direction),
_speed(speed),
_size(size),
_lifeTime(lifeTime)
{
}


Bullet2D::~Bullet2D()
{
}

bool Bullet2D::update() {
	_position += _direction * _speed;
	_lifeTime--;
	if (_lifeTime <= 0) {
		return true;
	}
	return false;
}

void Bullet2D::draw(Engine::SpriteBatch& spriteBatch) {
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Engine::GLTexture texture = Engine::ResourceManager::getTexture("resources/textures/purpBlend.png");
	Engine::Color color; color.r = 255; color.g = 255; color.b = 255; color.a = 255;

	spriteBatch.draw(glm::vec4(_position, _size), uv, texture.id, 0.0f, color);
}
