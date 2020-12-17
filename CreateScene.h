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

using namespace std;

class CreateScene
{
private:
	SDL_Window* window;
	SDL_GLContext glcontext;

	const int width = 640;
	const int height = 480;
	GLuint shaderProgram;
	GLuint vertexShader;
	GLuint fragmentShader;
	string vertexPath = "vertex.v";
	string fragmentPath = "fragment.f";
	GLuint vbo, vao;

public:
	CreateScene();
	~CreateScene();

	bool Init();
	bool InitVAO();
	bool InitVBO();

	GLuint LoadShader(string, string);
	string ReadFile(string path);

	void CreateShaderProgram();
	void OutShader();

	void Start();
	void MainLoop();

	void Close();

};

#endif
