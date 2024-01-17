cbuffer cbPerObject
{
	matrix worldProj; 
	matrix viewMatrix; 
	matrix projectionMatrix; 
};

struct VS_INPUT
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct VS_OUTPUT
{
    float4 position : VS_POSITION;
    float4 color : COLOR;
};

VS_OUTPUT main(VS_INPUT vin)
{
    VS_OUTPUT vout;
    vout.position = float4(vin.position, 1.0f);

    vout.position = mul(vin.position, worldProj);
    vout.position = mul(vin.position, viewMatrix);
    vout.position = mul(vin.position, projectionMatrix);
    
    vout.color = vin.color;

    return vout;
}