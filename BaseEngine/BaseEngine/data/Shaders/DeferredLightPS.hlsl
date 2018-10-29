
//#include "ShaderStructDefs.h"

//============================================
//Textures
//============================================

Texture2D shaderTexture : register(t0);	//Color Texture
Texture2D normalTexture : register(t1); //Normal Texture

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
	float4 ambientColor;
	float4 diffuseColor;
	float3 lightDirection;  //camera position
	float  specularPower;
	float4 specularColor;
	

};
//============================================


//============================================
//Typedef
//============================================

struct PixelInputType
{
	
	float4 position		 : SV_POSITION;
	float2 tex			 : TEXCOORD0;
	float3 normal		 : NORMAL;
	float3 viewDirection : TEXCOORD1;
	
};

//============================================




float4 LightPixelShader(PixelInputType input) : SV_TARGET
{
	
	//float4 texturecolor;
	float3  lightDir;
	float   lightIntensity;
    float3  lightColor = float3(1.0f,1.0f,1.0f);
	float4  color;
	float4  objectColor;
	float3  reflection;
	float4  specular;
	float3  normals;
    float4  diffuse;
    float3  viewdir;

    int width  = 800;
    int height = 600;

 
    float2 simpletex = float2(input.position.x/width,input.position.y/height);

    objectColor = shaderTexture.Sample(SampleType,simpletex);
	normals     = normalTexture.Sample(SampleType, simpletex).xyz;
	color		= shaderTexture.Sample(SampleType, input.tex);



    float ambientStrength = 0.87;
    float4 ambient = ambientStrength * ambientColor;

    normals = normalize(normals);
    lightDir = normalize(lightDirection);
    float diff = max(dot(normals,lightDir),0.0);
    diffuse = float4(diff * lightColor,1.0f);

	float specularstrength = 0.5;
	viewdir = input.viewDirection;
	reflection = reflect(-lightDir, normals);
	float spec = pow(max(dot(viewdir, reflection), 0.0), specularPower);
	specular = float4(specularstrength * spec * lightColor,1.0f);
	float4 resu = ambient + diffuse ;

	return  saturate(resu) * diffuseColor;
	

    //objectColor = shaderTexture.Sample(SampleType,input.tex);
	//normals = normalTexture.Sample(SampleType, input.tex);
    //return float4(objectColor.xyz,1.0f);
    //Ambient
   // float ambientStrength = 0.1;
  //  float3 ambient = ambientStrength * ambientColor;
   // return float4(ambient,1.0f) * objectColor;
    
    //Diffuse
  // normals = normalize(input.normal);
  // lightDir = normalize(lightDirection);
  // float diff = max(dot(normals,lightDir),0.0);
  // diffuse = diff * lightColor;

   // color = float4(diffuse * float3(0.5f,0.5f,0.5f),1.0f);

    //return color;

    //specular
    //float specularstrength = 0.5;
    //viewdir = input.viewDirection;
    //reflection = reflect(-lightDir , normals);
    //float spec = pow(max(dot(viewdir ,reflection),0.0),specularPower);
    //specular = specularstrength * spec * lightColor;

    //color = float4((ambient + diffuse + specular) * objectColor,1.0f);
    //return color;
    
	//=================================================================
    //Working Deferred Lighting
    //=================================================================

	//For color render target
	//color = shaderTexture.Sample(SampleType,input.tex);
    //
	////return color;
	//
	////For the normal render target
	//normals = normalTexture.Sample(SampleType,input.tex);
    //
	//
	//lightDir = -lightDirection;
	//
	//lightIntensity = saturate(dot(normals.xyz,lightDir));
	//
    //color = saturate(color * lightIntensity);
    //
    //
    ////   // color += (diffuseColor * lightIntensity);
    ////   // color = saturate(color);
    ////reflection = reflect((2 * lightIntensity * normals.xyz ) ,- lightDir);
    ////specular  = pow(max(dot(input.viewDirection ,reflection),0.0),specularPower);
	//
    ////color = color * specular * 0.5;
   	//
    //return float4(ambient,1.0f);
	//
    
	//=================================================================
	//Unlock this for the specular light
	//=================================================================

	//texturecolor  = shaderTexture.Sample(SampleType,input.tex);
    //normals = normalTexture.Sample(SampleType, input.tex);
   /* normals = float4(input.normal,1.0f);
    specular = specularColor;//float4(0.0f, 1.0f, 0.0f, 1.0f);

    color = ambientColor;
    

    lightDir = -lightDirection;

    //Ambient Lighting

    lightIntensity = saturate(dot(normals.xyz, lightDir));
	
    //color = saturate(diffuseColor * lightIntensity);
    
    if (lightIntensity > 0.0f)
    {
        color += (diffuseColor * lightIntensity);
        color = saturate(color);

        reflection = normalize(2 * lightIntensity * normals.xyz - lightDir);
        specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower);
    }

    //=======================================
    //TO DO :If texture works then enable it 
    //color = color * texturecolor;
    //=======================================

    color = saturate(color + specular);
	return color;
	*/
	//=================================================================
	//=================================================================	

}