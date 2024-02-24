// Vertex Shader ------------------------------------------------------------

cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

struct VertexIn
{
    float4 pos : POSITION;
    float3 nrl : NORMAL;
    float2 tex : TEXCOORD0;
};

struct PixelIn
{
    float4 pos : SV_POSITION;
    float3 nrl : NORMAL; 
    float2 tex : TEXCOORD0;
};


PixelIn VS(VertexIn vin)
{
    PixelIn vout;
    vout.pos= (0.0f, 0.0f, 0.0f, 1.0f);
    vout.nrl= (0.0f, 0.0f, 0.0f);
    vout.tex= (0.0f, 0.0f);

    vout.pos = mul(vin.pos, worldMatrix);
    vout.pos = mul(vout.pos, viewMatrix);
    vout.pos = mul(vout.pos, projectionMatrix);
    
    vout.tex = vin.tex;
    
    vout.nrl = mul(vin.nrl, (float3x3)worldMatrix);
    vout.nrl = normalize(vout.nrl);

    return vout;
}

// Pixel Shader ------------------------------------------------------------

Texture2D shaderTexture : register(t0);
SamplerState SampleType : register(s0);

struct PixelOut
{
    float4 color : SV_Target0;
    float3 normal : SV_Target1; 
};

PixelOut PS(PixelIn pin) : SV_Target
{
    PixelOut pout;

    pout.color =shaderTexture.Sample(SampleType, pin.tex);
    pout.normal = float4(pin.nrl, 1.0f);

    return pout;
}