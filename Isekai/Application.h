#ifndef _Application_H_
#define _Application_H_

#include<Windows.h>

#include "Direct3D.h"
#include "Camera.h"
#include "Model.h"
#include "Light.h"
#include "LightShader.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.3f;

class Application {
public:
	Application();
	Application(const Application&);
	~Application();

	bool initialize(int, int, HWND);
	void shutdown();
	bool frame();

private:
	bool render(float);

private:
	Direct3D* m_direct3D;
	Camera* m_camera;
	Model* m_model;
	LightShader* m_lightShader;
	Light* m_lights;
	int m_numLights;
};

#endif

