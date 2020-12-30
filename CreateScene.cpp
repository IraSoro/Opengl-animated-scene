#pragma comment(lib, "glew32.lib")
#include "CreateScene.h"

using namespace std;

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
/*
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
*/

float vertices1[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
};


void CreateScene::MainLoop() {
	Shader ourShader(vertexPath, fragmentPath);
	Shader LampShader(vertexLamp, fragmentLamp);

	WorkAttr();
	InitLight();
	
	//ourShader.Use();

	//GLint material_diffuse = glGetUniformLocation(ourShader.Program, "material.diffuse");
	//GLint material_specular = glGetUniformLocation(ourShader.Program, "material.specular");

	//glUniform1i(material_diffuse, 0);
	//glUniform1i(material_specular, 1);
	
	//unsigned int diffuseMap = loadTexture("container2.png");
	//unsigned int specularMap = loadTexture("container2_specular.png");
	
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	int keys[1024] = { 0 };

	Model ModelSun("sun/sun.obj");
	Model ModelHouse("house/house.obj");

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	bool running = true;
	GLfloat cameraSpeed;

	float temp = 0.0f;
	float fast = 0.25f;
	float radius = 2.5f;

	while (running) {
		SDL_Event event;
		float currentFrame = SDL_GetTicks();
		deltaTime = (currentFrame - lastFrame) / 100;
		lastFrame = currentFrame;
		GLfloat cameraSpeed = rotateSpeed * deltaTime;

		while (SDL_PollEvent(&event)) {			
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				keys[event.key.keysym.sym] = 1;
				if (keys[SDLK_ESCAPE] || (keys[SDLK_LCTRL] && keys[SDLK_q])) {
					//cout << "Q" << endl;
					running = false;
				} else if (keys[SDLK_w]) {
					//cout << "W" << endl;
					cameraPos += cameraSpeed * cameraFront;
				} else if (keys[SDLK_s]) {
					//cout << "S" << endl;
					cameraPos -= cameraSpeed * cameraFront;
				} else if (keys[SDLK_a]) {
					//cout << "A" << endl;
					cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
				} else if (keys[SDLK_d]) {
					//cout << "D" << endl;
					cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
				}else if (keys[SDLK_LEFT]) {
					//cout << "LEFT" << endl;

					Yaw -= rotateSpeed;

					glm::vec3 newFront;
					newFront.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
					newFront.y = sin(glm::radians(Pitch));
					newFront.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
					cameraFront = glm::normalize(newFront);

					cameraRight = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 0.1f, 0.0f)));
					cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
				} else if (keys[SDLK_RIGHT]) {
					//cout << "RIGHT" << endl;
					
					Yaw += rotateSpeed;

					glm::vec3 newFront;
					newFront.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
					newFront.y = sin(glm::radians(Pitch));
					newFront.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
					cameraFront = glm::normalize(newFront);

					cameraRight = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 0.1f, 0.0f)));
					cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
				} else if (keys[SDLK_UP]) {
					//cout << "UP" << endl;

					Pitch += rotateSpeed;

					glm::vec3 newFront;
					newFront.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
					newFront.y = sin(glm::radians(Pitch));
					newFront.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
					cameraFront = glm::normalize(newFront);

					cameraRight = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 0.1f, 0.0f)));
					cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
				} else if (keys[SDLK_DOWN]) {
					//cout << "DOWN" << endl;
					
					Pitch -= rotateSpeed;

					glm::vec3 newFront;
					newFront.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
					newFront.y = sin(glm::radians(Pitch));
					newFront.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
					cameraFront = glm::normalize(newFront);

					cameraRight = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 0.1f, 0.0f)));
					cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
				}
				break;
			case SDL_KEYUP:
				keys[event.key.keysym.sym] = 0;
				break;
			}
		}

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.Use();

		GLint light_position = glGetUniformLocation(ourShader.Program, "light.position");
		GLint viewPos = glGetUniformLocation(ourShader.Program, "viewPos");

		glUniform3fv(light_position, 1, glm::value_ptr(lightPos));
		glUniform3fv(viewPos, 1, glm::value_ptr(cameraPos));

		glm::vec3 lightColor;
		/*
		lightColor.x = 1.0f;
		lightColor.y = 1.0f;
		lightColor.z = 1.0f;
		*/
		
		temp = sin(currentFrame / 1000 * fast);
		if (temp > 0.0f) {
			lightColor.x = 1.0f;
			lightColor.y = sin(currentFrame / 1000 * fast);
			lightColor.z = sin(currentFrame / 1000 * fast);
		}
		else {
			lightColor.x = abs(cos(currentFrame / 1000 * fast));
			lightColor.y = 0.0f;
			lightColor.z = 0.0f;
		}
		
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.8f); 
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

		GLint light_ambient = glGetUniformLocation(ourShader.Program, "light.ambient");
		glUniform3fv(light_ambient, 1, glm::value_ptr(ambientColor));

		GLint light_diffuse = glGetUniformLocation(ourShader.Program, "light.diffuse");
		glUniform3fv(light_diffuse, 1, glm::value_ptr(diffuseColor));

		GLint light_specular = glGetUniformLocation(ourShader.Program, "light.specular");
		glUniform3f(light_specular, 1.0f, 1.0f, 1.0f);

		GLint light_constant = glGetUniformLocation(ourShader.Program, "light.constant");
		glUniform1f(light_constant, 1.0f);

		GLint light_light = glGetUniformLocation(ourShader.Program, "light.light");
		glUniform1f(light_light, 0.0014f);

		GLint light_quadratic = glGetUniformLocation(ourShader.Program, "light.quadratic");
		glUniform1f(light_quadratic, 0.000007f);

		GLint material_shininess = glGetUniformLocation(ourShader.Program, "material.shininess");
		glUniform1f(material_shininess, 64.0f);
		/*
		glm::mat4 view;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glm::mat4 projection;
		projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		glBindVertexArray(vao);
		for (GLuint i = 0; i < 10; i++){
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 20.0f * i;
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);


		glBindVertexArray(vaoLeght);
		glm::mat4 model;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		*/
		
		//ourShader.Use();

		glm::mat4 view;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glm::mat4 projection;
		projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));		
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		
		ModelHouse.Draw(ourShader);
					   
		
		LampShader.Use();

		GLint vertexColorLocation = glGetUniformLocation(LampShader.Program, "ourColor");
		glUniform4f(vertexColorLocation, lightColor.x, lightColor.y, lightColor.z, 1.0f);
		
		modelLoc = glGetUniformLocation(LampShader.Program, "model");
		viewLoc = glGetUniformLocation(LampShader.Program, "view");
		projLoc = glGetUniformLocation(LampShader.Program, "projection");
		
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		lightPos.x = cos(currentFrame / 1000 * fast) * radius;
		lightPos.y = sin(currentFrame / 1000 * fast) * radius;
		lightPos.z = 0.0f;
		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		
		glBindVertexArray(vaoLeght);
		ModelSun.Draw(LampShader);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		


		//SDL_Delay(200);
		
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

	glViewport(0, 0, width, height);

	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);
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
	if (!InitVAO() || !InitVBO() )
		return;

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
	return;
}

void CreateScene::InitLight() {
	
	glGenVertexArrays(1, &vaoLeght);
	glBindVertexArray(vaoLeght);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
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

unsigned int CreateScene::loadTexture(char const* path){
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		cout << "Texture failed to load at path: " << path << endl;
		stbi_image_free(data);
	}

	return textureID;
}

void CreateScene::RotateCamera() {
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
	newFront.y = sin(glm::radians(Pitch));
	newFront.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
	cameraFront = glm::normalize(newFront);

	cameraRight = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 0.1f, 0.0f)));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
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


