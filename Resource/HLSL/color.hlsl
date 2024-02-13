cbuffer cbPerObject : register(b0)
{
    //matrix gWorldViewProj; 
    matrix worldMatrix;
    matrix viewMatrix;
    Matrix projectionMatrix;
};

struct VertexIn
{
	float4 PosL  : POSITION;
    float4 Color : COLOR;
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
    float4 Color : COLOR;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	
    vout.PosH.w = 1.0f;
    vout.PosH = mul(vin.PosL, worldMatrix);
    vout.PosH = mul(vout.PosH, viewMatrix);
    vout.PosH = mul(vout.PosH, projectionMatrix);
    
    vout.Color = vin.Color;

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    return pin.Color;
}
