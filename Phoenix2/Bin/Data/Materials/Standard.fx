// Standard.fx

#include "Head.fx"

// ------------------------------------------- controlFloat 
float4 gControlFloat; //0 Alphavertex, 1 NormalEnable, 2 SpecularEnable
float4 gDegreeFloat; //0 NormalScale, 1 SpecularPower

// ------------------------------------------- diffuse
sampler2D gDiffuseSampler;

// ------------------------------------------- normal 
sampler2D gNormalSampler;

// ------------------------------------------- specular
sampler2D gSpecularSampler;

// ------------------------------------------- reflection 
samplerCUBE gReflectionSampler;

// ------------------------------------------- shader
void v_Standard
(
	in float3 modelPosition : POSITION,
	in float4 modelColor : COLOR,
	in float3 modelNormal : NORMAL,
	in float3 modelTangent : TANGENT,
	in float3 modelBiNormal : BINORMAL,
	in float2 modelTCoord0 : TEXCOORD0,
	out float4 clipPosition : POSITION,
	out float4 vertexColor : COLOR,
	out float2 vertexTCoord0 : TEXCOORD0,
	out float3 vertexLightDir : TEXCOORD1,
	out float3 vertexNormal : TEXCOORD2,
	out float3 vertexViewDir : TEXCOORD3
)
{
	clipPosition = mul(gPVWMatrix, float4(modelPosition,1.0f));

	vertexColor = modelColor;
	vertexNormal = modelNormal;
	vertexTCoord0 = modelTCoord0;

	float4 worldPos = mul(gWMatrix, float4(modelPosition,1.0f));
	float3 viewDir = gCameraWorldPosition - worldPos.xyz;

	//if (gControlFloat[1] == 1.0f)
	{
		float3x3 objToTangent;

		objToTangent[0] = modelTangent;
		objToTangent[1] = modelBiNormal;
		objToTangent[2] = modelNormal;
		
		vertexLightDir = mul(objToTangent, gLightModelDirection);
		vertexViewDir = mul(objToTangent, viewDir);
	}
	if (gControlFloat[1] == 5.0f)
	{
		vertexLightDir = gLightModelDirection;
		vertexViewDir = viewDir;
	}
}

void p_Standard
(
	in float4 vertexColor : COLOR,
	in float2 vertexTCoord0 : TEXCOORD0,
	in float3 vertexLightDir : TEXCOORD1,
	in float3 vertexNormal : TEXCOORD2,
	in float3 vertexViewDir : TEXCOORD3,
	out float4 pixelColor : COLOR
)
{
	float4 finalColor = tex2D(gDiffuseSampler, vertexTCoord0);
	float3 normal = normalize(vertexNormal);
	float3 lightDir = normalize(vertexLightDir); 
	float3 viewDir = normalize(vertexViewDir);
	float alpha = 1.0f;

	if(gControlFloat[0] == 1.0f)
		finalColor.a *= vertexColor.a;

	if(gControlFloat[1] == 1.0f)
		normal = NormalCalc(tex2D(gNormalSampler, vertexTCoord0).xyz, gDegreeFloat[0]);
		
	if(gControlFloat[2] == 1.0f)
	{
		float3 specColor = tex2D(gSpecularSampler, vertexTCoord0).xyz;
		finalColor.rgb += specColor*gDegreeFloat[1];
	}

	finalColor.rgb *= (gShineAmbient.rgb*gLightColour.rgb + 
		gLightColour.rgb*gShineDiffuse.rgb*saturate(dot(normal, lightDir)));
	finalColor.rgb += gShineEmissive.rgb;

	pixelColor = finalColor;
}