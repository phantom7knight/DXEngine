#pragma once



const int LIGHTS_COUNT = 4;


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
//#ifdef FWD_RENDERDING

	struct LightBufferType
	{

			XMFLOAT4 ambientColor;
			XMFLOAT4 diffuseColor;
			XMFLOAT3 lightDirection;
			float	 specularPower;
			XMFLOAT4 specularColor;
		
	};

//#endif // FWD_RENDERDING



//#ifdef DEFERRED_RENDERING
//
//	struct LightBufferType
//	{
//		XMFLOAT3 lightDirection;
//		float padding;
//	};
//
//#endif // DEFERRED_RENDERING



	//Point Light
	/*struct LightColorBufferType
	{
		XMFLOAT4 diffusecolor[LIGHTS_COUNT];
	};
	
	struct LightPositionBufferType
	{
		XMFLOAT4 lightPosition[LIGHTS_COUNT];
	};*/




public:
	LightShaderClass();
	LightShaderClass(const LightShaderClass&);
	~LightShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*,
				XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor, XMFLOAT4 ambientColor,
				XMFLOAT3 cameraPostion,XMFLOAT4 specularColor,float specularPower,
				ID3D11ShaderResourceView* normaltexture);

	bool FWD_Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture,
				XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor, XMFLOAT4 ambientColor,
				XMFLOAT3 cameraPostion, XMFLOAT4 specularColor, float specularPower);


private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT3 lightDirection, 
					XMFLOAT4 diffuseColor,XMFLOAT4 ambientColor, XMFLOAT3 cameraPostion, XMFLOAT4 specularColor, float specularPower,
					ID3D11ShaderResourceView* normaltexture);
	void RenderShader(ID3D11DeviceContext*, int);

	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;

	ID3D11Buffer*		   m_lightbuffer;
	ID3D11Buffer*		   m_camerabuffer;
	ID3D11SamplerState*    m_sampleState;

	//ID3D11Buffer* m_lightColorBuffer;
	//ID3D11Buffer* m_lightPositionBuffer;


};



