
//#include "ShaderStructDefs.h"

//============================================
//Textures
//============================================

Texture2D positionTexture : register(t0);	//position Texture
Texture2D normalTexture : register(t1);     //Normal Texture

//============================================
//TO DO :Add other textures for project
//Texture2D specularTexture : register(t2);   //Specular Texture
//Texture2D DiffuseTexture  : register(t3);   //Diffuse Texture
//============================================


//============================================
//Sample State
//============================================

SamplerState SampleType : register(s0);


//============================================
//Light Constant Buffer
//============================================
cbuffer LightBuffer
{
	float4  ambientColor;
	float4  diffuseColor;
	float3  lightPosition;  
	float   specularPower;
	float4  specularColor;
	

};
//============================================


//============================================
//Typedef
//============================================
struct PixelInputType
{
	
	float4 position		: SV_POSITION;
	float3 CameraPos    : PPOSITIONT;
    float4 fragPos      : PPOSITIONT1;
};


//============================================




float4 LightPixelShader(PixelInputType input) : SV_TARGET
{

	
    float4 ObjectColor;
    float3 Normals;


    int width  = 800;
    int height = 600;

 
    float2 simpletex = float2(input.position.x/width,input.position.y/height);

    ObjectColor = positionTexture.Sample(SampleType,simpletex);
	Normals     = normalTexture.Sample(SampleType, simpletex).xyz;
            



    float ambientStrength = 0.87;
    float4 ambient = ambientStrength * ambientColor;



    return ambient;
                                                                                      

}