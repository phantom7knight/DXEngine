#include "stdafx.h"
//#include "LightShaderClass.h"





LightShaderClass::LightShaderClass()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
	m_sampleState = 0;
	m_lightbuffer = 0;
	m_camerabuffer = 0;

}

LightShaderClass::LightShaderClass(const LightShaderClass& other)
{
}


LightShaderClass::~LightShaderClass()
{
}


bool LightShaderClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

#ifdef DEFERRED_RENDERING
	
	result = InitializeShader(device, hwnd, (WCHAR*)L"../BaseEngine/data/Shaders/DeferredLightVS.hlsl", (WCHAR*)L"../BaseEngine/data/Shaders/DeferredLightPS.hlsl");

#endif // DEFERRED_RENDERING

#ifdef FWD_RENDERDING
	
	result = InitializeShader(device, hwnd, (WCHAR*)L"../BaseEngine/data/Shaders/SpecularLightVS.hlsl", (WCHAR*)L"../BaseEngine/data/Shaders/SpecularLightPS.hlsl");
	//result = InitializeShader(device, hwnd, (WCHAR*)L"../BaseEngine/data/Shaders/LightVS.hlsl", (WCHAR*)L"../BaseEngine/data/Shaders/LightPS.hlsl");

#endif // FWD_RENDERDING



	if (!result)
	{
		return false;
	}
	return true;
}

void LightShaderClass::Shutdown()
{
	ShutdownShader();
	return;
}


bool LightShaderClass::FWD_Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture,
	XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor, XMFLOAT4 ambientColor,
	XMFLOAT3 cameraPostion, XMFLOAT4 specularColor, float specularPower)
{


	bool result;

	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, texture,
		lightDirection, diffuseColor, ambientColor, cameraPostion, specularColor, specularPower,NULL,NULL);

	if (!result)
	{
		return false;
	}

	RenderShader(deviceContext, indexCount);
	return true;



	return true;
}







bool LightShaderClass::Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture,
	XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor, XMFLOAT4 ambientColor,
	XMFLOAT3 cameraPostion, XMFLOAT4 specularColor, float specularPower,
	ID3D11ShaderResourceView* normaltexture, ID3D11ShaderResourceView* colortexture)
{
	bool result;

	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, texture,
		lightDirection, diffuseColor, ambientColor, cameraPostion, specularColor, specularPower, normaltexture, colortexture);

	if (!result)
	{
		return false;
	}

	RenderShader(deviceContext, indexCount);
	return true;
}

bool LightShaderClass::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
#ifdef DEFERRED_RENDERING

	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];

#endif // DEFERRED_RENDERING


#ifdef FWD_RENDERDING

	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];

#endif // FWD_RENDERING

	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC cameraBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_BUFFER_DESC lightBufferDesc;

	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	result = D3DCompileFromFile(vsFilename, NULL, NULL, "LightVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_DEBUG, 0, &vertexShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		else
		{
			MessageBox(hwnd, vsFilename, L"Missing Deferred Light Vertex Shader File", MB_OK);
		}
		return false;
	}

	result = D3DCompileFromFile(psFilename, NULL, NULL, "LightPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_DEBUG, 0, &pixelShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		else
		{
			MessageBox(hwnd, psFilename, L"Missing Deferred Light Pixel Shader File", MB_OK);
		}
		return false;
	}

	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}

	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(result))
	{
		return false;
	}


	//============================================================
	//Input Layout
	//============================================================
	

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

//#ifdef FWD_RENDERDING

	polygonLayout[2].SemanticName = "NORMAL";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

//#endif // FWD_RENDERDING


	
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout);

	if (FAILED(result))
	{
		return false;
	}

	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;


	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if (FAILED(result))
	{
		return false;
	}

	//============================================================
	//Matrices Constant Buffer
	//============================================================

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//============================================================
	//Camera Constant Buffer
	//============================================================

