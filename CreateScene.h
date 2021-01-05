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
#include <stb_image.h>

#include <SOIL2.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Model.h"

using namespace std;

class CreateScene {
private:
	SDL_Window* window;
	SDL_GLContext glcontext;

	const int width = 640;
	const int height = 480;
	const GLchar* vertexPath = "vertex.v";
	const GLchar* fragmentPath = "fragment.f";
	const GLchar* vertexLamp = "lampVertex.v";
	const GLchar* fragmentLamp = "lampFragment.f";
	const GLchar* vertexModel = "loadingModelVert.v";
	const GLchar* fragmentModel = "loadingModelFrag.f";
	GLuint vao, vaoLeght, vbo, ebo;
	
	GLuint texture1;
	GLuint texture2;
	
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraX = glm::vec3(1.0f, 0.0f, 0.0f);
	int keys[1024];

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	float Yaw = -90.0;						
	float Pitch = 0.0;
	const float rotateSpeed = 0.8f;
	glm::vec3 cameraRight;
	glm::vec3 lightPosSun = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 lightPosMoon = glm::vec3(0.0f, -1.0f, 0.0f);
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
	unsigned int loadTexture(char const* path);

	void RotateCamera();
	void InitLight();

	void Close();
};

#endif
