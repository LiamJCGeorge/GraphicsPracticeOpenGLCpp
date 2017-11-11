#include "Camera.h"
#include "Errors.h"

#include <GL\glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace Engine {
	Camera::Camera() :
		_cameraPos(glm::vec3(0, 0, 3)),
		_cameraFront(glm::vec3(0, 0, -1)),
		_cameraUp(glm::vec3(0, 1, 0)),
		_frontPitch(0),
		_frontYaw(270),
		_view(glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp)),
		_viewNeedsUpdate(true),
		isCursorCaptured(true),
		firstCaptureFlag(true),
		_speedFactor(0.00250f),
		_mouseSensitivity(0.0148)
	{
	}


	Camera::~Camera()
	{
	}

	void Camera::setSpeedFactor(float speedFactor) { _speedFactor = speedFactor; }

	void Camera::moveForward() {
		_cameraPos += _cameraFront * _speed;
		_viewNeedsUpdate = true;
	}

	void Camera::strafeRight() {
		_cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * _speed;
		_viewNeedsUpdate = true;
	}

	void Camera::strafeLeft() {
		_cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * _speed;
		_viewNeedsUpdate = true;
	}

	void Camera::moveBackward() {
		_cameraPos -= _cameraFront * _speed;
		_viewNeedsUpdate = true;
	}

	void Camera::moveUp() {
		_cameraPos += _cameraUp * _speed;
		_viewNeedsUpdate = true;
	}

	void Camera::moveDown() {
		_cameraPos -= _cameraUp * _speed;
		_viewNeedsUpdate = true;
	}



	float Camera::pitch(float y) {
		_frontPitch += y * _mouseSensitivity;
		if (_frontPitch > 89.0f)
			_frontPitch = 89.0f;
		if (_frontPitch < -89.0f)
			_frontPitch = -89.0f;
		_viewNeedsUpdate = true;
		return _frontPitch;
	}

	float Camera::yaw(float x) {
		_frontYaw += x * _mouseSensitivity;
		if (_frontYaw > 360.0f) {
			_frontYaw -= 360.0f;
		}else if (_frontYaw < -360.0f) {
			_frontYaw += 360.0f;
		}
		_viewNeedsUpdate = true;
		return _frontYaw;
	}

	//

	void Camera::reset(float deltaTime) {
		_speed = _speedFactor * deltaTime;
		_viewNeedsUpdate = false;
	}

	void Camera::updateCamera(float deltaTime) {
		if (_viewNeedsUpdate) {
			glm::vec3 front;
			front.x = cos(glm::radians(_frontPitch)) * cos(glm::radians(_frontYaw));
			front.y = sin(glm::radians(_frontPitch));
			front.z = cos(glm::radians(_frontPitch)) * sin(glm::radians(_frontYaw));
			_cameraFront = glm::normalize(front);
			_view = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
		}
	}

	void Camera::updateProgram(const GLSLProgram& program) {
		if (_viewNeedsUpdate) {
			glUniformMatrix4fv(program.viewLocation, 1, GL_FALSE, &_view[0][0]);
		}
	}

}

