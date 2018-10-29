#define PointLights


//============================================
//Constant Buffer
//============================================
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

//============================================
//Camera Constant Buffer
//============================================

cbuffer CameraBuffer
{
	float3 cameraPostion;	
	float padding;

};

//============================================
//	Typedefs / Vertex Buffer
//============================================

struct VertexInputType
{

	float4 position	: POSITION;
	float2 tex		: TEXCOORD0;
	float3 normal	: NORMAL;

};


struct PixelInputType
{
	
	float4 position		: SV_POSITION;
	float3 CameraPos    : PPOSITIONT0;
    float4 fragPos      : PPOSITIONT1;

};


PixelInputType LightVertexShader(VertexInputType input)
{
	PixelInputType output;
	
	float4 worldPostion;

	input.position.w = 1.0f;

	output.position = mul(input.position ,  worldMatrix);
    output.fragPos = input.position;
	output.position = mul(output.position , viewMatrix);
	output.position = mul(output.position , projectionMatrix);
	
    output.CameraPos = cameraPostion; 
    

	
										 
	return output;

}



//struct Point_Lights
//{
//    float _linear;
//    float _quadratic;
//    float radius;

//};

