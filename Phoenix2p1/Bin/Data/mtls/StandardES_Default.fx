// Standard.fx

// ------------------------------------------- diffuse
sampler2D gDiffuseSampler;

// ------------------------------------------- shader
void v_StandardES_Default
(
	in float3 modelPosition : POSITION,
	in float3 modelNormal : NORMAL,
	in float2 modelTCoord0 : TEXCOORD0,
	out float4 clipPosition : POSITION,
	out float2 vertexTCoord0 : TEXCOORD0,
	out float4 vertexTCoord1 : TEXCOORD1,
	uniform float4x4 gPVWMatrix,
	uniform float4 gShineEmissive,
	uniform float4 gShineAmbient,
	uniform float4 gShineDiffuse,
	uniform float4 gLightColour,
	uniform float4 gLightModelDirection
)
{
	clipPosition = mul(gPVWMatrix, float4(modelPosition,1.0f));
	
	vertexTCoord0 = modelTCoord0;
	
	vertexTCoord1.rgb = gShineEmissive.rgb
		+ gLightColour.rgb*gShineAmbient.rgb
		+ gLightColour.rgb*gShineDiffuse.rgb*max(0, dot(modelNormal, -gLightModelDirection.rgb));
	vertexTCoord1.a = gShineDiffuse.a;
}

void p_StandardES_Default
(
	in float2 vertexTCoord0 : TEXCOORD0,
	in float4 vertexTCoord1 : TEXCOORD1,
	out float4 pixelColor : COLOR
)
{
	float4 finalColor = tex2D(gDiffuseSampler, vertexTCoord0);
	finalColor *= vertexTCoord1;

	pixelColor = finalColor;
}