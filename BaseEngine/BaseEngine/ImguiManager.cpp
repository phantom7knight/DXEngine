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



void TestWindow()
{
	ImGui::Begin("Test");

	ImGui::End();

}



void ImguiManager::Init( HWND handle, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	////io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//
	//ImGui_ImplWin32_Init(handle);
	//ImGui_ImplDX11_Init(device, deviceContext);
	//
	//// Setup style
	//ImGui::StyleColorsDark();
}

void ImguiManager::Update()
{
	//ImGui_ImplDX11_NewFrame();
	//ImGui_ImplWin32_NewFrame();
	//ImGui::NewFrame();
	//
	////==================================================
	//// Call all the Window rendering calls here
	////==================================================
	//
	//
	//void TestWindow();
	//
	//
	//
	////==================================================
	//
	//
	//ImGui::Render();
	//ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImguiManager::Destroy()
{
}



