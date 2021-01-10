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
	const GLchar* vertexSkyBox = "vertexSkyBox.v";
	const GLchar* fragmentSkyBox = "fragmentSkyBox.f";
	GLuint vao, vbo;
	GLuint vaoLight;
	GLuint skyboxVAO, skyboxVBO;

	GLuint texture1;
	GLuint texture2;

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	int keys[1024];

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	float Yaw = -90.0;						
	float Pitch = 0.0;
	const float rotateSpeed = 0.8f;
	glm::vec3 cameraRight;

	glm::vec3 lightPosSun = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 lightPosMoon = glm::vec3(0.0f, -1.0f, 0.0f);

	glm::vec3 oneLampColor = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 twoLampColor = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 threeLampColor = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 fourLampColor = glm::vec3(0.0f, 0.0f, 0.0f);

	const GLchar* pos = "4.jpg";
	vector <string> faces{ pos, pos, pos, pos, pos, pos };

	
public:
	CreateScene();
	~CreateScene();

	bool InitSDL();
	bool InitGLEW();
	bool InitVAO();
	bool InitVBO();

	void Start();
	void MainLoop();
	void WorkAttr();
	
	void InitSkyBox();

	void Close();

	unsigned int loadCubemap(vector<std::string> faces);
};

#endif
