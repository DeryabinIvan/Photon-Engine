﻿#include "Source.h"

using namespace ph_engine;

int frames = 0;
bool secondPass = false;

void frameEvent() {
	frames = 0;
	secondPass = true;
}

int main() {
	cout << "Photon Engine v" << ph_engine::VERSION_MAJOR << "." << ph_engine::VERSION_MINOR << endl;

	int width = 800, height = 600;

	cout << "Starting app...\n";
	Timer timer;
	timer.start();

	Window::WindowSettings settings;
	settings.framerate = 60;

	Window window(width, height, "Photon Engine test app", settings);
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

	glm::vec3 position = glm::vec3(0, 1, 1), viewDirection;

	Player player(position, 4.0f / 144.0f);
	Camera camera(position, glm::vec3(0, 0, -3));

	bool isFreeCam = false, isMoving = true;

	const glm::mat4 projection = glm::perspective(glm::radians(90.f), (float)width / (float)height, 0.1f, 100.f);

	glm::vec3 lightPos(0, 0, 0);
	Color red(1, 0, 0), green(0, 1, 0), blue(0, 0, 1), white(1, 1, 1), grey(.5, .5, .5);
	Light dotL, spot;

	dotL.makeDot(lightPos, white);
	dotL.setAmbient(0.1f);
	dotL.setDiffuse(0.5f);
	dotL.setSpecular(1.f);
	dotL.setAttenuation(0.032f, 0.09f, 1.f);
	dotL.getPosition().y = 0.5;

	spot.makeSpot(position, glm::vec3(0, 0, -3), 10, 20, white);
	spot.setAmbient(0.f);
	spot.setDiffuse(0.5f);
	spot.setSpecular(1.f);
	spot.setAttenuation(0.032f, 0.09f, 1.f);

	Model cube;
	cube.loadModel("res/model/cube/cube.obj");
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

	float floorVertices[] = {
	//  |   positions     |   normal   | texture |
		-1.f, -1.f,  1.f, 0.f, 1.f, 0.f, 0.f, 1.f,
		-1.f, -1.f, -1.f, 0.f, 1.f, 0.f, 0.f, 0.f,
		 1.f, -1.f, -1.f, 0.f, 1.f, 0.f, 1.f, 0.f,
	//  |    positions    |   normal   | texture |
		-1.f, -1.f,  1.f, 0.f, 1.f, 0.f, 0.f, 1.f,
		 1.f, -1.f, -1.f, 0.f, 1.f, 0.f, 1.f, 0.f,
		 1.f, -1.f,  1.f, 0.f, 1.f, 0.f, 1.f, 1.f
	};

	MeshDataHelper quadOffsets, floorOffsets;
	quadOffsets.setVertex(0, 2);
	quadOffsets.setTexture(2, 2);

	floorOffsets.setVertex(0, 3);
	floorOffsets.setNormal(3, 3);
	floorOffsets.setTexture(6, 2);

	Mesh plane(quadOffsets, quadVertices, sizeof(quadVertices) / sizeof(float));

	Mesh floor(floorOffsets, floorVertices, sizeof(floorVertices) / sizeof(float));
	floor.loadTextures("res/model/floor.png", "res/model/floor.png");
	 
	floor.translate(0, 0, 0);
	vec3 rotateAxis = vec3(1, 0, 0);

	Texture color, depth;
	FrameBuffer framebuffer;

	/*RenderBuffer renderbuffer;
	renderbuffer.bind();
	renderbuffer.create(GL_DEPTH_COMPONENT24, width, height);
	renderbuffer.bindBaseBuffer();*/

	color.emptyTexture(Texture::TEXTURE_TYPE::COLOR, width, height);
	depth.emptyTexture(Texture::TEXTURE_TYPE::DEPTH, width, height);

	framebuffer.bind();
	framebuffer.attachTexture(color, FrameBuffer::AttachmentType::COLOR);
	framebuffer.attachTexture(depth, FrameBuffer::AttachmentType::DEPTH);
	//framebuffer.attachRenderBuffer(renderbuffer, GL_DEPTH_ATTACHMENT);

	if (framebuffer.checkErrors()) {
		cerr << "FRAMEBUFFER NOT COMPLETE" << endl;
		System::printGLError();
	}
	framebuffer.bindBaseBuffer();

	cout << "\nSetup completed in " << timer.timestamp() << "s\n";

	timer.setDuration(1000);
	timer.setTimerCallback(frameEvent);
	timer.startMT();

	std::stringstream ss;

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
			if (secondPass) {
				player.setSpeed(1.f / (frames * 10));
				secondPass = false;
			}
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
			position = player.getPosition();
			viewDirection = player.getFrontVec();
			
			ss  << "Posistion. X: "       << position.x      << " Y: " << position.y      << " Z: " << position.z << " " 
				<<  "View direction. X: " << viewDirection.x << " Y: " << viewDirection.y << " Z: " << viewDirection.z;

			window.setTitle(ss.str());
			ss.str("");

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

		program.setMat4("model", floor.getModelMatrix());
		floor.draw(program);

		//screen render
		framebuffer.bindBaseBuffer();
		window.disableFeature(GL_DEPTH_TEST);
		window.clearColor(grey);
		window.clearBuffers(GL_COLOR_BUFFER_BIT);

		screenProg.use();
		color.bind();
		plane.draw(screenProg);

		if (keyboard.keyPressedOnce(Keyboard::KEY_F12)) {
			color.save("color_buffer.png");
			std::cerr << "F12 pressed" << std::endl;
		}

		window.swapBuffer();
		frames++;
	}

	timer.stopMT();

	return EXIT_SUCCESS;
}