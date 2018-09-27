#pragma once
class LightShaderClass
{

	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct CameraBufferType
	{
		XMFLOAT3 cameraPostion;
		float    padding;

	};

	struct LightBufferType
	{
		XMFLOAT4 ambientColor;
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightDirection;
		float	 specularPower;
		XMFLOAT4 specularColor;
		
		//float padding;
	};

public:
	LightShaderClass();
	LightShaderClass(const LightShaderClass&);
	~LightShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*,
			XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor, XMFLOAT4 ambientColor,
				XMFLOAT3 cameraPostion,XMFLOAT4 specularColor,float specularPower);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT3 lightDirection, 
					XMFLOAT4 diffuseColor,XMFLOAT4 ambientColor, XMFLOAT3 cameraPostion, XMFLOAT4 specularColor, float specularPower);
	void RenderShader(ID3D11DeviceContext*, int);

	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;

	ID3D11Buffer* m_lightbuffer;
	ID3D11Buffer* m_camerabuffer;
	ID3D11SamplerState* m_sampleState;

};



