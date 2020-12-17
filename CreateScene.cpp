#pragma comment(lib, "glew32.lib")
#include "CreateScene.h"

const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

CreateScene::CreateScene() : 
		window(nullptr),
		vao(0),
		vbo(0),
		shaderProgram(0),
		glcontext(0), 
		fragmentShader(0),
		vertexShader(0) {

}

CreateScene::~CreateScene() {

}

void CreateScene::Start() {
	if (Init() && InitGLEW() && InitVAO() && InitVBO()) {
		MainLoop();
	}
	return;
}

GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f, // Left  
	 0.5f, -0.5f, 0.0f, // Right 
	 0.0f,  0.5f, 0.0f  // Top   
};

void CreateScene::MainLoop() {
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);


	bool running = true;

	while (running) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					running = false;
					break;
				case SDLK_LEFT:
					break;
				case SDLK_RIGHT:
					break;
				}
				break;
			}
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// обновл¤ем экран
		glFlush();
		SDL_GL_SwapWindow(window);
	}

}

bool CreateScene::Init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Unable to init SDL, error: " << SDL_GetError() << endl;
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);


	window = SDL_CreateWindow("Ira_Soro", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	glcontext = SDL_GL_CreateContext(window);

	if (window == NULL) {
		return false;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f); // настраиваем трехмерную перспективу
	glMatrixMode(GL_MODELVIEW); // переходим в трехмерный режим

	return true;
}

bool CreateScene::InitGLEW() {
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		return false;
	}
	return true;
}

bool CreateScene::InitVBO() {
	glGenBuffers(1, &vbo);
	if (vbo == 1) printf("VBO = %u\n", vbo);
	else {
		cout << "glGenBuffers Error: VBO = ";
		printf("%u\n", vbo);
		return false;
	}

	return true;
}

bool CreateScene::InitVAO() {
	glGenVertexArrays(1, &vao);
	if (vao == 1) printf("VAO = %u\n", vao);
	else {
		cout << "glGenBuffers Error: VAO = ";
		printf("%u\n", vao);
		return false;
	}

	return true;
}

GLuint CreateScene::LoadShader(string vertex_path, string fragment_path) {
	string vertexStr = ReadFile(vertex_path);
	string fragmentStr = ReadFile(fragment_path);
	const GLchar* vertShaderSrc = vertexStr.c_str();
	const GLchar* fragShaderSrc = fragmentStr.c_str();

	//компил¤ци¤ вершинного шейдера
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertShaderSrc, NULL);
	glCompileShader(vertexShader);
	//проверка компил¤ции шейдера
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE) cout << "vertexShader success compile" << endl;
	else {
		cout << "vertexShader compile error " << status << endl;
		int logLen = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLen);
		char* log = new char[logLen];
		glGetShaderInfoLog(vertexShader, logLen, NULL, log);
		cout << log << endl;
		delete [] log;
		return -1;
	}
	//компил¤ци¤ фрагментного шейдера
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragShaderSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE) cout << "fragmentShader success compile" << endl;
	else {
		cout << "fragmentShader compile error " << status << endl;
		int logLen = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLen);
		char* log = new char[logLen];
		glGetShaderInfoLog(fragmentShader, logLen, NULL, log);
		cout << log << endl;
		delete [] log;
		return -1;
	}
	return 0;
}

string CreateScene::ReadFile(string path) {
	string content;
	ifstream file(path);
	if (!file.is_open()) return "";
	string line = "";
	while (getline(file, line)) {
		content += line + '\n';
	}
	file.close();
	return content;
}

void CreateScene::CreateShaderProgram() {
	//создание программы-шейдера
	shaderProgram = glCreateProgram();
	//прикрепление шейдеров к программе
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	//glUseProgram(shaderProgram);
}

void CreateScene::OutShader() {
	//открепление шейдеров
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glDeleteProgram(shaderProgram);
}

void CreateScene::Close() {
	printf("%s\n", glGetString(GL_VERSION));
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
	cout << "Clear finish" << endl;
}