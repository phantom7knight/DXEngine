
//#include "ShaderStructDefs.h"

//============================================
//Textures
//============================================

Texture2D shaderTexture : register(t0);	//Color texture
Texture2D normalTexture : register(t1);


//============================================
//Sample State
//============================================

SamplerState SampleType : register(s0);


//============================================
//Light Constant Buffer
//============================================
cbuffer LightBuffer
{
	//float4 ambientColor;
	//float4 diffuseColor;
	float3 lightDirection;
	float padding;
	//float specularPower;
	//float4 specularColor;

};

//============================================
//Typedef
//============================================

struct PixelInputType
{
	
	float4 position		 : SV_POSITION;
	float2 tex			 : TEXCOORD0;
	//float3 normal		 : NORMAL;
	//float3 viewDirection : TEXCOORD1;
	
};



struct PixelOutputType
{
	float4 color  : SV_Target0;
	float4 normal : SV_Target1;

};


float4 LightPixelShader(PixelInputType input) : SV_TARGET
{
	
	//float4 texturecolor;
	float3 lightDir;
	float  lightIntensity;
	float4 color;
	float3 reflection;
	float4 specular;
	float4 normals;

	//For color render target
	color = shaderTexture.Sample(SampleType,input.tex);

	return color;
	
	//For the normal render target
	normals = normalTexture.Sample(SampleType,input.tex);

	lightDir = -lightDirection;

	lightIntensity = saturate(dot(normals.xyz,lightDir));

    //color = saturate(color * lightIntensity);







	//=================================================================
	//Unlock this for the specular light
	//=================================================================

	/*//texturecolor  = shaderTexture.Sample(SampleType,input.tex);
	normals = normalTexture.Sample(SampleType,input.tex);

	//specular = float4(0.0f,0.0f,0.0f,0.0f);

	//color = ambientColor;

	//lightDir = -lightDirection;

	//Ambient Lighting
	//lightintensity = saturate(dot(normals.xyz,lightDir));
	
	//color = saturate(diffuseColor * lightintensity);

	if(lightintensity > 0.0f)
	{
		color += (diffuseColor * lightintensity);
		color = saturate(color);

		reflection = normalize(2* lightintensity * normals.xyz - lightDir);
		specular = pow(saturate(dot(reflection , input.viewDirection)),specularPower);
	}

	//color = color * texturecolor;
	//color = saturate(color + specular);*/
	//return color;
	
	//=================================================================
	//=================================================================	




}