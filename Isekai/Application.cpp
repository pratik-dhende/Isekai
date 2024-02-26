#include "Application.h"

Application::Application() {
	m_direct3D = nullptr;
}

Application::Application(const Application& other) {

}

Application::~Application() {

}

bool Application::initialize(int screenWidth, int screenHeight, HWND hwnd) {
	bool result;

	// Create and initialize the Direct3D object.
	m_direct3D = new Direct3D();
	result = m_direct3D->initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);

	if (!result) {
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	return true;
}

void Application::shutdown() {
	// Release the Direct3D object.
	if (m_direct3D) {
		m_direct3D->shutdown();
		delete m_direct3D;
		m_direct3D = nullptr;
	}
}

bool Application::frame() {
	bool result;

	// Render the graphics scene.
	result = render();

	return result;
}

bool Application::render() {
	// Clear the buffers to begin the scene.
	m_direct3D->beginScene(0.5f, 0.5f, 0.5f, 1.0f);

	// Present the rendered scene to the screen.
	m_direct3D->endScene();

	return true;
}

