#pragma comment(lib, "glew32.lib")
#include "CreateScene.h"

using namespace std;

CreateScene::CreateScene() : 
		window(nullptr),
		vao(0),
		vbo(0),
		texture1(0),
		texture2(0),
		glcontext(0){

}

CreateScene::~CreateScene() {

}

void CreateScene::Start() {
	if (InitSDL() && InitGLEW()) {

		MainLoop();

		Close();
	}
	return;
}

float skyboxVertices[] = {       
	-3.0f,  3.0f, -3.0f,
	-3.0f, -3.0f, -3.0f,
	 3.0f, -3.0f, -3.0f,
	 3.0f, -3.0f, -3.0f,
	 3.0f,  3.0f, -3.0f,
	-3.0f,  3.0f, -3.0f,

	-3.0f, -3.0f,  3.0f,
	-3.0f, -3.0f, -3.0f,
	-3.0f,  3.0f, -3.0f,
	-3.0f,  3.0f, -3.0f,
	-3.0f,  3.0f,  3.0f,
	-3.0f, -3.0f,  3.0f,

	 3.0f, -3.0f, -3.0f,
	 3.0f, -3.0f,  3.0f,
	 3.0f,  3.0f,  3.0f,
	 3.0f,  3.0f,  3.0f,
	 3.0f,  3.0f, -3.0f,
	 3.0f, -3.0f, -3.0f,
	 
	-3.0f, -3.0f,  3.0f,
	-3.0f,  3.0f,  3.0f,
	 3.0f,  3.0f,  3.0f,
	 3.0f,  3.0f,  3.0f,
	 3.0f, -3.0f,  3.0f,
	-3.0f, -3.0f,  3.0f,

	-3.0f,  3.0f, -3.0f,
	 3.0f,  3.0f, -3.0f,
	 3.0f,  3.0f,  3.0f,
	 3.0f,  3.0f,  3.0f,
	-3.0f,  3.0f,  3.0f,
	-3.0f,  3.0f, -3.0f,

	-3.0f, -3.0f, -3.0f,
	-3.0f, -3.0f,  3.0f,
	 3.0f, -3.0f, -3.0f,
	 3.0f, -3.0f, -3.0f,
	-3.0f, -3.0f,  3.0f,
	 3.0f, -3.0f,  3.0f
};

glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.4f,  0.125f,  0.2f),
        glm::vec3( -0.6f, 0.15f, 0.2f),
        glm::vec3(-0.3f,  0.15f, 0.7f),
        glm::vec3( 0.15f,  0.125f, 0.7f)
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
	Shader SkyBoxShader(vertexSkyBox, fragmentSkyBox);

	WorkAttr();
	InitSkyBox();

	int keys[1024] = { 0 };

	Model ModelSun("sun/sun.obj");
	Model ModelMoon("moon/moon.obj");
	Model ModelHouse("house/house.obj");
	Model ModelClouds("clouds/clouds.obj");
	Model ModelLamp("lamp/lamp.obj");

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	bool running = true;
	GLfloat cameraSpeed;

	float temp = 0.0f;
	float fast = 0.25f;
	float radiusSun = 1.75f;
	float radiusMoon = 1.5f;
	float val = 0.0f;
	
	float opacityMoon = 0.0f;
	float opacitySun = 0.0f;

	float step = 0.0f;

	float limitTransparency = 0.2f;

	unsigned int cubemapTexture = loadCubemap(faces);

	SkyBoxShader.Use();
	SkyBoxShader.setInt("skybox", 0);
		
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
					running = false;
				} else if (keys[SDLK_w]) {
					cameraPos += cameraSpeed * cameraFront;
				} else if (keys[SDLK_s]) {
					cameraPos -= cameraSpeed * cameraFront;
				} else if (keys[SDLK_a]) {
					cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
				} else if (keys[SDLK_d]) {
					cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
				}else if (keys[SDLK_LEFT]) {
					Yaw -= rotateSpeed;

					glm::vec3 newFront;
					newFront.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
					newFront.y = sin(glm::radians(Pitch));
					newFront.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
					cameraFront = glm::normalize(newFront);

					cameraRight = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 0.1f, 0.0f)));
					cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
				} else if (keys[SDLK_RIGHT]) {
					Yaw += rotateSpeed;

					glm::vec3 newFront;
					newFront.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
					newFront.y = sin(glm::radians(Pitch));
					newFront.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
					cameraFront = glm::normalize(newFront);

					cameraRight = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 0.1f, 0.0f)));
					cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
				} else if (keys[SDLK_UP]) {
					Pitch += rotateSpeed;

					glm::vec3 newFront;
					newFront.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
					newFront.y = sin(glm::radians(Pitch));
					newFront.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
					cameraFront = glm::normalize(newFront);

					cameraRight = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 0.1f, 0.0f)));
					cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
				} else if (keys[SDLK_DOWN]) {
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
		
		glm::vec3 lightColor;
		temp = sin(currentFrame / 1000 * fast);
		val = abs(cos(currentFrame / 1000 * fast));

		if (temp > 0.0f) {
			lightColor.x = 1.0f;
			lightColor.y = temp;
			lightColor.z = temp;			
		}
		else {
			lightColor.x = val;
			lightColor.y = 0.0f;
			lightColor.z = 0.0f;			
		}
			   

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.8f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.05f);

		ourShader.setVec3("viewPos", cameraPos);
		ourShader.setFloat("material.shininess", 8.0f);
		ourShader.setFloat("opacity", 1.0f);

		ourShader.setVec3("dirLight.direction", 3.0f, -3.0f, 0.0f);
		ourShader.setVec3("dirLight.ambient", lightColor.x * 0.1f, lightColor.y * 0.1f, lightColor.z * 0.1f);
		ourShader.setVec3("dirLight.diffuse", lightColor.x, lightColor.y, lightColor.z);
		ourShader.setVec3("dirLight.specular", lightColor.x, lightColor.y, lightColor.z);

		if (temp > 0.0f) {
			//день
			step = abs(temp);		
			oneLampColor = glm::vec3(1.0f, step, step);
			twoLampColor =	glm::vec3(1.0f, step, step);
			threeLampColor = glm::vec3(1.0f, step, 1.0f);
			fourLampColor =	glm::vec3(step, step, 1.0f);
		}
		else {
			//ночь
			step = 0.0f;
			oneLampColor =	glm::vec3(1.0f, step, step);
			twoLampColor =	glm::vec3(1.0f, step, step);
			threeLampColor = glm::vec3(1.0f, step, 1.0);
			fourLampColor =	glm::vec3(step, step, 1.0f);
		}


		// point light 1
		ourShader.setVec3("pointLights[0].position", oneLampColor.x, oneLampColor.y, oneLampColor.z);
		ourShader.setVec3("pointLights[0].ambient", oneLampColor.x *0.1f, oneLampColor.y *0.1f, oneLampColor.z*0.1f);
		ourShader.setVec3("pointLights[0].diffuse", oneLampColor.x, oneLampColor.y, oneLampColor.z);
		ourShader.setVec3("pointLights[0].specular", oneLampColor.x, oneLampColor.y, oneLampColor.z);
		ourShader.setFloat("pointLights[0].constant", 1.0f);
		ourShader.setFloat("pointLights[0].linear", 0.7);
		ourShader.setFloat("pointLights[0].quadratic", 1.8);
		// point light 2
		ourShader.setVec3("pointLights[1].position", twoLampColor.x, twoLampColor.y, twoLampColor.z);
		ourShader.setVec3("pointLights[1].ambient", twoLampColor.x * 0.1f, twoLampColor.y * 0.1f, twoLampColor.z * 0.1f);
		ourShader.setVec3("pointLights[1].diffuse", twoLampColor.x, twoLampColor.y, twoLampColor.z);
		ourShader.setVec3("pointLights[1].specular", twoLampColor.x, twoLampColor.y, twoLampColor.z);
		ourShader.setFloat("pointLights[1].constant", 1.0f);
		ourShader.setFloat("pointLights[1].linear", 0.7);
		ourShader.setFloat("pointLights[1].quadratic", 1.8);
		// point light 3
		ourShader.setVec3("pointLights[2].position", threeLampColor.x, threeLampColor.y, threeLampColor.z);
		ourShader.setVec3("pointLights[2].ambient", threeLampColor.x * 0.1f, threeLampColor.y * 0.1f, threeLampColor.z * 0.1f);
		ourShader.setVec3("pointLights[2].diffuse", threeLampColor.x, threeLampColor.y, threeLampColor.z);
		ourShader.setVec3("pointLights[2].specular", threeLampColor.x, threeLampColor.y, threeLampColor.z);
		ourShader.setFloat("pointLights[2].constant", 1.0f);
		ourShader.setFloat("pointLights[2].linear", 0.7);
		ourShader.setFloat("pointLights[2].quadratic", 1.8);
		// point light 4
		ourShader.setVec3("pointLights[3].position", fourLampColor.x, fourLampColor.y, fourLampColor.z);
		ourShader.setVec3("pointLights[3].ambient", fourLampColor.x * 0.1f, fourLampColor.y * 0.1f, fourLampColor.z * 0.1f);
		ourShader.setVec3("pointLights[3].diffuse", fourLampColor.x, fourLampColor.y, fourLampColor.z);
		ourShader.setVec3("pointLights[3].specular", fourLampColor.x, fourLampColor.y, fourLampColor.z);
		ourShader.setFloat("pointLights[3].constant", 1.0f);
		ourShader.setFloat("pointLights[3].linear", 0.7);
		ourShader.setFloat("pointLights[3].quadratic", 1.8);
		// point light 5		
		ourShader.setVec3("pointLights[4].position", lightPosSun.x, lightPosSun.y, lightPosSun.z);
		ourShader.setVec3("pointLights[4].ambient", ambientColor);
		ourShader.setVec3("pointLights[4].diffuse", diffuseColor);
		ourShader.setVec3("pointLights[4].specular", 1.0f, 1.0f, 1.0f);
		ourShader.setFloat("pointLights[4].constant", 1.0f);
		ourShader.setFloat("pointLights[4].linear", 0.35);
		ourShader.setFloat("pointLights[4].quadratic", 0.44);

		glm::mat4 view;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glm::mat4 projection;
		projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);

		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		ourShader.setMat4("model", model);
				
		ModelHouse.Draw(ourShader);

		ourShader.setFloat("opacity", 0.9f);
		ModelClouds.Draw(ourShader);

		LampShader.Use();


		LampShader.setMat4("projection", projection);
		LampShader.setMat4("view", view);

		glBindVertexArray(vaoLight);
		for (unsigned int i = 0; i < 4; i++){
			
			switch (i) {
			case 0:
				LampShader.setVec4("ourColor", oneLampColor.x, oneLampColor.y, oneLampColor.z, 1.0f);
				break;
			case 1:
				LampShader.setVec4("ourColor", twoLampColor.x, twoLampColor.y, twoLampColor.z, 1.0f);
				break;
			case 2:
				LampShader.setVec4("ourColor", threeLampColor.x, threeLampColor.y, threeLampColor.z, 1.0f);
				break;
			case 3:
				LampShader.setVec4("ourColor", fourLampColor.x, fourLampColor.y, fourLampColor.z, 1.0f);
				break;
			default:
				break;
			}
			
			if (temp < 0.0f) {
				//ночь
				opacityMoon = abs(temp);
				opacitySun = 0.0f;
			}
			else {
				//день
				LampShader.setVec4("ourColor", 1.0f, 1.0f, 1.0f, 1.0f);
				opacityMoon = 0.0f;
				opacitySun = temp;
			}
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.1f)); 
			LampShader.setMat4("model", model);
			ModelLamp.Draw(LampShader);
		}

		if (opacitySun < limitTransparency)
			opacitySun = limitTransparency;

		LampShader.setVec4("ourColor", lightColor.x, lightColor.y, lightColor.z, opacitySun);
		model = glm::mat4(1.0f);
		lightPosSun.x = cos(currentFrame / 1000 * fast) * radiusSun;
		lightPosSun.y = sin(currentFrame / 1000 * fast) * radiusSun;
		lightPosSun.z = 0.0f;
		model = glm::translate(model, lightPosSun);
		model = glm::scale(model, glm::vec3(0.2f));
		LampShader.setMat4("model", model);
		ModelSun.Draw(LampShader);

		if (opacityMoon < limitTransparency)
			opacityMoon = limitTransparency;

		LampShader.setVec4("ourColor",1.0f, 1.0f, 1.0f, opacityMoon);
		model = glm::mat4(1.0f);
		lightPosMoon.x = cos(currentFrame / 1000 * fast+3.14f) * radiusMoon;
		lightPosMoon.y = sin(currentFrame / 1000 * fast+3.14f) * radiusMoon;
		lightPosMoon.z = 0.0f;
		model = glm::translate(model, lightPosMoon);
		model = glm::scale(model, glm::vec3(0.1f));
		LampShader.setMat4("model", model);
		ModelMoon.Draw(LampShader);
		
		
		glDepthFunc(GL_LEQUAL);
		SkyBoxShader.Use();
		glm::mat4 view1;
		view1 = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glm::mat4 projection1;
		projection1 = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
		SkyBoxShader.setMat4("view", view1);
		SkyBoxShader.setMat4("projection", projection1);

		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);



		SDL_GL_SwapWindow(window);
	}

}

bool CreateScene::InitSDL() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Unable to init SDL, error: " << SDL_GetError() << endl;
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);


	window = SDL_CreateWindow("Irina_Sorokina_I582", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	glcontext = SDL_GL_CreateContext(window);

	if (window == NULL) {
		return false;
	}
	   
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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


void CreateScene::InitSkyBox() {
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void CreateScene::WorkAttr() {
	if (!InitVAO() || !InitVBO() )
		return;

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); 
	return;
}


void CreateScene::Close() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vaoLight);

	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);

	printf("%s\n", glGetString(GL_VERSION));
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
	cout << "Clear finish" << endl;
}

unsigned int CreateScene::loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;


	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			GLenum format ;
			if (nrChannels == 1)
				format = GL_RED;
			else if (nrChannels == 3)
				format = GL_RGB;
			else if (nrChannels == 4)
				format = GL_RGBA;

			cout << "load side of the cube number: "<<i+1 << endl;

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
