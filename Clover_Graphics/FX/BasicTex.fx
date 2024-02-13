//=============================================================================
// Basic.fx by Frank Luna (C) 2011 All Rights Reserved.
//
// Basic effect that currently supports transformations, lighting, and texturing.
//=============================================================================

#include "LightHelper.fx"

cbuffer cbPerFrame
{
	DirectionalLight gDirLights[3];
	float3 gEyePosW;

	float  gFogStart;
	float  gFogRange;
	float4 gFogColor;
};

cbuffer cbPerObject
{
	float4x4 gWorld;
	float4x4 gWorldInvTranspose;
	float4x4 gWorldViewProj;
    //float4x4 gWorldViewProjTex;
	float4x4 gTexTransform;
    //float4x4 gShadowTransform; 
	Material gMaterial;
}; 

// 행렬 팔레트
cbuffer cbSkinned
{
    float4x4 gBoneTransforms[255];
};

//Nonnumeric values cannot be added to a cbuffer.
// 숫자아닌 값은 상수버처에 더할 수 없다
//Texture2D gShadowMap;
Texture2D gDiffuseMap;
//Texture2D gNormalMap;
//Texture2D gSsaoMap;

SamplerState samAnisotropic
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

struct VertexIn
{
	float3 PosL    : POSITION;
	float3 NormalL : NORMAL;
	float2 Tex     : TEXCOORD;
    //float4 TangentL : TANGENT; // 언젠간 추가할 것
};

struct SkinnedVertexIn
{
    float3 PosL		   : POSITION;
    float3 NormalL	   : NORMAL;
    float2 Tex		   : TEXCOORD;
    //float4 TangentL   : TANGENT;
    float3 Weights	   : WEIGHTS;
    uint4  BoneIndices : BONEINDICES;
};

struct VertexOut
{
    float4 PosH    : SV_POSITION;
    float3 PosW    : POSITION;
    float3 NormalW : NORMAL;
    //float4 TangentL   : TANGENT;
    float2 Tex     : TEXCOORD;
    //float4 ShadowPosH : TEXCOORD1;
    //float4 SsaoPosH : TEXCOORD2;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
	
	// Transform to world space space. 
    // 월드 공간으로 변환
    vout.PosW    = mul(float4(vin.PosL, 1.0f), gWorld).xyz;
    vout.NormalW = mul(vin.NormalL, (float3x3) gWorldInvTranspose);
    //vout.TangentW = mul(vin.TangentL, gWorld);
		
	// Transform to homogeneous clip space.
    // 동차 절단으로 변환
    vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	
	// Output vertex attributes for interpolation across triangle.
    vout.Tex = mul(float4(vin.Tex, 0.0f, 1.0f), gTexTransform).xy;

    return vout;
}

