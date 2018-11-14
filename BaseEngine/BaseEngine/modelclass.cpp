
#include "stdafx.h"
#include "modelclass.h"






ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;

	m_Texture = 0;
}

ModelClass::ModelClass(const ModelClass& other)
{

}

ModelClass::~ModelClass()
{

}

bool ModelClass::Initialize(ID3D11Device* device, WCHAR* textureFilename)
{
	bool result;

	result = InitializeBuffer(device);
	if (!result)
	{
		return false;
	}

	result = LoadTexture(device,textureFilename);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::Shutdown()
{
	ReleaseTexture();

	ShutdownBuffer();
	return;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	RenderBuffers(deviceContext);
	return;
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_Texture->GetTextureView();
}


bool ModelClass::InitializeBuffer(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC		vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA  vertexData, indexData;
	HRESULT  result;

	m_vertexCount = 36;
					
	m_indexCount  = 36;

	vertices = new VertexType[m_vertexCount];

	if (!vertices)
	{
		return false;
	}

	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

#pragma region All the vertex&index data
	//To draw a quad without the texture
	/*//vertices[0].position = XMFLOAT3(-1.0ff, -1.0ff, 0.0f);  // Bottom left.
	//vertices[0].color = XMFLOAT4(1.0ff, 0.0f, 0.0f, 1.0ff);

	//vertices[1].position = XMFLOAT3(-1.0ff, 1.0ff, 0.0f);  // Top left.
	//vertices[1].color = XMFLOAT4(1.0ff, 0.0f, 0.0f, 1.0ff);

	//vertices[2].position = XMFLOAT3(1.0ff, 1.0ff, 0.0f);  // top right.
	//vertices[2].color = XMFLOAT4(1.0ff, 0.0f, 0.0f, 1.0ff);

	//vertices[3].position = XMFLOAT3(1.0ff, -1.0ff, 0.0f);  // Bottom right.
	//vertices[3].color = XMFLOAT4(1.0ff, 0.0f, 0.0f, 1.0ff);

	//// Load the index array with data.
	//indices[0] = 0;  // Bottom left.
	//indices[1] = 1;  // Top left.
	//indices[2] = 2;  // top right.

	//indices[3] = 0;  // Bottom left.
	//indices[4] = 2;  // Top right.
	//indices[5] = 3;  // Bottom right.*/

	/*vertices[0].position = XMFLOAT3(-1.0ff, -1.0ff, 0.0f);  // Bottom left.
	vertices[0].texture = XMFLOAT2(0.0f, 1.0ff);
	vertices[0].normal = XMFLOAT3(0.0f, 0.0f, -1.0ff);

	vertices[1].position = XMFLOAT3(0.0f, 1.0ff, 0.0f);  // Top middle.
	vertices[1].texture = XMFLOAT2(0.5f, 0.0f);
	vertices[1].normal = XMFLOAT3(0.0f, 0.0f, -1.0ff);

	vertices[2].position = XMFLOAT3(1.0ff, -1.0ff, 0.0f);  // Bottom right.
	vertices[2].texture = XMFLOAT2(1.0ff, 1.0ff);
	vertices[2].normal = XMFLOAT3(0.0f, 0.0f, -1.0ff);*/

	/*{ XMFLOAT3(-1.0ff, -1.0ff, -1.0ff), XMFLOAT2(0.0f, 1.0ff) ,XMFLOAT3(0.0f, 0.0f, -1.0ff)  },  // 0
	{ XMFLOAT3(-1.0ff,  1.0ff, -1.0ff), XMFLOAT2(0.0f, 1.0ff) ,XMFLOAT3(0.0f, 0.0f, -1.0ff)  },  // 1
	{ XMFLOAT3(1.0ff,  1.0ff, -1.0ff) , XMFLOAT2(0.0f, 1.0ff) ,XMFLOAT3(0.0f, 0.0f, -1.0ff)  },   // 2
	{ XMFLOAT3(1.0ff, -1.0ff, -1.0ff) , XMFLOAT2(0.0f, 1.0ff) ,XMFLOAT3(0.0f, 0.0f, -1.0ff)  },   // 3
	{ XMFLOAT3(-1.0ff, -1.0ff,  1.0ff), XMFLOAT2(0.0f, 1.0ff) ,XMFLOAT3(0.0f, 0.0f,  1.0ff)  },  // 4
	{ XMFLOAT3(-1.0ff,  1.0ff,  1.0ff), XMFLOAT2(0.0f, 1.0ff) ,XMFLOAT3(0.0f, 0.0f,  1.0ff)  },  // 5
	{ XMFLOAT3(1.0ff,  1.0ff,  1.0ff) , XMFLOAT2(0.0f, 1.0ff) ,XMFLOAT3(0.0f, 0.0f,  1.0ff)  },   // 6
	{ XMFLOAT3(1.0ff, -1.0ff,  1.0ff) , XMFLOAT2(0.0f, 1.0ff) ,XMFLOAT3(0.0f, 0.0f,  1.0ff)  }  */  // 7

#pragma endregion


#pragma region Vertex Positions
	VertexType vVertices[36] =
	{	//Position						 // UV co-ordinates						//Normals	
								  	     
		{ XMFLOAT3(-0.5f,  0.5f, -0.5f),    XMFLOAT2(  0.0f , -1.0f  ),	       XMFLOAT3(0.0, 0.0,1.0) },
		{ XMFLOAT3(0.5f,  0.5f , -0.5f),     XMFLOAT2(0.0f , -1.0f),		   XMFLOAT3(0.0, 0.0,1.0) },
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f),     XMFLOAT2(0.0f ,  -1.0f),		   XMFLOAT3(0.0, 0.0,1.0) },
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f),     XMFLOAT2(0.0f ,  -1.0f),		   XMFLOAT3(0.0, 0.0,1.0) },
		{ XMFLOAT3(0.5f,  0.5f , -0.5f),     XMFLOAT2(0.0f , -1.0f),		   XMFLOAT3(0.0, 0.0,1.0) },
		{ XMFLOAT3(0.5f, -0.5f, -0.5f),      XMFLOAT2(0.0f ,  -1.0f),		   XMFLOAT3(0.0, 0.0,1.0) },
		{ XMFLOAT3(0.5f,  0.5f , -0.5f),     XMFLOAT2(0.0f ,  0.0f),		   XMFLOAT3(1.0, 0.0, 0.0) },
		{ XMFLOAT3(0.5f,  0.5f ,  0.5f),     XMFLOAT2(0.0f ,  0.0f),		   XMFLOAT3(1.0, 0.0, 0.0) },
		{ XMFLOAT3(0.5f, -0.5f, -0.5f),      XMFLOAT2(0.0f ,  0.0f),		   XMFLOAT3(1.0, 0.0, 0.0) },
		{ XMFLOAT3(0.5f, -0.5f, -0.5f),      XMFLOAT2(0.0f ,  0.0f),		   XMFLOAT3(1.0, 0.0, 0.0) },
		{ XMFLOAT3(0.5f,  0.5f ,  0.5f),     XMFLOAT2(0.0f ,  0.0f),		   XMFLOAT3(1.0, 0.0, 0.0) },
		{ XMFLOAT3(0.5f, -0.5f,  0.5f),      XMFLOAT2(0.0f ,  0.0f),		   XMFLOAT3(1.0, 0.0, 0.0) },
		{ XMFLOAT3(0.5f,  0.5f ,  0.5f),      XMFLOAT2(0.0f ,  1.0f),		   XMFLOAT3(0.0, 0.0,-1.0) },
		{ XMFLOAT3(-0.5f,  0.5f ,  0.5f),      XMFLOAT2(0.0f ,  1.0f),		   XMFLOAT3(0.0, 0.0,-1.0) },
		{ XMFLOAT3(0.5f, -0.5f,  0.5f),     XMFLOAT2(0.0f ,  1.0f),		       XMFLOAT3(0.0, 0.0,-1.0) },
		{ XMFLOAT3(0.5f, -0.5f,  0.5f),     XMFLOAT2(0.0f ,  1.0f),		       XMFLOAT3(0.0, 0.0,-1.0) },
		{ XMFLOAT3(-0.5f,  0.5f ,  0.5f),     XMFLOAT2(0.0f ,  1.0f),		   XMFLOAT3(0.0, 0.0,-1.0) },
		{ XMFLOAT3(-0.5f, -0.5f,  0.5f),     XMFLOAT2(0.0f ,  1.0f),		   XMFLOAT3(0.0, 0.0,-1.0) },
		{ XMFLOAT3(-0.5f,  0.5f ,  0.5f),     XMFLOAT2(0.0f ,  0.0f),		   XMFLOAT3(-1.0, 0.0, 0.0)},
		{ XMFLOAT3(-0.5f,  0.5f , -0.5f),     XMFLOAT2(0.0f ,  0.0f),		   XMFLOAT3(-1.0, 0.0, 0.0)},
		{ XMFLOAT3(-0.5f, -0.5f,  0.5f),     XMFLOAT2(0.0f ,  0.0f),		   XMFLOAT3(-1.0, 0.0, 0.0)},
		{ XMFLOAT3(-0.5f, -0.5f,  0.5f),     XMFLOAT2(0.0f ,  0.0f),		   XMFLOAT3(-1.0, 0.0, 0.0)},
		{ XMFLOAT3(-0.5f,  0.5f , -0.5f),     XMFLOAT2(0.0f ,  0.0f),		   XMFLOAT3(-1.0, 0.0, 0.0)},
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f),     XMFLOAT2(0.0f ,  0.0f),		   XMFLOAT3(-1.0, 0.0, 0.0)},
		{ XMFLOAT3(-0.5f,  0.5f ,  0.5f),     XMFLOAT2(1.0f ,  0.0f),		   XMFLOAT3(0.0, 1.0, 0.0) },
		{ XMFLOAT3(0.5f,  0.5f ,  0.5f),     XMFLOAT2(1.0f ,  0.0f),		   XMFLOAT3(0.0, 1.0, 0.0) },
		{ XMFLOAT3(-0.5f,  0.5f , -0.5f),     XMFLOAT2(1.0f ,  0.0f),		   XMFLOAT3(0.0, 1.0, 0.0) },
		{ XMFLOAT3(-0.5f,  0.5f , -0.5f),     XMFLOAT2(1.0f ,  0.0f),		   XMFLOAT3(0.0, 1.0, 0.0) },
		{ XMFLOAT3(0.5f,  0.5f ,  0.5f),     XMFLOAT2(1.0f ,  0.0f),		   XMFLOAT3(0.0, 1.0, 0.0) },
		{ XMFLOAT3(0.5f,  0.5f , -0.5f),     XMFLOAT2(1.0f ,  0.0f),		   XMFLOAT3(0.0, 1.0, 0.0) },
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f),     XMFLOAT2(-1.0f ,  0.0f),		   XMFLOAT3(0.0,-1.0, 0.0) },
		{ XMFLOAT3(0.5f, -0.5f, -0.5f),     XMFLOAT2(-1.0f ,  0.0f),		   XMFLOAT3(0.0,-1.0, 0.0) },
		{ XMFLOAT3(-0.5f, -0.5f,  0.5f),     XMFLOAT2(-1.0f ,  0.0f),	       XMFLOAT3(0.0,-1.0, 0.0) },
		{ XMFLOAT3(-0.5f, -0.5f,  0.5f),     XMFLOAT2(-1.0f ,  0.0f),	       XMFLOAT3(0.0,-1.0, 0.0) },
		{ XMFLOAT3(0.5f, -0.5f, -0.5f),     XMFLOAT2(-1.0f ,  0.0f),		   XMFLOAT3(0.0,-1.0, 0.0) },
		{ XMFLOAT3(0.5f, -0.5f,  0.5f),     XMFLOAT2(-1.0f ,  0.0f)	,	       XMFLOAT3(0.0,-1.0, 0.0) }
															 		  
		 


	};

#pragma endregion


#pragma region Index
	for (int i = 0; i < 36; ++i)
	{
		indices[i] = i;
	}
#pragma endregion


	//========================================================================
	// Vertex Buffer setting
	//========================================================================

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * _countof(vVertices);	//m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vVertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//========================================================================
	// Index Buffer setting
	//========================================================================


	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * (m_indexCount);
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void ModelClass::ShutdownBuffer()
{
	Safe_Release(m_indexBuffer);
	Safe_Release(m_vertexBuffer);

	return;
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	//=============================================================================
	//This is how binding the buffers is done
	//=============================================================================

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;

}


bool ModelClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;


	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	result = m_Texture->Initialize(device, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::ReleaseTexture()
{
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}


