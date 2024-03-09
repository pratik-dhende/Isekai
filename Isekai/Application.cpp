#include "Application.h"
#include <iostream>

Application::Application() {
	m_direct3D = nullptr;
	m_camera = nullptr;
	m_model = nullptr;
	m_light = nullptr;
	m_lightShader = nullptr;
}

Application::Application(const Application& other) {

}

Application::~Application() {

}

bool Application::initialize(int screenWidth, int screenHeight, HWND hwnd) {
	char modelFileName[128];
	char textureFileName[128];
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
	m_camera->setPosition(0.0, 0.0, -10.0f);

	// Create and initialize the model object.
	m_model = new Model();

	// Set the file name of the model.
	strcpy_s(modelFileName, "../Isekai/data/sphere.txt");

	// Set the name of the texture file that we will be loading.
	strcpy_s(textureFileName, "../Isekai/data/stone01.tga");

	result = m_model->initialize(m_direct3D->getDevice(), m_direct3D->getDeviceContext(), modelFileName, textureFileName);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the light shader object.
	m_lightShader = new LightShader();

	result = m_lightShader->initialize(m_direct3D->getDevice(), hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the light object.
	m_light = new Light();

	m_light->setAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_light->setDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_light->setDirection(1.0f, 0.0f, 1.0f);
	m_light->setSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_light->setSpecularPower(32.0f);

	return true;
}

void Application::shutdown() {
	// Release the light object.
	if (m_light){
		delete m_light;
		m_light = nullptr;
	}

	// Release the light shader object.
	if (m_lightShader)
	{
		m_lightShader->shutdown();
		delete m_lightShader;
		m_lightShader = nullptr;
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
	static float rotation = 0.0f;
	bool result;

	// Update the rotation variable each frame.
	rotation -= 0.0174532925f * 0.8f;
	if (rotation < 0.0f) {
		rotation += 360.0f;
	}

	// Render the graphics scene.
	result = render(rotation);

	return result;
}

bool Application::render(float rotation) {
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

	// Rotate the world matrix by the rotation value so that the model will spin.
	worldMatrix = XMMatrixRotationY(rotation);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_model->render(m_direct3D->getDeviceContext());

	// Render the model using the light shader.
	result = m_lightShader->render(m_direct3D->getDeviceContext(), m_model->getIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_model->getTexture(), m_light->getDirection(), m_light->getAmbientColor(), m_light->getDiffuseColor(), m_camera->getPosition(), m_light->getSpecularColor(), m_light->getSpecularPower());
	if (!result) {
		return false;
	}

	// Present the rendered scene to the screen.
	m_direct3D->endScene();

	return true;
}

