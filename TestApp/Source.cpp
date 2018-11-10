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
	vert.loadFromFile("res/shader/vertex.glsl", Shader::VERTEX);
	frag.loadFromFile("res/shader/fragment.glsl", Shader::FRAGMENT);

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
	Light dotL;

	dotL.makeDot(lightPos, white);
	dotL.setAmbient(0.2);
	dotL.setDiffuse(0.5);
	dotL.setSpecular(1);
	dotL.setAttenuation(0.032, 0.09, 1);

	const std::string path = "res/model/";

	Model model;

	model.load(path + "cube/cube.fbx");
	model.translate(0, 0, -3);
	model.scale(1.f / 2.f);

	PhongMaterial material;
	material.loadDiffuse("res/model/cube/container.jpg", 0);
	material.loadSpecular("res/model/cube/container2_specular.png", 1);
	material.setShininess(2);

	FrameBuffer framebuffer;
	RenderBuffer renderbuffer;

	renderbuffer.bind();
	renderbuffer.create(width, height);
	renderbuffer.bindBaseBuffer();

	framebuffer.bind();
	System::printGLError();

	framebuffer.attachTexture(width, height, FrameBuffer::COLOR);
	System::printGLError();

	framebuffer.attachRenderBuffer(renderbuffer);
	System::printGLError();

	framebuffer.bindBaseBuffer();
	System::printGLError();

	if (framebuffer.checkErrors()) {
		cerr << "FRAMEBUFFER NOT COMPLETE" << endl;
		System::printGLError();
	}

	Shader fragScreen, vertScreen;
	fragScreen.loadFromFile("res/shader/framebuffer_fs.glsl", Shader::FRAGMENT);
	vertScreen.loadFromFile("res/shader/framebuffer_vs.glsl", Shader::VERTEX);

	ShaderProgram screenProg;
	screenProg.addShader(fragScreen);
	screenProg.addShader(vertScreen);

	screenProg.link();
	fragScreen.remove();
	vertScreen.remove();

	float quadVertices[] = {
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};
	VAO quadVAO;
	VBO quadVBO;
	quadVAO.bind();
		quadVBO.bind();
			quadVBO.load(sizeof(quadVertices), &quadVertices);

			quadVBO.enableAttrib(0);
			quadVBO.addVertexAttrib(0, 2, false, 4, 0);

			quadVBO.enableAttrib(1);
			quadVBO.addVertexAttrib(1, 2, false, 4, (void*)(2 * sizeof(float)));
		quadVBO.unbind();
	quadVAO.unbind();

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
				
		framebuffer.bind();
		window.enableFeature(GL_DEPTH_TEST);
		window.clear();

		program.use();
		
		//draw here
		dotL.getPosition().x = glm::sin(System::getTime()) * 4;
		dotL.getPosition().z = -3 + glm::cos(System::getTime()) * 4;

		dotL.sendInShader(program, "l");
		material.sendInShader(program, "material");

		material.activeDiffuse();
		material.activeSpecular();
		
		if (isFreeCam) {
			program.setMat4("view", player.getViewMatrix());
			program.setVec3("viewPos", player.getPosition());
		} else {
			program.setMat4("view", camera.getViewMatrix());
			program.setVec3("viewPos", camera.getPosition());
		}
		program.setMat4("projection", projection);
		program.setMat4("model", model.getModelMatrix());
		model.draw(program);

		//framebuffer render
		framebuffer.bindBaseBuffer();
		window.disableFeature(GL_DEPTH_TEST);
		window.clear(white);

		screenProg.use();
		quadVAO.bind();
		framebuffer.bindTexture();
		window.draw(Window::TRIANGLES, 0, 6);

		window.swapBuffer();
	}

	return EXIT_SUCCESS;
}