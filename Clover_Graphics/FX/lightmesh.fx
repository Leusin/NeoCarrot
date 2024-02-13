//***************************************************************************************
// color.fx by Frank Luna (C) 2011 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************

//struct DirectionalLight
//{
//    float4 Ambient;
//    float4 Diffuse;
//    float4 Specular;
//    float3 Direction;
//    float pad;
//};

//struct Material
//{
//    float4 Ambient;
//    float4 Diffuse;
//    float4 Specular; // w = SpecPower
//    float4 Reflect;
//};

#include "LightHelper.fx"

cbuffer cbPerFrame
{
    DirectionalLight gDirLight;
    float3 gEyePosW;
};

cbuffer cbPerObject
{
    float4x4 gWorld;
    float4x4 gWorldInvTranspose;
	float4x4 gWorldViewProj; 
    Material gMaterial;
};

struct VertexIn
{
	float3 PosL   : POSITION;
    float3 NormalL : NORMAL;
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
    float3 PosW : POSITION;
    float3 NormalW : NORMAL;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	
	// Transform to homogeneous clip space.
	vout.PosW= mul(float4(vin.PosL, 1.0f), gWorld).xyz;
    vout.NormalW = mul(vin.NormalL, (float3x3) gWorldInvTranspose);
	// Just pass vertex color into the pixel shader.
    vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    pin.NormalW = normalize(pin.NormalW);
    
    // The toEye vector is used in lighting.
    float3 toEye = gEyePosW - pin.PosW;

	// Cache the distance to the eye from this surface point.
    float distToEye = length(toEye);

	// Normalize.
    toEye /= distToEye;
	
    
    float3 toEyeW = normalize(gEyePosW - pin.PosW);

    float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
    
    float4 litColor = ambient + diffuse + spec;
    
    litColor.a = gMaterial.Diffuse.a;
    
    return litColor; 
}

technique11 LightTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS() ) );
    }
}
