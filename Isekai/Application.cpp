#include "Application.h"

Application::Application() {

}

Application::Application(const Application& other) {

}

Application::~Application() {

}

bool Application::initialize(int screenWidth, int screenHeight, HWND hwnd) {
	return true;
}

void Application::shutdown() {

}

bool Application::frame() {
	return true;
}

bool Application::render() {
	return true;
}

