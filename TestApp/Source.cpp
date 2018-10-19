#include "Source.h"

using namespace ph_engine;

int main() {
	cout << "Photon Engine v" << ph_engine::VERSION_MAJOR << "." << ph_engine::VERSION_MINOR << endl;

	int width = 800, height = 600;

	Window window(width, height, "Photon Engine test app");
	window.setActive();
	
	Keyboard keyboard(window);
	Mouse mouse(window);
	mouse.setPosition(width / 2, height / 2);
	mouse.setSensitivity(.5f);

	Shader vert, frag;
	vert.loadFromFile("res/shader/vertex.glsl", SHADER_TYPE::VERTEX);
	frag.loadFromFile("res/shader/fragment.glsl", SHADER_TYPE::FRAGMENT);

	ShaderProgram program;
	program.addShader(vert);
	program.addShader(frag);

	program.link();
	vert.remove();
	frag.remove();
	
	window.hideCursor();

	Player player(glm::vec3(0, 1, -2), 0.005f);
	Camera camera(glm::vec3(0, 1, -2), glm::vec3(0, 0, -3));

	bool isFreeCam = false;

	const glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)width / (float)height, 0.1f, 100.f);

	glm::vec3 lightPos(0, 0, 0);
	Color color(1, 1, 1);
	Light light(lightPos, glm::vec3(1), color, Light::DIRECTION);

	light.setAmbient(0.0001);
	light.setDiffuse(1);
	light.setSpecular(0.0001);

	Model pumpkin;
	pumpkin.load("res/model/pumpkin/pumpkin.fbx");
	pumpkin.translate(0, 0, -3);
	pumpkin.scale(1.f / 256.f);

	while (!window.shouldClose()) {
		window.pollEvents();

		switch (keyboard.getPressedKey()) {
			case Keyboard::KEY_ESCAPE:
				window.close();
				break;

			case Keyboard::KEY_2:
				isFreeCam = true;
				break;

			case Keyboard::KEY_1:
				isFreeCam = false;
				break;
		}

		if (isFreeCam) {
			player.move(keyboard);
			player.look(mouse);
		}

		window.clear();

		program.use();
		
		//draw here
		light.getPosition().x = glm::sin(System::getTime()) * 4;
		light.getPosition().z = glm::cos(System::getTime()) * 4;
		light.sendInShader(program, "light");
		
		if (isFreeCam) {
			program.setMat4("view", player.getViewMatrix());
			program.setVec3("viewPos", player.getPosition());
		} else {
			program.setMat4("view", camera.getViewMatrix());
			program.setVec3("viewPos", camera.getPosition());
		}
		program.setMat4("projection", projection);
		program.setMat4("model", pumpkin.getModelMatrix());
		pumpkin.draw(program);

		window.swapBuffer();
	}

	return EXIT_SUCCESS;
}