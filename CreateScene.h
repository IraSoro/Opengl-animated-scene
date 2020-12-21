#ifndef __CREATE_SCENE_H__
#define __CREATE_SCENE_H__

#include <iostream> 
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>

#include <SDL.h>
#include <GL/glew.h>
#include <GL/GLU.h>

#include <SOIL2.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

using namespace std;

class CreateScene {
private:
	SDL_Window* window;
	SDL_GLContext glcontext;

	const int width = 640;
	const int height = 480;
	const GLchar* vertexPath = "vertex.v";
	const GLchar* fragmentPath = "fragment.f";
	GLuint vao, vbo, ebo;

	
	
	GLuint texture1;
	GLuint texture2;

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	GLfloat yaw = -90.0f;	
	GLfloat pitch = 0.0f;
	GLfloat lastX = width/ 2.0;
	GLfloat lastY = height/ 2.0;
	GLfloat fov = 45.0f;
	

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

public:
	CreateScene();
	~CreateScene();

	bool Init();
	bool InitGLEW();
	bool InitVAO();
	bool InitVBO();
	bool InitEBO();

	void Start();
	void MainLoop();
	void WorkAttr();
	void WorkTexture(GLuint &texture, const GLchar* name);
	void DrawObject();

	void CameraMove(float TimeForCamera);

	void Close();
};

#endif
