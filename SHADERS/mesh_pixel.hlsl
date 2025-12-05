struct PS_INPUT
{
    float4 position : SV_POSITION;
};

cbuffer CONSTANT : register(b0)
{
    row_major float4x4 transform;
    row_major float4x4 view;
    row_major float4x4 projection;
    float3 color;
    float delta_time;
}

float4 psmain(PS_INPUT input) : SV_TARGET
{
    return float4(color, 1.0f);
}