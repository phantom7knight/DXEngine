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
	m_DeferredShader = 0;
	m_DeferredBuffer = 0;
	m_ScreenQuad = 0;
	m_ScreenQuadShader = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{

}

GraphicsClass::~GraphicsClass()
{

}

void GraphicsClass::Update()
{
	m_Camera->SetPosition(Camera_PosX, Camera_PosY, Camera_PosZ);
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd, XMFLOAT3 LightPos)
{
	bool result;

	Camera_PosX = 0.0f;
	Camera_PosY = 0.0f;
	Camera_PosZ = -5.0f;

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

	m_Camera->SetPosition(Camera_PosX, Camera_PosY, Camera_PosZ);
	m_Camera->Render();
	m_Camera->RenderBaseViewMatrix();

	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	result = m_Model->Initialize(m_D3D->GetDevice(), (WCHAR*)L"../BaseEngine/data/rock.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object", L"Error", MB_OK);
		return false;
	}
	
#ifdef DEFERRED_RENDERING
	
	m_ScreenQuad = new ScreenQuad;
	if (!m_ScreenQuad)
		return false;
	//Result_Check(!m_ScreenQuad);
	
	result = m_ScreenQuad->Initialize(m_D3D->GetDevice(),screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Screen Quad object", L"Error", MB_OK);
		return false;
	}

	m_DeferredBuffer = new DeferredBuffersClass();
	
	if (!m_DeferredBuffer)
		return false;


	result = m_DeferredBuffer->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Deferred Buffers", L"Error", MB_OK);
		return false;
	}


	m_DeferredShader = new DeferredShaderClass();

	if (!m_DeferredBuffer)
		return false;


	result = m_DeferredShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Deferred Shader Object", L"Error", MB_OK);
		return false;
	}


#endif // DEFERRED_RENDERING




	/*m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Texture shader object.", L"Error", MB_OK);
		return false;
	}*/

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
	m_Light->SetDiffuseColor(1.0f, 0.0f, 1.0f, 1.0f);
	//m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetLightPosition(LightPos.x, LightPos.y, LightPos.z);
	m_Light->SetAmbientColor(1.0f, 1.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(0.22f, 0.021f, 0.23F, 1.0f);
	m_Light->SetSpecularPower(32.0f);
	
	//ImguiManager::getInstance()->Init(hwnd, m_D3D->GetDevice(), m_D3D->GetDeviceContext());



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

	if (m_DeferredBuffer)
	{
		m_DeferredBuffer->ShutDown();
		delete m_DeferredBuffer;
		m_DeferredBuffer = 0;
	}

	if (m_DeferredShader)
	{
		m_DeferredShader->Shutdown();
		delete m_DeferredShader;
		m_DeferredShader = 0;
	}

	/*if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}*/
	
	if (m_ScreenQuad)
	{
		m_ScreenQuad->ShutDown();
		delete m_ScreenQuad;
		m_ScreenQuad = 0;
	}

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
	bool result = false;
	static float rotation = 0.0f;

	rotation += (float)PI_ *0.0051f;

	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	

/*#pragma region CamerControls
	if (m_Input->IsKeyDown(VK_UP))
	{
		Camera_PosY += 0.1f;
	}
	if (m_Input->IsKeyDown(VK_DOWN))
	{
		Camera_PosY -= 0.1f;
	}
	if (m_Input->IsKeyDown(VK_LEFT))
	{
		Camera_PosX -= 0.1f;
	}
	if (m_Input->IsKeyDown(VK_RIGHT))
	{
		Camera_PosX += 0.1f;
	}

	//Reset the Camera Position
	if (m_Input->IsKeyDown(VK_SPACE))
	{
		Camera_PosX = 0.0f;
		Camera_PosY = 0.0f;
		Camera_PosZ = -5.0f;
	}
#pragma endregion*/

	
	

#ifdef DEFERRED_RENDERING
	
	result = DeferredRender(rotation);

#endif // DEFERRED_RENDERING


#ifdef FWD_RENDERDING
	
	result = Render(rotation);

#endif // FWD_RENDERING


	if (!result)
	{
		return false;
	}
	return true;
}

#ifdef DEFERRED_RENDERING

bool GraphicsClass::FirstPass(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	//Set the render buffers to be the render targets
	m_DeferredBuffer->SetRenderTargets(m_D3D->GetDeviceContext());

	//clear render buffers
	m_DeferredBuffer->CleanRenderTargets(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);


	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	//worldMatrix = XMMatrixRotationY(rotation);	//same as model matrix

	m_Model->Render(m_D3D->GetDeviceContext());

	//Check this
	m_DeferredShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
					 m_Model->GetTexture(), m_Light->GetLightPosition(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor(),
					 m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());


	m_D3D->SetBackBufferRenderTarget();

	m_D3D->ResetViewPort();

	return true;
}

bool GraphicsClass::DeferredRender(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	//Obtain G-Buffer Pass or First Pass

	result = FirstPass(rotation);
	if (!result) 
		return false;
	

	//Clear the Screen
	m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);		//Which calls the Clear color function

	//Call the 2nd Render Texture


	m_Camera->Render();

	//Get MVP matrix
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetBaseViewMatrix(viewMatrix);
	m_D3D->GetOrthoMatrix(projectionMatrix);

	//Depth Testing Off
	m_D3D->TurnZBufferOff();
	
	//For Rotation
	//worldMatrix = XMMatrixRotationY(rotation);


	m_ScreenQuad->Render(m_D3D->GetDeviceContext());

	//Render whichever model which we wamt to use ex: here triangle
	//m_Model->Render(m_D3D->GetDeviceContext());

	 m_LightShader->Render(m_D3D->GetDeviceContext(), m_ScreenQuad->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_DeferredBuffer->GetShaderResourceView(0), m_Light->GetLightPosition(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),m_DeferredBuffer->GetShaderResourceView(1),m_DeferredBuffer->GetShaderResourceView(2));

	/*if (!result)
		return false;*/

	/*Result_Check(!result);
	/*Add the shader on top of the model which is being used 
	/*result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture());
	/*result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	
	/*result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor(),m_Camera->GetPosition(),
		m_Light->GetSpecularColor(),m_Light->GetSpecularPower());*/
	
		
	m_D3D->TurnZBufferOn();
	
	m_D3D->EndScene();							  //Ends the rendering part and stuff



	return true;
}


#endif // DEFERRED_RENDERING



#ifdef FWD_RENDERDING

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

	//Result_Check(!result);
	//Add the shader on top of the model which is being used 
	
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture());
	//result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);

	result = m_LightShader->FWD_Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor(),m_Camera->GetPosition(),
		m_Light->GetSpecularColor(),m_Light->GetSpecularPower());


	m_D3D->EndScene();							  //Ends the rendering part and stuff



	return true;
}

#endif // FWD_RENDERING
