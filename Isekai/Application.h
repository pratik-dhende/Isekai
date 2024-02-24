#ifndef _Application_H_
#define _Application_H_

#include<Windows.h>

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
	bool render();
};

#endif

