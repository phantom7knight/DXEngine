#include "stdafx.h"



SystemClass::SystemClass()
{
	m_Input = 0;
	m_Camera = 0;
	m_Graphics = 0;
	LightPos = XMFLOAT3(0.0f, 0.0f, 2.0f);
}

SystemClass::SystemClass(const SystemClass& other)
{

}

SystemClass::~SystemClass()
{

}

bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;
	bool result;
	

	screenWidth = 0;
	screenHeight = 0;

	InitializeWindows(screenWidth, screenHeight);

	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	m_Input->Initialize();

	m_Graphics = new GraphicsClass;
	if (!m_Graphics)
	{
		return false;
	}
	
	m_Camera = new CameraClass;
	
	if (!m_Camera)
	{
		return false;
	}


	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd, LightPos);
	if (!result)
	{
		return false;
	}

	return true;
}

void SystemClass::Shutdown()
{
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	if (m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	ShutdownWindows();

	return;
}
 
void SystemClass::Run()
{
	MSG msg;
	bool done, result;

	ZeroMemory(&msg, sizeof(MSG));

	done = false;
	while (!done)
	{

		m_Graphics->Update();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			//Main loop Update stuff goes here
			result = Frame(getHandle());
			if (!result)
			{
				done = true;
			}
		}
	}
	return;
}

bool SystemClass::Frame( HWND handle)
{
	bool result;

	if (!m_Input->Update())
	{
		return false;
	}

#pragma region CamerControls
	if (m_Input->IsKeyDown(VK_UP))
	{	
		m_Graphics->Camera_PosY += 0.1f;
	}	
	if (m_Input->IsKeyDown(VK_DOWN))
	{	
		m_Graphics->Camera_PosY -= 0.1f;
	}	
	if (m_Input->IsKeyDown(VK_LEFT))
	{
		m_Graphics->Camera_PosX -= 0.1f;
	}
	if (m_Input->IsKeyDown(VK_RIGHT))
	{
		m_Graphics->Camera_PosX += 0.1f;
	}
	if (m_Input->IsKeyDown(VK_CONTROL))
	{
		m_Graphics->Camera_PosZ -= 0.1f;
	}
	if (m_Input->IsKeyDown(VK_SHIFT))
	{
		m_Graphics->Camera_PosZ += 0.1f;
	}

	//Reset the Camera Position
	if (m_Input->IsKeyDown(VK_SPACE))
	{
		m_Graphics->Camera_PosX = 0.0f;
		m_Graphics->Camera_PosY = 0.0f;
		m_Graphics->Camera_PosZ = -5.0f;
	}
#pragma endregion
	
	/*if (m_Input->IsKeyDown(VK_NUMPAD4))
	{
		LightPos.x -= 0.0f;
		std::cout << " 4 Pressed!" << std::endl;
	}*/



	result = m_Graphics->Frame();
	if (!result)
	{
		return false;
	}
	
	
	//ImguiManager::getInstance()->Update();
	
	return true;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);


LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, umsg, wparam, lparam))
	{
		return true;
	}

	switch (umsg)
	{
	case WM_KEYDOWN:
		m_Input->KeyDown((unsigned int)wparam);
		return 0;

	case WM_KEYUP:
		m_Input->KeyUp((unsigned int)wparam);
		return 0;

	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	ApplicationHandle = this;

	m_hinstance = GetModuleHandle(NULL);

	m_applicationName = L"Base Engine";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (FULL_SCREEN)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth = 800;
		screenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(true);

	return;
}

void SystemClass::ShutdownWindows()
{
	ShowCursor(true);

	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	ApplicationHandle = NULL;

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;

		default:
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
}