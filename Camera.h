#pragma once
#ifndef CAMERA
#define CAMERA

#include <iostream> 

#include <gl\glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

enum Keys { W, A, S, D, UP, DOWN, LEFT, RIGHT };	//объединение для обращения к индексам клавиш

class Camera {
private:
	glm::vec3 camPosition;						//позиция камеры
	glm::vec3 camFront;							//вектор вперед камеры
	glm::vec3 camUp;							//вектор вверх
	glm::vec3 camRight;							//вектор вправо
	float Yaw = -90.0;							//поворот вокруг y
	float Pitch = 0.0;							//поворот вокруг x
	bool keyMoveEnable;							//разрешение движения камере
	bool keyRotateEnable;						//разрешение вращения камере
	const float rotateSpeed = 0.02f;
	const float moveSpeed = 0.8f;
public:
	void SetPosition(glm::vec3 position) {
		this->camPosition = position;
	}
	glm::vec3 getCameraPosition() {
		return this->camPosition;
	}
	void SetTarget(glm::vec3 target);
	glm::mat4 GetCameraMatrix() {
		return glm::lookAt(camPosition, camPosition + camFront, camUp);
	}
	void cameraKeyMove(bool mode) {
		this->keyMoveEnable = mode;
		cout << "camera keyMove = " << mode << endl;
	}
	void cameraKeyRotate(bool mode) {
		this->keyRotateEnable = mode;
		cout << "camera rotateMove = " << mode << endl;
	}
	void KeyEvent(Keys key, float deltaTime);
	Camera();
	Camera(glm::vec3 position, glm::vec3 up) :camPosition(position), camUp(up), camFront(glm::vec3(0.0f, 0.0f, -1.0f)), keyMoveEnable(false), keyRotateEnable(false) {}
	void Update();
	void SetupFront();
};
#endif CAMERA