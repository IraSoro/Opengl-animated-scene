#pragma comment(lib, "glew32.lib")
#include "CreateScene.h"

CreateScene::CreateScene() : 
		window(nullptr),
		vao(0),
		vbo(0),
		ebo(0),
		texture1(0),
		texture2(0),
		glcontext(0){

}

CreateScene::~CreateScene() {

}

void CreateScene::Start() {
	if (Init() && InitGLEW()) {

		MainLoop();

		Close();
	}
	return;
}

GLfloat vertices[] = {
	// Positions          // Colors           // Texture Coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
};
GLuint indices[] = {  // Note that we start from 0!
	0, 1, 3, // First Triangle
	1, 2, 3  // Second Triangle
};

void CreateScene::MainLoop() {
	Shader ourShader(vertexPath, fragmentPath);

	WorkAttr();
	
	WorkTexture(texture1, "awesomeface.png");
	WorkTexture(texture2, "container.jpg");

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
					cout << "left" << endl;
					break;
				case SDLK_RIGHT:
					break;
				}
				break;
			}
		}
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);
		
		ourShader.Use();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// обновляем экран
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

	return true;
}

bool CreateScene::InitGLEW() {
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
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

bool CreateScene::InitEBO() {
	glGenBuffers(1, &ebo);
	if (vbo == 1) printf("EBO = %u\n", vbo);
	else {
		cout << "glGenBuffers Error: EBO = ";
		printf("%u\n", vbo);
		return false;
	}

	return true;
}

void CreateScene::WorkAttr() {
	if (!InitVAO() || !InitVBO() || !InitEBO())
		return;

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
	return;
}

void CreateScene::WorkTexture(GLuint &texture, const GLchar* name) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); 
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(name, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return;
}

void CreateScene::Close() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	printf("%s\n", glGetString(GL_VERSION));
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
	cout << "Clear finish" << endl;
}