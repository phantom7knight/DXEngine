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

void ImguiManager::Init()
{
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	////io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//
	////ImGui_ImplWin32_Init(m_d3dobj.);
	////ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
	//
	//// Setup style
	//ImGui::StyleColorsDark();
}

void ImguiManager::Update()
{
}

void ImguiManager::Destroy()
{
}

