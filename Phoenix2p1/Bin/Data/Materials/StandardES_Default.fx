// Standard.fx

#include "Head.fx"

// ------------------------------------------- diffuse
sampler2D gDiffuseSampler;

// ------------------------------------------- shader
void v_StandardES_Default
(
	in float3 modelPosition : POSITION,
	in float3 modelNormal : NORMAL,
	in float2 modelTCoord0 : TEXCOORD0,
	out float4 clipPosition : POSITION,
	out float4 vertexColor : COLOR,
	out float2 vertexTCoord0 : TEXCOORD0
)
{
	clipPosition = mul(gPVWMatrix, float4(modelPosition,1.0f));
	
	vertexColor.rgb = gShineEmissive.rgb
		+ gLightColour.rgb*gShineAmbient.rgb
		+ gLightColour.rgb*gShineDiffuse.rgb*max(0, dot(modelNormal, gLightModelDirection));
	vertexColor.a = gShineDiffuse.a;
	
	vertexTCoord0 = modelTCoord0;
}

void p_StandardES_Default
(
	in float4 vertexColor : COLOR,
	in float2 vertexTCoord0 : TEXCOORD0,
	out float4 pixelColor : COLOR
)
{
	float4 finalColor = tex2D(gDiffuseSampler, vertexTCoord0);
	finalColor *= vertexColor;

	pixelColor = finalColor;
}