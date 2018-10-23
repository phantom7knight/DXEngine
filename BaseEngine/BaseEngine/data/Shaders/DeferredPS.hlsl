


Texture2D shaderTexture : register(t0);
//TO DO :REMOVE IF ERROR
Texture2D normalTexture : register(t1);

SamplerState SampleTypeWrap : register(s0);


struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
    float4 fragPos : POSITION0;
};


struct PixelOutputType
{
	float4 color : SV_Target0;
	float4 normal: SV_Target1;

};


PixelOutputType DeferredPixelShader(PixelInputType input) //: SV_TARGET0
{
	PixelOutputType output;

    output.color = shaderTexture.Sample(SampleTypeWrap, input.tex); //(input.fragPos); 
    //shaderTexture.Sample(SampleTypeWrap, input.tex);
	output.normal = float4(input.normal,1.0f);

	return output;
}