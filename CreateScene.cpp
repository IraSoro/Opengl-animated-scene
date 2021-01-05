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
	Shader CloudShader(vertexLamp, fragmentLamp);

	WorkAttr();
	InitLight();
	
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
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
	float fast = 0.5f;
	float radiusSun = 1.75f;
	float radiusMoon = 1.5f;
	float val = 0.0f;
	float val1 = 0.0f;

	glm::vec3 one = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 two = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 three = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 four = glm::vec3(0.0f, 0.0f, 0.0f);

	float opacityMoon = 0.0f;
	float opacitySun = 0.0f;

	float step = 0.0f;

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

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.Use();
		
		glm::vec3 lightColor;
		temp = sin(currentFrame / 1000 * fast);
		val = abs(cos(currentFrame / 1000 * fast));
		val1 = val / 3;
		float val2 = val + 0.1f;

		if (temp > 0.0f) {
			lightColor.x = 1.0f;
			lightColor.y = temp;
			lightColor.z = temp;
			/*
			if (temp < val1) {
				lightColor.y = val1;
				lightColor.z = val1;
			}
			else {
				lightColor.y = temp;
				lightColor.z = temp;
			}
			*/
		}
		else {
			
			//lightColor.x = val;
			//lightColor.y = val1;
			//lightColor.z = val1;
			
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
			one = glm::vec3(1.0f, step, step);
			two =	glm::vec3(1.0f, step, step);
			three = glm::vec3(1.0f, step, 1.0f);
			four =	glm::vec3(step, step, 1.0f);
		}
		else {
			//ночь
			step = 0.0f;
			one =	glm::vec3(1.0f, step, step);
			two =	glm::vec3(1.0f, step, step);
			three = glm::vec3(1.0f, step, 1.0);
			four =	glm::vec3(step, step, 1.0f);
		}


		// point light 1
		ourShader.setVec3("pointLights[0].position", one.x, one.y, one.z);
		ourShader.setVec3("pointLights[0].ambient", one.x *0.1f, one.y *0.1f, one.z*0.1f);
		ourShader.setVec3("pointLights[0].diffuse", one.x, one.y, one.z);
		ourShader.setVec3("pointLights[0].specular", one.x, one.y, one.z);
		ourShader.setFloat("pointLights[0].constant", 1.0f);
		ourShader.setFloat("pointLights[0].linear", 0.7);
		ourShader.setFloat("pointLights[0].quadratic", 1.8);
		// point light 2
		ourShader.setVec3("pointLights[1].position", two.x, two.y, two.z);
		ourShader.setVec3("pointLights[1].ambient", two.x * 0.1f, two.y * 0.1f, two.z * 0.1f);
		ourShader.setVec3("pointLights[1].diffuse", two.x, two.y, two.z);
		ourShader.setVec3("pointLights[1].specular", two.x, two.y, two.z);
		ourShader.setFloat("pointLights[1].constant", 1.0f);
		ourShader.setFloat("pointLights[1].linear", 0.7);
		ourShader.setFloat("pointLights[1].quadratic", 1.8);
		// point light 3
		ourShader.setVec3("pointLights[2].position", three.x, three.y, three.z);
		ourShader.setVec3("pointLights[2].ambient", three.x * 0.1f, three.y * 0.1f, three.z * 0.1f);
		ourShader.setVec3("pointLights[2].diffuse", three.x, three.y, three.z);
		ourShader.setVec3("pointLights[2].specular",three.x, three.y, three.z);
		ourShader.setFloat("pointLights[2].constant", 1.0f);
		ourShader.setFloat("pointLights[2].linear", 0.7);
		ourShader.setFloat("pointLights[2].quadratic", 1.8);
		// point light 4
		ourShader.setVec3("pointLights[3].position", four.x, four.y, four.z);
		ourShader.setVec3("pointLights[3].ambient", four.x * 0.1f, four.y * 0.1f, four.z * 0.1f);
		ourShader.setVec3("pointLights[3].diffuse",  four.x, four.y, four.z);
		ourShader.setVec3("pointLights[3].specular", four.x, four.y, four.z);
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
		
		// spotLight
		/*
		ourShader.setVec3("spotLight.position", cameraPos);
		ourShader.setVec3("spotLight.direction", cameraFront);
		ourShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		ourShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		ourShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		ourShader.setFloat("spotLight.constant", 1.0f);
		ourShader.setFloat("spotLight.linear", 0.09);
		ourShader.setFloat("spotLight.quadratic", 0.032);
		ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		*/

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

		ourShader.setFloat("opacity", 0.2f);
		ModelClouds.Draw(ourShader);

		LampShader.Use();


		LampShader.setMat4("projection", projection);
		LampShader.setMat4("view", view);

		glBindVertexArray(vaoLeght);
		for (unsigned int i = 0; i < 4; i++){
			
			switch (i) {
			case 0:
				LampShader.setVec4("ourColor", one.x, one.y, one.z, 1.0f);
				break;
			case 1:
				LampShader.setVec4("ourColor", two.x, two.y, two.z, 1.0f);
				break;
			case 2:
				LampShader.setVec4("ourColor", three.x, three.y, three.z, 1.0f);
				break;
			case 3:
				LampShader.setVec4("ourColor", four.x, four.y, four.z, 1.0f);
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

		if (opacitySun < 0.2f)
			opacitySun = 0.2f;

		LampShader.setVec4("ourColor", lightColor.x, lightColor.y, lightColor.z, opacitySun);
		model = glm::mat4(1.0f);
		lightPosSun.x = cos(currentFrame / 1000 * fast) * radiusSun;
		lightPosSun.y = sin(currentFrame / 1000 * fast) * radiusSun;
		lightPosSun.z = 0.0f;
		model = glm::translate(model, lightPosSun);
		model = glm::scale(model, glm::vec3(0.2f)); 
		LampShader.setMat4("model", model);
		ModelSun.Draw(LampShader);

		if (opacityMoon < 0.2f)
			opacityMoon = 0.2f;

		LampShader.setVec4("ourColor",1.0f, 1.0f, 1.0f, opacityMoon);
		model = glm::mat4(1.0f);
		lightPosMoon.x = cos(currentFrame / 1000 * fast+3.14f) * radiusMoon;
		lightPosMoon.y = sin(currentFrame / 1000 * fast+3.14f) * radiusMoon;
		lightPosMoon.z = 0.0f;
		model = glm::translate(model, lightPosMoon);
		model = glm::scale(model, glm::vec3(0.1f));
		LampShader.setMat4("model", model);
		ModelMoon.Draw(LampShader);
		

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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
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


