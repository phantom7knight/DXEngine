#pragma once
class ScreenQuad
{

private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

	
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	
	bool InitializeBuffers(ID3D11Device*, int, int);
	void ShutDownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	

public:
	ScreenQuad();
	ScreenQuad(const ScreenQuad&);
	~ScreenQuad();

	bool Initialize(ID3D11Device*, int, int);
	void ShutDown();
	void Render(ID3D11DeviceContext*);
	int  GetIndexCount();

};

