// 전역
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
    float2 tex : TEXCOORD0;
};

struct VertexOut
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD0;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
	
    // 월드, 뷰, 투영 행렬에 대한 정점의 위치 계산
    vout.pos.w = 1.0f;
    vout.pos = mul(vin.pos, worldMatrix);
    vout.pos = mul(vout.pos, viewMatrix);
    vout.pos = mul(vout.pos, projectionMatrix);

    // 픽셀 셰이더의 텍스처 좌표 저장
    vout.tex = vin.tex;

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    // 텍스처 좌표 위치에서 샘프러를 사용해 픽셀 색상 샘플링
    float4 textureColor = shaderTexture.Sample(SampleType, pin.tex);

    return textureColor;
}
