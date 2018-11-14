
//#include "ShaderStructDefs.h"

//============================================
//Textures
//============================================

Texture2D positionTexture : register(t0);	//position Texture
Texture2D normalTexture : register(t1);     //Normal Texture
Texture2D DiffuseTexture  : register(t2);   //Diffuse Texture

//============================================
//TO DO :Add other textures for project
//Texture2D specularTexture : register(t3);   //Specular Texture
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
	float3 CameraPos    : PPOSITIONT0;
    float4 fragPos      : PPOSITIONT1;
	float2 tex			: TEXCOORD0;
};


//============================================




float4 LightPixelShader(PixelInputType input) : SV_TARGET
{

	
    float4 ObjectPosition;
    float3 objectColor;
    float3 Normals;


	 int width  = 800;
	 int height = 600;

 
    float2 simpletex = float2(input.position.x/width,input.position.y/height);

    ObjectPosition  = positionTexture.Sample(SampleType,input.tex);
	Normals         = normalTexture.Sample(SampleType, input.tex).xyz;
    objectColor     = DiffuseTexture.Sample(SampleType, input.tex).xyz;
            

    float4 light_Color = float4(0.5f,0.5f,0.5f,1.0f);

    //Ambient
    float ambientStrength = 0.87;
    float4 ambient = ambientStrength * light_Color;

    //Diffuse
    Normals = normalize(Normals);
    float3 LightDir = normalize(lightPosition - ObjectPosition.xyz);
    float diff = max(dot(Normals,LightDir),0.0f);
    float4 diffuse = diff * light_Color;

    //Specular
    float specular_strength     = 0.5;
    float specular_intensity    = 64;
    float3 viewdir = normalize(input.CameraPos - ObjectPosition.xyz);
    float3 reflectdir = reflect(-LightDir,Normals); 
    float spec = pow(max(dot(viewdir,reflectdir),0.0),specular_intensity);
    float4 specular = specular_strength *  spec * light_Color;


	float4 result = (ambient + diffuse + specular) * float4(objectColor, 1.0f);

   // return float4(Normals,1.0f);

    return result;
                                                                                      

}