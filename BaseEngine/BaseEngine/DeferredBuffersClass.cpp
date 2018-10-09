#include "stdafx.h"
#include "DeferredBuffersClass.h"


DeferredBuffersClass::DeferredBuffersClass()
{
	int i;
	for (i = 0; i < Buffer_Count; ++i)
	{
		m_renderTargetTextureArray[i] = 0;
		m_renderTargetViewArray[i] = 0;
		m_shaderResourceViewArray[i] = 0;
	}
	m_depthStencilBuffer = 0;
	m_depthStencilView = 0;
}

DeferredBuffersClass::DeferredBuffersClass(const DeferredBuffersClass &)
{
}


DeferredBuffersClass::~DeferredBuffersClass()
{
}

//Create the G-Buffer for the Deferred Shading
bool DeferredBuffersClass::Initialize(ID3D11Device* device, int textureWidth, int textureHeight, float screenDepth, float screenHeight)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT result;
	D3D11_RENDER_TARGET_VIEW_DESC   renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	int i;

	m_textureHeight = textureHeight;
	m_textureWidth = textureWidth;

	//====================================================================================
	//We create an array of 2D textures to which is used for diferred shader
	//====================================================================================

	//init texture desc
	ZeroMemory(&textureDesc, sizeof(textureDesc));

	textureDesc.Height = textureHeight;
	textureDesc.Width = textureWidth;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0; //D3D11_RESOURCE_MISC_GENERATE_MIPS


	
	for (i = 0; i < Buffer_Count; ++i)
	{
		result = device->CreateTexture2D(&textureDesc, NULL, &m_renderTargetTextureArray[i]);

		if (FAILED(result))
		{
			return false;
		}
	}

	//====================================================================================
	//We create render target views to access the render target textures
	//====================================================================================
	
	ZeroMemory(&renderTargetViewDesc, sizeof(renderTargetViewDesc));

	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;	//RTV->Render Target View
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	for (i = 0; i < Buffer_Count; ++i)
	{
		result = device->CreateRenderTargetView(m_renderTargetTextureArray[i], &renderTargetViewDesc, &m_renderTargetViewArray[i]);

		if (FAILED(result))
		{
			return false;
		}
	}

	//====================================================================================
	//We create shader resource views for shaders to access render target textures
	//====================================================================================

	ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));

	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;	//SRV->Shader Resource View
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	for (i = 0; i < Buffer_Count; ++i)
	{
		result = device->CreateShaderResourceView(m_renderTargetTextureArray[i], &shaderResourceViewDesc, &m_shaderResourceViewArray[i]);

		if (FAILED(result))
		{
			return false;
		}
	}

	//====================================================================================
	//Set up desc of the depthbuffer
	//====================================================================================


	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	depthBufferDesc.Height = textureHeight;
	depthBufferDesc.Width = textureWidth;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL ;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0; //D3D11_RESOURCE_MISC_GENERATE_MIPS

	
	result = device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);

	if (FAILED(result))
	{
		return false;
	}

	//====================================================================================
	//Set up the depth stencil view
	//====================================================================================

	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));


	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;	//DSV->Depth Stencil View
	depthStencilViewDesc.Texture2D.MipSlice = 0;


	result = device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);

	if (FAILED(result))
	{
		return false;
	}


	m_viewport.Width		= (float)textureWidth;
	m_viewport.Height		= (float)textureHeight;
	m_viewport.MinDepth		= 0.0f;
	m_viewport.MaxDepth		= 1.0F;
	m_viewport.TopLeftX		= 0.0F;
	m_viewport.TopLeftY		= 0.0F;
	


	return true;
}

void DeferredBuffersClass::ShutDown()
{
	int i;

	Safe_Release(m_depthStencilView);
	Safe_Release(m_depthStencilBuffer);
	for (i = 0; i < Buffer_Count; ++i)
	{
		if (m_shaderResourceViewArray[i])
		{
			m_shaderResourceViewArray[i]->Release();
			m_shaderResourceViewArray[i] = 0;
		}
		if (m_renderTargetViewArray[i])
		{
			m_renderTargetViewArray[i]->Release();
			m_renderTargetViewArray[i] = 0;
		}
		if (m_renderTargetTextureArray[i])
		{
			m_renderTargetTextureArray[i]->Release();
			m_renderTargetTextureArray[i] = 0;
		}
	}


}


void DeferredBuffersClass::SetRenderTargets(ID3D11DeviceContext *deviceContext)
{

	deviceContext->OMSetRenderTargets(Buffer_Count, m_renderTargetViewArray, m_depthStencilView);
	deviceContext->RSSetViewports(1, &m_viewport);

	return;

}

void DeferredBuffersClass::CleanRenderTargets(ID3D11DeviceContext *deviceContext, float red, float blue, float green, float alpha)
{
	float color[4];
	int i;

	color[0] = red;
	color[1] = blue;
	color[2] = green;
	color[3] = alpha;

	for (i = 0; i < Buffer_Count; ++i)
	{
		deviceContext->ClearRenderTargetView(m_renderTargetViewArray[i], color);
	}

	deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return;
}

ID3D11ShaderResourceView * DeferredBuffersClass::GetShaderResourceView(int view)
{
	return m_shaderResourceViewArray[view];
}
