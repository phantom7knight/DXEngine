
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;

};

cbuffer CameraBuffer
{
	float3 cameraPostion;
	float padding;

};

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



	return output;

}