VertexOut SkinnedVS(SkinnedVertexIn vin)
{
    VertexOut vout;
	
	// 버텍스 가중치 배열 초기화
    float weights[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    weights[0] = vin.Weights.x;
    weights[1] = vin.Weights.y;
    weights[2] = vin.Weights.z;
    weights[3] = 1.0f - weights[0] - weights[1] - weights[2];
    
    //weights[0] = 0;
    //weights[1] = 0;
    //weights[2] = 0;
    //weights[3] = 0;
	
    float3 posL		= float3(0.0f, 0.0f, 0.0f);
    float3 normalL	= float3(0.0f, 0.0f, 0.0f);
	//float3 tangentL = float3(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < 4; ++i)
    {
        posL	+= weights[i] * mul(float4(vin.PosL, 1.0f), gBoneTransforms[vin.BoneIndices[i]]).xyz;
        normalL += weights[i] * mul(vin.NormalL, (float3x3)gBoneTransforms[vin.BoneIndices[i]]);
        //tangentL += weights[i]*mul(vin.TangentL.xyz, (float3x3)gBoneTransforms[vin.BoneIndices[i]]);
    }
	
	// 월드 공간으로 변환
    vout.PosW = mul(float4(posL, 1.0f), gWorld).xyz;
    vout.NormalW = mul(normalL, (float3x3) gWorldInvTranspose);
    //vout.TangentW = float4(mul(tangentL, (float3x3)gWorld), vin.TangentL.w);
		
	// 동차 절단 공간(homogeneous clip space)으로 변환
    vout.PosH = mul(float4(posL, 1.0f), gWorldViewProj);
	
	// Output vertex attributes for interpolation across triangle.
	// 정점 특성 출력
    vout.Tex = mul(float4(vin.Tex, 0.0f, 1.0f), gTexTransform).xy;
    
    vout.Tex.x = weights[0];
    vout.Tex.y = weights[1];

    //vout.SsaoPosH = mul(float4(posL, 1.0f), gWorldViewProjTex);
    
    return vout;
}
 
float4 PS(VertexOut pin
        , uniform int gLightCount
        , uniform bool gUseTexure
        //, uniform bool gAlphaClip
        //, uniform bool gFogEnabled
        //, uniform bool gReflectionEnabled
        ) : SV_Target
{
	// Interpolating normal can unnormalize it, so normalize it.
    pin.NormalW = normalize(pin.NormalW);

	// The toEye vector is used in lighting.
	float3 toEye = gEyePosW - pin.PosW;

	// Cache the distance to the eye from this surface point.
	float distToEye = length(toEye); 

	// Normalize.
	toEye /= distToEye;
	
    // Default to multiplicative identity.
    float4 texColor = float4(1, 1, 1, 1);
    if(gUseTexure)
	{
		// Sample texture.
		texColor = gDiffuseMap.Sample( samAnisotropic, pin.Tex );
        /*
        if(gAlphaClip)
		{
			// Discard pixel if texture alpha < 0.1.  Note that we do this
			// test as soon as possible so that we can potentially exit the shader 
			// early, thereby skipping the rest of the shader code.
			clip(texColor.a - 0.1f);
		}
        */
        
	}
	 
    //
	// Normal mapping
	//

    //float3 normalMapSample = gNormalMap.Sample(samLinear, pin.Tex).rgb;
    //float3 bumpedNormalW = NormalSampleToWorldSpace(normalMapSample, pin.NormalW, pin.TangentW);
    
	//
	// Lighting.
	//

	float4 litColor = texColor;
	if( gLightCount > 0  )
	{  
		// Start with a sum of zero. 
		float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 spec    = float4(0.0f, 0.0f, 0.0f, 0.0f);

		// Sum the light contribution from each light source.  
		[unroll]
		for(int i = 0; i < gLightCount; ++i)
		{
			float4 A, D, S;
			ComputeDirectionalLight(gMaterial, gDirLights[i], pin.NormalW, toEye, 
				A, D, S);

			ambient += A;
			diffuse += D;
			spec    += S;
            
            ambient += /*ambientAccess */ A;
            diffuse += /*shadow[i]     */ D;
            spec    += /*shadow[i]     */ S;
        }

		// Modulate with late add.
		litColor = texColor*(ambient + diffuse) + spec;
	}

	// Common to take alpha from diffuse material and texture.
	litColor.a = gMaterial.Diffuse.a * texColor.a;

	//litColor.r = 1.0f;
	//litColor.g = 1.0f;
	//litColor.b = 1.0f;
	//litColor.a = 1.0f;
    
    litColor.r = pin.Tex.x;
    litColor.g = pin.Tex.y;
    litColor.b = 0;
    litColor.a = 1.0f;
    
    

    return litColor;
}

technique11 Light1
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(1, false) ) );
    }
}

technique11 Light2
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(2, false) ) );
    }
}

technique11 Light3
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(3, false) ) );
    }
}

technique11 Light0Tex
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(0, true) ) );
    }
}

technique11 Light1Tex
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(1, true) ) );
    }
}

technique11 Light2Tex
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(2, true) ) );
    }
}

technique11 Light3Tex
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(3, true) ) );
    }
}

technique11 Light1Skinned
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, SkinnedVS()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, PS(1, false)));
    }
}

technique11 Light2Skinned
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, SkinnedVS()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, PS(2, false)));
    }
}

technique11 Light3Skinned
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, SkinnedVS()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, PS(3, false)));
    }
}

technique11 Light0TexSkinned
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, SkinnedVS()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, PS(0, true)));
    }
}

technique11 Light1TexSkinned
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, SkinnedVS()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, PS(1, true)));
    }
}

technique11 Light2TexSkinned
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, SkinnedVS()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, PS(2, true)));
    }
}

technique11 Light3TexSkinned
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, SkinnedVS()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, PS(3, true)));
    }
}
