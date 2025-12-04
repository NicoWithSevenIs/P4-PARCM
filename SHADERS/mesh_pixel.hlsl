struct PS_INPUT
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

float4 psmain(PS_INPUT input) : SV_TARGET
{
    return float4(1.0f, 1.0f, 1.0f, 1.0f);
}