#include "stdafx.h"
#include "System.h"

double ph_engine::System::getTime() {
	return glfwGetTime();
}

void ph_engine::System::setTime(double time) {
	glfwSetTime(time);
}
