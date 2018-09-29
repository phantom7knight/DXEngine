#pragma once

#define Buffer_Count 2

class DeferredBuffersClass
{
public:
	DeferredBuffersClass();
	DeferredBuffersClass(const DeferredBuffersClass&);
	~DeferredBuffersClass();

	bool Initialize(ID3D11Device*, int, int, float, float);
	void ShutDown();


	void SetRenderTargets(ID3D11DeviceContext*);
	void CleanRenderTargets(ID3D11DeviceContext*, float, float, float, float);

	ID3D11ShaderResourceView* GetShaderResourceView(int);

private:

	int m_textureWidth, m_textureHeight;

	ID3D11Texture2D*			m_renderTargetTextureArray[Buffer_Count];
	ID3D11RenderTargetView*		m_renderTargetViewArray[Buffer_Count];
	ID3D11ShaderResourceView*	m_shaderResourceViewArray[Buffer_Count];
	ID3D11Texture2D*			m_depthStencilBuffer;
	ID3D11DepthStencilView*		m_depthStencilView;
	D3D11_VIEWPORT				m_viewport;

};

