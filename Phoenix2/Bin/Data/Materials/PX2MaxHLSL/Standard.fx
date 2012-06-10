// Standard.fx
#include "Head.fx"

// ------------------------------------------- blend
int gBlendMode
<
	string UIName = "BlendMode";
	string UIType = "IntSpinner";
	float UIMin = 0;
	float UIMax = 4;	
> = 0;
// ------------------------------------------- doubleSide
bool gDoubleSide
<
	string UIName = "DoubleSide";
> = false;
// ------------------------------------------- alphaVertex
bool gAlphaVertex
<
	string UIName = "Vertex Alpha";
> = false;
// ------------------------------------------- diffuse
texture gDiffuseTexture : DiffuseMap
< 
	string UIName = "Diffuse Map";
	int Texcoord = 0;
	int MapChannel = 1;
>;
sampler2D gDiffuseSampler = sampler_state
{
	Texture = <gDiffuseTexture>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
};
// ------------------------------------------- specular
bool gSpecularEnable 
<
	string UIName = "Specular Texture Enable";
> = false;
float gSpecularPower
<
	string UIName = "SpecularPower";
	string UIWidget = "g_Shininess";
	float UIMin = 0;
	float UIMax = 10.0;
	float UIStep = 0.5;
> = 8.0;
texture gSpecularTexture
< 
	string UIName = "Specular";
	int Texcoord = 6;
	int MapChannel = 1;
>;
sampler2D gSpecularSampler = sampler_state
{
	Texture = <gSpecularTexture>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
};

// ------------------------------------------- normal 
bool gNormalEnable
<
	string UIName = "Normal Enable";
> = false;
texture gNormalTexture 
< 
	string UIName = "Normal";
	int Texcoord = 7;
	int MapChannel = 1;
>;
sampler2D gNormalSampler = sampler_state
{
	Texture = <gNormalTexture>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
};
float gNormalScale
<
	string UIName = "Bump Amount";
	float UIMin = 0.0f;
	float UIMax = 5.0f;
	float UIStep = 0.2f;
>   = 1.0f;

// ------------------------------------------- reflection 
bool gReflectionEnable
<
	string UIName = "Reflection Enable";
> = false;
texture gReflectionTexture
< 
	string UIName = "Reflection";
	string Type = "CUBE";
>;
samplerCUBE gReflectionSampler = sampler_state
{
	Texture = <gReflectionTexture>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
};
float gReflectPower
<
	string UIName = "ReflectPower";
	string UIWidget = "gReflectPower";
	float UIMin = 0;
	float UIMax = 10;
	float UIStep = 1.0;
> = 8.0;
// ------------------------------------------- struct 
struct VSIn
{
	float3 Position		: POSITION;
	float4 Colour		: COLOR;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float3 BiNormal		: BINORMAL;
	float2 UV0		: TEXCOORD0;	
};

struct VSOut
{
	float4 Position		: POSITION;
	float4 Colour		: COLOR;
   	float2 UV0		: TEXCOORD0;
   	float3 LightDir		: TEXCOORD1;
   	float3 Normal		: TEXCOORD2;
   	float3 ViewDir		: TEXCOORD3; 
};

struct PSIn
{
	float4 Colour		: COLOR0;
   	float2 UV0		: TEXCOORD0;
   	float3 LightDir		: TEXCOORD1;
   	float3 Normal		: TEXCOORD2;
   	float3 ViewDir		: TEXCOORD3;
};

struct PSOut
{
	float4 Colour		: COLOR0;
};

// ------------------------------------------- shader
VSOut VS(VSIn vsIn) 
{
	VSOut vsOut;                                                                                                                                                                                                                                                                                                                                   
   	vsOut.Position = mul(float4(vsIn.Position, 1.0f), PVWMatrix);
	vsOut.Colour = vsIn.Colour;
	vsOut.Normal = vsIn.Normal;

	float4 WorldPos = mul(float4(vsIn.Position, 1.0f),WMatrix);
	float3 ViewDir = CameraWorldPosition - WorldPos.xyz;

	if(gNormalEnable)
	{
		float3x3 objToTangent;

		objToTangent[0] = vsIn.BiNormal;
		objToTangent[1] = vsIn.Tangent;
		objToTangent[2] = vsIn.Normal;
		
		vsOut.LightDir = mul(objToTangent, gLightDir);
		vsOut.ViewDir = mul(objToTangent, ViewDir);		
	}
	else
	{
		vsOut.LightDir = gLightDir;
		vsOut.ViewDir = ViewDir;
	}
	
   	vsOut.UV0 = vsIn.UV0;

	return vsOut;
}

PSOut PS( PSIn psIn )
{
	PSOut psOut;

	float4 finalColor = tex2D(gDiffuseSampler, psIn.UV0);
	float3 Normal = normalize(psIn.Normal);
	float3 LightDir = normalize(psIn.LightDir); 
	float3 ViewDir = normalize(psIn.ViewDir);
	float alpha = 1.0f;

	if(gAlphaVertex)
		finalColor.a *= psIn.Colour.a;

	if(gNormalEnable)
		Normal = NormalCalc(tex2D(gNormalSampler, psIn.UV0).xyz, gNormalScale);
		
	if(gSpecularEnable)
	{
		float3 specColor = tex2D(gSpecularSampler, psIn.UV0).xyz;
		finalColor.rgb += specColor*gSpecularPower;
	}

	finalColor.rgb *= (gShineAmbient.rgb*gLightColour.rgb + 
		gLightColour.rgb*gShineDiffuse.rgb*saturate(dot(Normal, LightDir)));
	finalColor.rgb += gShineEmissive.rgb;

	if (gReflectionEnable)
	{
		float3 CUV = normalize(reflect(ViewDir, Normal));
		float4 env = texCUBE(gReflectionSampler, CUV);
		finalColor.rgb += env.rgb*gReflectPower/10.0f; 
	}	

	psOut.Colour = finalColor;

	return psOut;
}

technique Default
{
    pass P0 
    {		
#if gBlendMode == 0
        	AlphaBlendEnable = FALSE;
#elif gBlendMode == 1
		AlphaBlendEnable = TRUE;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		//ZWriteEnable = FALSE;
		AlphaTestEnable = TRUE;
		AlphaRef = 178;
		AlphaFunc = GREATEREQUAL;
#elif gBlendMode == 2
		AlphaBlendEnable = FALSE;
		AlphaTestEnable = TRUE;
		AlphaRef = 178;
		AlphaFunc = GREATEREQUAL;
#endif

#if gDoubleSide == true
	CullMode = NONE;
#else
	CullMode = CW;
#endif
		VertexShader		= compile vs_2_0 VS();
		PixelShader		= compile ps_2_0 PS();
    }
}