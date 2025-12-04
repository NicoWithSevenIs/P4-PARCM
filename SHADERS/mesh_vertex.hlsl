struct VS_INPUT
{
    float3 position : POSITION0;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
};

cbuffer CONSTANT : register(b0)
{
    row_major float4x4 transform;
    row_major float4x4 view;
    row_major float4x4 projection;
    float delta_time;
}

VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    float4 vec = float4(input.position, 1.0);
  
    output.position = mul(vec, transform);
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
    
    return output;
}