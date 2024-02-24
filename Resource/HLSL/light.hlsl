// Vertex Shader ------------------------------------------------------------

cbuffer MatrixBuffer
{
    //matrix gWorldViewProj; 
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

struct VertexIn
{
    float4 pos : POSITION;
    float2 tex : TEXCOORD0;
};

struct PixelIn
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD0;
};

PixelIn VS(VertexIn vin)
{
    PixelIn vout;
	
    vin.pos.w = 1.0f;
    vout.pos = mul(vin.pos, worldMatrix);
    vout.pos = mul(vout.pos, viewMatrix);
    vout.pos = mul(vout.pos, projectionMatrix);

    vout.tex = vin.tex;

    return vout;
}

// Pixel Shader ------------------------------------------------------------

Texture2D colorTexture : register(t0);
Texture2D normalTexture : register(t1);

SamplerState SampleTypePoint : register(s0);

cbuffer LightBuffer
{
    float3 lightDirection;
    float padding;
};

struct VertexOut
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD0;
};


float4 PS(PixelIn pin) : SV_Target
{
    float4 colors = colorTexture.Sample(SampleTypePoint, pin.tex);
    float4 normals = normalTexture.Sample(SampleTypePoint, pin.tex);
    float3 lightDir = - lightDirection;
    float lightIntensity = saturate(dot(normals.xyz, lightDir));
    float4 outputColor = saturate(colors * lightIntensity);

    return outputColor;
}