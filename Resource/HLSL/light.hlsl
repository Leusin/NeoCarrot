// VS ??
cbuffer MatrixBuffer
{
    //matrix gWorldViewProj; 
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

// PS ??
Texture2D shaderTexture;
SamplerState SampleType;

cbuffer LightBuffer
{
    float4 diffuseColor;
    float3 lightDirection;
    float padding;
};

struct VertexInput
{
    float4 pos : POSITION;
    float3 nrl : NORMAL;
    float2 tex : TEXCOORD0;
};

struct VertexOut
{
    float4 pos : SV_POSITION;
    float3 nrl : NORMAL; 
    float2 tex : TEXCOORD0;
};

VertexOut VS(VertexInput vin)
{
    VertexOut vout;
	
    vin.pos.w = 1.0f;
    vout.pos = mul(vin.pos, worldMatrix);
    vout.pos = mul(vout.pos, viewMatrix);
    vout.pos = mul(vout.pos, projectionMatrix);

    vout.tex = vin.tex;

    vout.nrl = mul(vin.nrl, (float3x3)worldMatrix);
    vout.nrl = normalize(vout.nrl);

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    float4 textureColor = shaderTexture.Sample(SampleType, pin.tex);

    float3 lightDir = -lightDirection;

    float lightIntensity = saturate(dot(pin.nrl, lightDir));

    float4 color = saturate(diffuseColor * lightIntensity);
    color = color * textureColor;

    return color;
}