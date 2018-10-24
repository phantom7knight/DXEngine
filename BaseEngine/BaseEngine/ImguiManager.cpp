#include "stdafx.h"
#include "ImguiManager.h"


ImguiManager* ImguiManager::m_Instance = nullptr;


ImguiManager::ImguiManager()
{
}

ImguiManager * ImguiManager::getInstance()
{
	if (!m_Instance)
		m_Instance = new ImguiManager();

	return m_Instance;
}


ImguiManager::~ImguiManager()
{
}

void ImguiManager::Init( HWND handle)
{
	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	
	//ImGui_ImplWin32_Init(handle);
	//ImGui_ImplDX11_Init(m_d3dobj.GetDevice(), m_d3dobj.GetDeviceContext());
	
	// Setup style
	//ImGui::StyleColorsDark();
}

void ImguiManager::Update()
{
}

void ImguiManager::Destroy()
{
}

