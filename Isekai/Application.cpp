#include "Application.h"
#include <iostream>

Application::Application() {
	m_direct3D = nullptr;
	m_camera = nullptr;
	m_model = nullptr;
	m_colorShader = nullptr;
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

	// Create the camera object.
	m_camera = new Camera();
	
	// Set the initial position of the camera.
	m_camera->setPosition(0.0, 0.0, -5.0f);

	// Create and initialize the model object.
	m_model = new Model();

	result = m_model->initialize(m_direct3D->getDevice());
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the color shader object.
	m_colorShader = new ColorShader();

	result = m_colorShader->initialize(m_direct3D->getDevice(), hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void Application::shutdown() {
	// Release the color shader object.
	if (m_colorShader)
	{
		m_colorShader->shutdown();
		delete m_colorShader;
		m_colorShader = nullptr;
	}

	// Release the model object.
	if (m_model)
	{
		m_model->shutdown();
		delete m_model;
		m_model = nullptr;
	}

	// Release the camera object.
	if (m_camera)
	{
		delete m_camera;
		m_camera = nullptr;
	}

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
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	m_direct3D->beginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_camera->render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_direct3D->getWorldMatrix(worldMatrix);
	m_camera->getViewMatrix(viewMatrix);
	m_direct3D->getProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_model->render(m_direct3D->getDeviceContext());

	// Render the model using the color shader.
	result = m_colorShader->render(m_direct3D->getDeviceContext(), m_model->getIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result) {
		return false;
	}

	// Present the rendered scene to the screen.
	m_direct3D->endScene();

	return true;
}

