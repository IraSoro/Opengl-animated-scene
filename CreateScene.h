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

#include "Shader.h"

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

	void Close();

};

#endif
