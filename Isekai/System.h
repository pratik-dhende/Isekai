#ifndef _System_H_
#define _System_H_

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "Input.h"
#include "Application.h"

class System {
public:
	System();
	System(const System&);
	~System();

	bool initialize();
	void shutdown();
	void run();

	LRESULT CALLBACK messageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool frame();
	void initializeWindows(int&, int&);
	void shutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hInstance;
	HWND m_hwnd;

	Input* m_input;
	Application* m_application;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static System* ApplicationHandle = nullptr;

#endif
