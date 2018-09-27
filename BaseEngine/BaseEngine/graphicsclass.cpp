#include "stdafx.h"

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_TextureShader = 0;
	m_ColorShader = 0;
	m_Light = 0;
	m_LightShader = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{

}

GraphicsClass::~GraphicsClass()
{

}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd, XMFLOAT3 LightPos)
{
	bool result;

	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize DIRECT3D", L"Error", MB_OK);
		return false;
	}
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);

	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	result = m_Model->Initialize(m_D3D->GetDevice(),m_D3D->GetDeviceContext() ,(char*)"../BaseEngine/data/stone01.tga");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object", L"Error", MB_OK);
		return false;
	}

	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Texture shader object.", L"Error", MB_OK);
		return false;
	}

	//Init Light shader object

	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Light shader object.", L"Error", MB_OK);
		return false;
	}

	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}


	//We set the  color and the light direction
	m_Light->SetDiffuseColor(1.0f, 0.0f, 0.5f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetAmbientColor(1.0f, 0.0f, 0.5f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);
	//m_Light->SetDirection(LightPos.x, LightPos.y, LightPos.z);
	

	return true;
}

void GraphicsClass::Shutdown()
{

	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}


	/*if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}*/

	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	return;
}

bool GraphicsClass::Frame()
{
	bool result;
	static float rotation = 0.0f;

	rotation += (float)PI_ *0.01f;

	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	
	result = Render(rotation);
	if (!result)
	{
		return false;
	}
	return true;
}

bool GraphicsClass::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	m_D3D->BeginScene(0.0f, 0.5f, 0.46f, 1.0f);		//Which calls the Clear color function

	m_Camera->Render();

	//Get MVP matrix
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	worldMatrix = XMMatrixRotationY(rotation);

	//Render whichever model which we wamt to use ex: here triangle
	m_Model->Render(m_D3D->GetDeviceContext());

	//Add the shader on top of the model which is being used 
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture());
	//result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor(),m_Camera->GetPosition(),
		m_Light->GetSpecularColor(),m_Light->GetSpecularPower());
	
		
	
	if (!result)
	{
		return false;
	}

	m_D3D->EndScene();							  //Ends the rendering part and stuff



	return true;
}