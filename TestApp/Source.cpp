#include "Source.h"

const double c_1TO60 = 1.0 / 60.0;

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

	Model testModel;
	testModel.load("res/model/pumpkin/pumpkin.fbx");
	testModel.translate(0, 0, 2);
	testModel.scale(1.f/256.f);

	Player player(0, 0, 3, 0.005f);
	window.hideCursor();

	while (!window.shouldClose()) {
		window.pollEvents();

		switch (keyboard.getPressedKey()) {
			case Keyboard::KEY_ESCAPE:
			window.close();
			break;
		}
		
		player.move(keyboard);
		player.look(mouse);

		window.clear();

		program.use();
		glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)width / (float)height, 0.1f, 100.f);
		
		program.setMat4("model", testModel.getModelMatrix());
		program.setMat4("view", player.getViewMatrix());
		program.setMat4("projection", projection);

		//draw here
		testModel.draw(program);

		window.swapBuffer();
	}
	return EXIT_SUCCESS;
}