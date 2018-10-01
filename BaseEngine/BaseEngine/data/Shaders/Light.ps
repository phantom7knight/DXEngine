
//#define LIGHTS_COUNT 4


Texture2D shaderTexture;
SamplerState SampleType;

/*cbuffer LightColorBuffer
{
	float4 diffuseColor[LIGHTS_COUNT];
};*/

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
	
	/*float3 lightPos1 : TEXCOORD2;
	float3 lightPos2 : TEXCOORD3;
	float3 lightPos3 : TEXCOORD4;
	float3 lightPos4 : TEXCOORD5;*/

};


float4 LightPixelShader(PixelInputType input) : SV_TARGET
{
	float4 texturecolor;
	float3 lightDir;
	float  lightintensity;
	float4 color;
	float3 reflection;
	float4 specular;
	//float lightIntensity1,lightIntensity2,lightIntensity3,lightIntensity4;
	//float4 color1,color2,color3,color4;

	texturecolor  = shaderTexture.Sample(SampleType,input.tex);
	specular = float4(0.0f,0.0f,0.0f,0.0f);

	color = ambientColor;

	lightDir = -lightDirection;

	//Ambient Lighting
	lightintensity = saturate(dot(input.normal,lightDir));

	/*lightintensity1 = saturate(dot(input.normal,input.lightPos1));
	lightintensity2 = saturate(dot(input.normal,input.lightPos2));
	lightintensity3 = saturate(dot(input.normal,input.lightPos3));
	lightintensity4 = saturate(dot(input.normal,input.lightPos4));*/
	
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