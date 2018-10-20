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
	Color red(1, 0, 0), green(0, 1, 0), blue(0, 0, 1), white(1, 1, 1);
	Light dirL, dotL, spotL;

	dirL.makeDirected(glm::vec3(1, 0, 0), green);
	dirL.setAmbient(0.1);
	dirL.setDiffuse(0.01);
	dirL.setSpecular(0);

	dotL.makeDot(lightPos, red);
	dotL.setAmbient(0.1);
	dotL.setDiffuse(0.01);
	dotL.setSpecular(0);

	spotL.makeSpot(player.getPosition(), camera.getFrontVec(), 2, 10, white);
	spotL.setAmbient(0.1);
	spotL.setDiffuse(0.01);
	spotL.setSpecular(0);

	dotL.setAttenuation(0.032, 0.09, 1);
	spotL.setAttenuation(0.032, 0.09, 1);

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
		dotL.getPosition().x = glm::sin(System::getTime()) * 4;
		dotL.getPosition().z = -3 + glm::cos(System::getTime()) * 4;

		dotL.sendInShader(program, "l1");
		dirL.sendInShader(program, "l2");
		spotL.sendInShader(program, "l3");
		
		if (isFreeCam) {
			program.setMat4("view", player.getViewMatrix());
			program.setVec3("viewPos", player.getPosition());
			spotL.setPosition(player.getPosition());
			spotL.setDirection(player.getFrontVec());
		} else {
			program.setMat4("view", camera.getViewMatrix());
			program.setVec3("viewPos", camera.getPosition());
			spotL.setPosition(camera.getPosition());
			spotL.setDirection(camera.getFrontVec());
		}
		program.setMat4("projection", projection);
		program.setMat4("model", pumpkin.getModelMatrix());
		pumpkin.draw(program);

		window.swapBuffer();
	}

	return EXIT_SUCCESS;
}