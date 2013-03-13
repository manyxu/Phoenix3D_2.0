// Standard.fx

#include "Head.fx"

// ------------------------------------------- diffuse
sampler2D gDiffuseSampler;

// ------------------------------------------- shader
void v_Jungler
(
	in float3 modelPosition : POSITION,
	in float3 modelNormal : NORMAL,
	in float2 modelTCoord0 : TEXCOORD0,
	out float4 clipPosition : POSITION,
	out float2 vertexTCoord0 : TEXCOORD0,
	out float4 vertexTCoord1 : TEXCOORD1
)
{	
	float valSin = sin(gUser.x + gUser.y + modelPosition.y);
	modelPosition += modelNormal * 0.1 * valSin * modelTCoord0.y;

	clipPosition = mul(gPVWMatrix, float4(modelPosition,1.0f));
	
	vertexTCoord0 = modelTCoord0;
	
	vertexTCoord1.rgb = gShineEmissive.rgb
		+ gLightColour.rgb*gShineAmbient.rgb
		+ gLightColour.rgb*gShineDiffuse.rgb*max(0, abs(dot(modelNormal, -gLightModelDirection)));
	vertexTCoord1.a = gShineDiffuse.a;
}

void p_Jungler
(
	in float2 vertexTCoord0 : TEXCOORD0,
	in float4 vertexTCoord1 : TEXCOORD1,
	out float4 pixelColor : COLOR
)
{
	float4 finalColor = tex2D(gDiffuseSampler, float2(vertexTCoord0.x, 1.0f-vertexTCoord0.y));
	finalColor *= vertexTCoord1;

	pixelColor = finalColor;
}