#pragma once
#include "GLSLProgram.h"
#include "Vertex.h"

#include <glm/glm.hpp>

namespace Engine {

	class GLSLProgram;

	class Camera
	{
	public:
		Camera();

		~Camera();

		void moveForward();
		void strafeRight();
		void strafeLeft();
		void moveBackward();
		void moveUp();
		void moveDown();

		float yaw(float x);
		float pitch(float y);

		void setSpeedFactor(float speedFactor);
		void updateCamera(float deltaTime);
		void updateProgram(const GLSLProgram& program);
		void reset(float deltaTime);

		
		bool isCursorCaptured;
		bool firstCaptureFlag;

	private:
		glm::vec3 _cameraPos;
		glm::vec3 _cameraFront;
		glm::vec3 _cameraUp;

		glm::mat4 _view;
		bool _viewNeedsUpdate;

		float _speed;
		float _speedFactor;
		float _mouseSensitivity;

		float _frontYaw;
		float _frontPitch;
	};
}

