
#define LIGHTS_COUNT 4

//Constant Buffer
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;

};

/*cbuffer LightPositionBuffer
{
	float4 lightPosition[LIGHTS_COUNT];
};*/

cbuffer CameraBuffer
{
	float3 cameraPostion;
	float padding;

};


//Input layout
struct VertexInputType
{

	float4 position	: POSITION;
	float2 tex		: TEXCOORD0;
	float3 normal	: NORMAL;

};


struct PixelInputType
{
	
	float4 position		: SV_POSITION;
	float2 tex			: TEXCOORD0;
	float3 normal		: NORMAL;
	float3 viewDirection: TEXCOORD1;

	/*float3 lightPos1 : TEXCOORD2;
	float3 lightPos2 : TEXCOORD3;
	float3 lightPos3 : TEXCOORD4;
	float3 lightPos4 : TEXCOORD5;*/


};


PixelInputType LightVertexShader(VertexInputType input)
{
	PixelInputType output;
	float4 worldPostion;

	input.position.w = 1.0f;

	output.position = mul(input.position ,  worldMatrix);
	output.position = mul(output.position , viewMatrix);
	output.position = mul(output.position , projectionMatrix);
	
	output.tex - input.tex;

	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);

	worldPostion = mul(input.position , worldMatrix);
	output.viewDirection = cameraPostion.xyz - worldPostion.xyz;

	output.viewDirection = normalize(output.viewDirection);

	/*output.lightPos1.xyz = lightPosition[0] - worldPosition.xyz;
	output.lightPos2.xyz = lightPosition[1] - worldPosition.xyz;
	output.lightPos3.xyz = lightPosition[2] - worldPosition.xyz;
	output.lightPos4.xyz = lightPosition[3] - worldPosition.xyz;


	output.lightPos1 = normalize(output.lightPos1);
	output.lightPos2 = normalize(output.lightPos2);
	output.lightPos3 = normalize(output.lightPos3);
	output.lightPos4 = normalize(output.lightPos4);*/
										 
	return output;

}