//#ifdef FWD_RENDERDING

	cameraBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cameraBufferDesc.ByteWidth = sizeof(CameraBufferType);
	cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cameraBufferDesc.MiscFlags = 0;
	cameraBufferDesc.StructureByteStride = 0;


	result = device->CreateBuffer(&cameraBufferDesc, NULL, &m_camerabuffer);
	if (FAILED(result))
	{
		return false;
	}

//#endif // FWD_RENDERDING

	
	//============================================================
	//Light Constant Buffer
	//============================================================

	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(LightBufferType);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;


	result = device->CreateBuffer(&lightBufferDesc, NULL, &m_lightbuffer);
	if (FAILED(result))
	{
		return false;
	}



	return true;
}

void LightShaderClass::ShutdownShader()
{
	Safe_Release(m_lightbuffer);
	Safe_Release(m_sampleState);
	Safe_Release(m_matrixBuffer);
	Safe_Release(m_layout);
	Safe_Release(m_pixelShader);
	Safe_Release(m_vertexShader);

//#ifdef FWD_RENDERDING

	Safe_Release(m_camerabuffer);

//#endif // DEFERRED_RENDERING



	return;
}

void LightShaderClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long  bufferSize, i;
	ofstream fout;

	compileErrors = (char*)(errorMessage->GetBufferPointer());

	bufferSize = errorMessage->GetBufferSize();

	fout.open("shader-error.txt");

	for (i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	fout.close();

	errorMessage->Release();
	errorMessage = 0;

	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}

bool LightShaderClass::SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture,
								XMFLOAT3 lightPosition, XMFLOAT4 diffuseColor, XMFLOAT4 ambientColor,
								XMFLOAT3 cameraPostion, XMFLOAT4 specularColor, float specularPower,
								ID3D11ShaderResourceView* normaltexture,ID3D11ShaderResourceView* colortexture)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	LightBufferType* lightPtr;
	CameraBufferType* cameraptr;
	unsigned int bufferNumber;

	worldMatrix			= XMMatrixTranspose(worldMatrix);
	viewMatrix			= XMMatrixTranspose(viewMatrix);
	projectionMatrix	= XMMatrixTranspose(projectionMatrix);

	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	dataPtr = (MatrixBufferType*)mappedResource.pData;

	dataPtr->world			= worldMatrix;
	dataPtr->view			= viewMatrix;
	dataPtr->projection		= projectionMatrix;

	deviceContext->Unmap(m_matrixBuffer, 0);

	bufferNumber = 0;

	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);
	deviceContext->PSSetShaderResources(0, 1, &texture);		//color texture

//#ifdef DEFERRED_RENDERING

	deviceContext->PSSetShaderResources(1, 1, &normaltexture);	//normal texture
	deviceContext->PSSetShaderResources(2, 1, &colortexture);	//position texture
	//deviceContext->PSSetShaderResources(3, 1, &speculartexture);	//specular texture

//#endif // DEFERRED_RENDERING


		
//#ifdef FWD_RENDERDING

	result = deviceContext->Map(m_camerabuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	cameraptr = (CameraBufferType*)mappedResource.pData;

	cameraptr->cameraPostion = cameraPostion;
	cameraptr->padding = 0.0f;
	

	deviceContext->Unmap(m_camerabuffer, 0);

	bufferNumber = 1;

	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_camerabuffer);

//#endif // FWD_RENDERDING




	result = deviceContext->Map(m_lightbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	lightPtr = (LightBufferType*)mappedResource.pData;

//#ifdef FWD_RENDERDING

	lightPtr->ambientColor		= ambientColor;
	lightPtr->diffuseColor		= diffuseColor;
	lightPtr->specularColor		= specularColor;
	lightPtr->specularPower		= specularPower;

//#endif // FWD_RENDERDING

	lightPtr->lightPosition = lightPosition;
	
	deviceContext->Unmap(m_lightbuffer, 0);

	bufferNumber = 0;

	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_lightbuffer);


	return true;
}

void LightShaderClass::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	deviceContext->IASetInputLayout(m_layout);

	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	deviceContext->PSSetSamplers(0, 1, &m_sampleState);

	deviceContext->DrawIndexed(indexCount, 0, 0);
	return;
}
