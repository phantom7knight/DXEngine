Texture2D shaderTexture;
SamplerState SampleType;

cbuffer LightBuffer
{
	float4 ambientColor;
	float4 diffuseColor;
	float3 lightDirection;
	float specularPower;
	float4 specularColor;
	
};

//Input Layout
struct PixelInputType
{
	
	float4 position : SV_POSITION;
	float2 tex		: TEXCOORD0;
	float3 normal	: NORMAL;
	float3 viewDirection : TEXCOORD1;

};


float4 LightPixelShader(PixelInputType input) : SV_TARGET
{
	float4 texturecolor;
	float3 lightDir;
	float  lightintensity;
	float4 color;
	float3 reflection;
	float4 specular;


	texturecolor  = shaderTexture.Sample(SampleType,input.tex);
	specular = float4(0.0f,0.0f,0.0f,0.0f);

	color = ambientColor;

	lightDir = -lightDirection;

	//Ambient Lighting
	lightintensity = saturate(dot(input.normal,lightDir));
	
	//color = saturate(diffuseColor * lightintensity);

	if(lightintensity > 0.0f)
	{
		color += (diffuseColor * lightintensity);
		color = saturate(color);

		reflection = normalize(2* lightintensity * input.normal - lightDir);
		specular = pow(saturate(dot(reflection , input.viewDirection)),specularPower);
	}

	//color = color * texturecolor;
	color = saturate(color + specular);

	return color;
}