// dllmain.cpp : Defines the entry point for the DLL application.
#include "Config.h"

#include "GLFW/glfw3.h"

#include <iostream>

void error_callback(int error, const char* desc) {
	std::cerr << "GLFW Error(" << error << "): " << desc << std::endl;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved){
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		glfwInit();

		glfwSetErrorCallback(error_callback);
	} else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
		glfwTerminate();
	}

    return TRUE;
}

