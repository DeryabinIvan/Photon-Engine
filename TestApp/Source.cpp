#include "Source.h"

const double c_1TO60 = 1.0 / 60.0;

int main() {
	cout << "Photon Engine v" << ph_engine::VERSION_MAJOR << "." << ph_engine::VERSION_MINOR << endl;

	ph_engine::Window window(800, 600, "Photon Engine test app"), test(640, 480, "Second window");
	
	while (!window.shouldClose() && !test.shouldClose()) {
		window.pollEvents();
		
		window.setActive();
		window.swapBuffer();

		test.setActive();
		test.swapBuffer();
	}

	return EXIT_SUCCESS;
}