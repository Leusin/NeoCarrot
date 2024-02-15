// ??
cbuffer MatrixBuffer
{
    //matrix gWorldViewProj; 
    matrix worldMatrix;
    matrix viewMatrix;
    Matrix projectionMatrix;
};

Texture2D shaderTexture;
SamplerState SampleType;

struct VertexIn
{
    float4 pos : POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD0;
};

struct VertexOut
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD0;
};

VertexOut VS(VertexIn vin)
{
    printf("vs ??? ??\n");

    VertexOut vout;
	
    // ??, ?, ?? ??? ?? ??? ?? ??
    vout.pos.w = 1.0f;
    vout.pos = mul(vin.pos, worldMatrix);
    vout.pos = mul(vout.pos, viewMatrix);
    vout.pos = mul(vout.pos, projectionMatrix);

    // ?? ???? ??? ?? ??
    vout.tex = vin.tex;

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    printf("ps ??? ??\n");

    // ??? ?? ???? ???? ??? ?? ?? ???
    float4 textureColor = shaderTexture.Sample(SampleType, pin.tex);

    return textureColor;
}
