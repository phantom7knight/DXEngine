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

	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;


	return true;
}

void DeferredBuffersClass::ShutDown()
{
}

void DeferredBuffersClass::SetRenderTargets(ID3D11DeviceContext *)
{
}

void DeferredBuffersClass::CleanRenderTargets(ID3D11DeviceContext *, float, float, float, float)
{
}

ID3D11ShaderResourceView * DeferredBuffersClass::GetShaderResourceView(int)
{
	return nullptr;
}
