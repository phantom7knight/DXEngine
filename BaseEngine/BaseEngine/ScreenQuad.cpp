#include "stdafx.h"
#include "ScreenQuad.h"




ScreenQuad::ScreenQuad()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

ScreenQuad::ScreenQuad(const ScreenQuad &)
{
}


ScreenQuad::~ScreenQuad()
{
}



bool ScreenQuad::InitializeBuffers(ID3D11Device *device, int quadwidth, int quadheight)
{
	float left, right, top, bottom;
	VertexType* VertexCB;
	unsigned long* indeces;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

	left = (float)((quadwidth / 2) * -1);
	
	right =  left + quadwidth;

	top = (float)((quadheight / 2));

	bottom = top - (float)quadheight;

	m_vertexCount = 6;
	m_indexCount = m_vertexCount;

	VertexCB = new VertexType[m_vertexCount];

	if (!VertexCB)
		return false;

	//Result_Check(!VertexCB);

	indeces = new unsigned long[m_indexCount];

	if (!indeces)
		return false;

	//Result_Check(!indeces);


	#pragma region ScreenQuadParamerters
	//First Triangle
	VertexCB[0].position = XMFLOAT3(left, top, 0.0f);
	VertexCB[0].texture = XMFLOAT2(0.0f, 0.0f);

	VertexCB[1].position = XMFLOAT3(right, bottom, 0.0f);
	VertexCB[1].texture = XMFLOAT2(1.0f, 1.0f);

	VertexCB[2].position = XMFLOAT3(left, bottom, 0.0f);
	VertexCB[2].texture = XMFLOAT2(0.0f, 1.0f);
	
	//Second Triangle
	VertexCB[3].position = XMFLOAT3(left, top, 0.0f);
	VertexCB[3].texture = XMFLOAT2(0.0f, 0.0f);

	VertexCB[4].position = XMFLOAT3(right, top, 0.0f);
	VertexCB[4].texture = XMFLOAT2(1.0f, 0.0f);

	VertexCB[5].position = XMFLOAT3(right, bottom, 0.0f);
	VertexCB[5].texture = XMFLOAT2(1.0f, 1.0f);

	for (int i = 0; i < m_indexCount; ++i)
	{
		indeces[i] = i;
	}

	#pragma endregion

	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	vertexData.pSysMem = VertexCB;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	//Result_Check(!result);
	if (FAILED(result)) 
		return false;

	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	indexData.pSysMem = VertexCB;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	//Result_Check(!result);
	if (FAILED(result))
		return false;


	delete [] VertexCB;
	VertexCB = 0;

	delete [] indeces;
	indeces = 0;

	return true;

}

void ScreenQuad::ShutDownBuffers()
{
	Safe_Release(m_indexBuffer);
	Safe_Release(m_vertexBuffer);
}

void ScreenQuad::RenderBuffers(ID3D11DeviceContext *deviceContext)
{

	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}


bool ScreenQuad::Initialize(ID3D11Device *device, int screenWidth, int screenHeight)
{

	bool result;
	result = InitializeBuffers(device, screenWidth, screenHeight);

	if (!result)
		return false;

	
	return true;
}

void ScreenQuad::ShutDown()
{
	ShutDownBuffers();
}

void ScreenQuad::Render(ID3D11DeviceContext *deviceContext)
{
	RenderBuffers(deviceContext);
}

int ScreenQuad::GetIndexCount()
{
	return m_indexCount;
}
