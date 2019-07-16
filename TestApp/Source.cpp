﻿#include "Source.h"

using namespace ph_engine;

int main() {
	cout << "Photon Engine v" << ph_engine::VERSION_MAJOR << "." << ph_engine::VERSION_MINOR << endl;

	int width = 800, height = 600;

	cout << "Starting app...\n";
	Timer timer;
	timer.start();

	Window window(width, height, "Photon Engine test app");
	window.setActive();
	System::activeDebugOutput();
	
	Keyboard keyboard(window);
	Mouse mouse(window);
	mouse.setPosition(width / 2, height / 2);
	mouse.setSensitivity(.5f);

	Shader vert, frag;
	vert.loadFromFile("res/shader/vertex.glsl", Shader::VERTEX);
	frag.loadFromFile("res/shader/fragment.glsl", Shader::FRAGMENT);

	ShaderProgram program;
	program.addShader(vert);
	program.addShader(frag);

	program.link();
	vert.remove();
	frag.remove();
	
	window.hideCursor();

	glm::vec3 position = glm::vec3(0, 1, 0);

	Player player(position, 0.005f);
	Camera camera(position, glm::vec3(0, 0, -3));

	bool isFreeCam = false, isMoving = true;

	const glm::mat4 projection = glm::perspective(glm::radians(90.f), (float)width / (float)height, 0.1f, 100.f);

	glm::vec3 lightPos(0, 0, 0);
	Color red(1, 0, 0), green(0, 1, 0), blue(0, 0, 1), white(1, 1, 1), grey(.5, .5, .5);
	Light dotL, spot;

	dotL.makeDot(lightPos, white);
	dotL.setAmbient(0.1);
	dotL.setDiffuse(0.5);
	dotL.setSpecular(1);
	dotL.setAttenuation(0.032, 0.09, 1);
	dotL.getPosition().y = 0.5;

	spot.makeSpot(position, glm::vec3(0, 0, -3), 10, 20, white);
	spot.setAmbient(0);
	spot.setDiffuse(0.5);
	spot.setSpecular(1);
	spot.setAttenuation(0.032, 0.09, 1);

	const std::string path = "res/model/";

	Model cube;

	cube.load(path + "cube/cube.obj");
	cube.translate(0, 0, -3);

	Shader fragScreen, vertScreen;
	fragScreen.loadFromFile("res/shader/framebuffer_fs.glsl", Shader::FRAGMENT);
	vertScreen.loadFromFile("res/shader/framebuffer_vs.glsl", Shader::VERTEX);

	ShaderProgram screenProg;
	screenProg.addShader(vertScreen);
	screenProg.addShader(fragScreen);

	screenProg.link();
	vertScreen.remove();
	fragScreen.remove();

	float quadVertices[] = {
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};
	VertexArray quadVAO;
	VertexBuffer quadVBO;
	quadVAO.bind();
		quadVBO.bind();
			quadVBO.load(sizeof(quadVertices), &quadVertices);

			quadVBO.enableAttrib(0);
			quadVBO.addVertexAttrib(0, 2, false, 4 * sizeof(float), (void*)0);

			quadVBO.enableAttrib(1);
			quadVBO.addVertexAttrib(1, 2, false, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		quadVBO.unbind();
	quadVAO.unbind();

	//RenderBuffer renderbuffer;
	FrameBuffer framebuffer;

	Texture color, depth;

	color.emptyTexture(Texture::COLOR, width, height);
	depth.emptyTexture(Texture::DEPTH, width, height);

	framebuffer.bind();
	framebuffer.attachTexture(color, FrameBuffer::COLOR);
	framebuffer.attachTexture(depth, FrameBuffer::DEPTH);
	if (framebuffer.checkErrors()) {
		cerr << "FRAMEBUFFER NOT COMPLETE" << endl;
		System::printGLError();
	}
	framebuffer.bindBaseBuffer();

	cout << "\nSetup completed in " << timer.step() << "s\n";

	timer.setDuration(2000);
	timer.setTimerCallback([] {
		cout << "<--Timer event-->\n";
		});
	timer.startMT();

	//Render loop
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

		if (keyboard.keyPressedOnce(Keyboard::KEY_F)) {
			isMoving = !isMoving;
		}

		if (isFreeCam) {
			player.move(keyboard);
			player.look(mouse);
		}
		
		//framebuffer render
		framebuffer.bind();
		window.enableFeature(GL_DEPTH_TEST);
		window.clearColor(grey);
		window.clearBuffers(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program.use();
		
		//draw here
		if (isMoving) {
			dotL.getPosition().x = glm::sin(System::getTime()) * 1.5;
			dotL.getPosition().z = -3 + glm::cos(System::getTime()) * 1.5;
		}
		
		if (isFreeCam) {
			program.setMat4("view", player.getViewMatrix());

			spot.setPosition(player.getPosition());
			spot.setDirection(player.getFrontVec());

			program.setVec3("viewPos", player.getPosition());
		} else {
			program.setMat4("view", camera.getViewMatrix());

			spot.setPosition(camera.getPosition());
			spot.setDirection(camera.getFrontVec());

			program.setVec3("viewPos", camera.getPosition());
		}

		dotL.sendInShader(program, "l");
		spot.sendInShader(program, "s");

		program.setMat4("projection", projection);
		program.setMat4("model", cube.getModelMatrix());
		cube.draw(program);

		//screen render
		framebuffer.bindBaseBuffer();
		window.disableFeature(GL_DEPTH_TEST);
		window.clearColor(grey);
		window.clearBuffers(GL_COLOR_BUFFER_BIT);

		screenProg.use();
		quadVAO.bind();
		color.bind();
		window.draw(Window::TRIANGLES, 0, 6);

		if (keyboard.keyPressedOnce(Keyboard::KEY_F12)) {
			color.save("color_buffer.png");
			depth.save("depth_buffer.png");
			std::cerr << "F12 pressed" << std::endl;
		}

		window.swapBuffer();
	}

	timer.stopMT();

	return EXIT_SUCCESS;
}