

//The initial texture which we send
Texture2D shaderTexture : register(t0);

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
	float4 gcolor           : SV_Target0;
	float4 gnormal          : SV_Target1;
    //float4 gposition      : SV_Target2;
    //float4 gSpecularcolor : SV_Target3;
};


PixelOutputType DeferredPixelShader(PixelInputType input) //: SV_TARGET0
{
	PixelOutputType output;

    //This gives the Color for Render Target 0
    output.gcolor = (input.fragPos); 

    //output.color = shaderTexture.Sample(SampleTypeWrap, input.tex);

    //This is for the Normal Render Target
	output.gnormal = float4(input.normal,1.0f);

    

	return output;
}