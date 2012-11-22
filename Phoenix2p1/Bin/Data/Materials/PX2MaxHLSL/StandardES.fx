// Standard.fx
#include "Head.fx"

// ------------------------------------------- blend
int gBlendMode
<
	string UIName = "BlendMode";
	string UIType = "IntSpinner";
	float UIMin = 0;
	float UIMax = 4;	
>  = 0;
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
float gSpecularPower
<
	string UIName = "SpecularPower";
	string UIWidget = "g_Shininess";
	float UIMin = 0;
	float UIMax = 10.0;
	float UIStep = 0.5;
> = 8.0;
// ------------------------------------------- struct 
struct VSIn
{
	float3 Position		: POSITION;
	float3 Normal		: NORMAL;
	float2 UV0			: TEXCOORD0;
};

struct VSOut
{
	float4 Position		: POSITION;
	float4 Colour		: COLOR;
   	float2 UV0			: TEXCOORD0;
};

struct PSIn
{
	float4 Colour		: COLOR0;
   	float2 UV0			: TEXCOORD0;
};

struct PSOut
{
	float4 Colour		: COLOR0;
};

// ------------------------------------------- shader
VSOut VS(VSIn vsIn) 
{	
	VSOut vsOut;
	
	float3 normalWorld = normalize(mul(vsIn.Normal, (float3x3)WMatrix));
	
   	vsOut.Position = mul(float4(vsIn.Position, 1.0f), PVWMatrix);
	
	vsOut.Colour.rgb = gLightColour.rgb*gShineAmbient.rgb 
		+ gLightColour.rgb*gShineDiffuse.rgb*max(0, dot(normalWorld, gLightDir));
	vsOut.Colour.a = 1.0;
	
   	vsOut.UV0 = vsIn.UV0;

	return vsOut;
}

PSOut PS(PSIn psIn)
{
	PSOut psOut;

	float4 finalColor = tex2D(gDiffuseSampler, psIn.UV0);
	
	finalColor.rgb = finalColor.rgb*psIn.Colour.rgb;

	if(gSpecularEnable)
	{
		float3 specColor = tex2D(gSpecularSampler, psIn.UV0).rgb;
		finalColor.rgb += specColor*gSpecularPower;
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
		CullMode = CW;
		VertexShader	= compile vs_2_0 VS();
		PixelShader		= compile ps_2_0 PS();
    }
}