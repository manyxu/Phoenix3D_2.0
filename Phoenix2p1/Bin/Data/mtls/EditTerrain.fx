// EditTerrain.fx
#include "Head.fx"

sampler2D Sampler0;
sampler2D SamplerAlpha;
sampler2D Sampler1;
sampler2D Sampler2;
sampler2D Sampler3;
sampler2D Sampler4;

void v_EditTerrain
(
    in float3 modelPosition : POSITION,
    in float3 modelNormal : NORMAL,
    in float3 modelColor : COLOR,
    in float2 modelTCoord0 : TEXCOORD0,
    in float2 modelTAlpha : TEXCOORD1,
    in float2 modelTCoord1 : TEXCOORD2,
    in float2 modelTCoord2 : TEXCOORD3,
    in float2 modelTCoord3 : TEXCOORD4,
    in float2 modelTCoord4 : TEXCOORD5,
    out float4 clipPosition : POSITION,
    out float4 vertexColor : COLOR,
    out float2 vertexTCoord0 : TEXCOORD0,
    out float2 vertexTAlpha : TEXCOORD1,
    out float2 vertexTCoord1 : TEXCOORD2,
    out float2 vertexTCoord2 : TEXCOORD3,
    out float2 vertexTCoord3 : TEXCOORD4,
    out float2 vertexTCoord4 : TEXCOORD5
)
{
    // transform
    clipPosition = mul(gPVWMatrix, float4(modelPosition,1.0f));
	
	vertexColor.rgb = modelColor.rgb + gShineEmissive.rgb
		+ gLightColour.rgb*gShineAmbient.rgb
		+ gLightColour.rgb*gShineDiffuse.rgb*max(0, dot(modelNormal, -gLightModelDirection));
	vertexColor.a = gShineDiffuse.a;

    // pass texture coord
    vertexTCoord0 = float2(modelTCoord0.x, 1.0f-modelTCoord0.y);
    vertexTAlpha  = modelTAlpha;
    vertexTCoord1 = float2(modelTCoord1.x, 1.0f-modelTCoord1.y);
    vertexTCoord2 = float2(modelTCoord2.x, 1.0f-modelTCoord2.y);
    vertexTCoord3 = float2(modelTCoord3.x, 1.0f-modelTCoord3.y);
    vertexTCoord4 = float2(modelTCoord4.x, 1.0f-modelTCoord4.y);
}

void p_EditTerrain
(
    in float4 vertexColor : COLOR,
    in float2 vertexTCoord0 : TEXCOORD0,
    in float2 vertexTAlpha : TEXCOORD1,
    in float2 vertexTCoord1 : TEXCOORD2,
    in float2 vertexTCoord2 : TEXCOORD3,
    in float2 vertexTCoord3 : TEXCOORD4,
    in float2 vertexTCoord4 : TEXCOORD5,
    out float4 pixelColor : COLOR,
    uniform float4 UVScale01,
    uniform float4 UVScale23,
    uniform float4 UVScale4
)
{
    	// texture	
    	float4 color0 = tex2D(Sampler0, vertexTCoord0*UVScale01.xy);
    	float4 colorAlpha = tex2D(SamplerAlpha, vertexTAlpha);
    	float4 color1 = tex2D(Sampler1, vertexTCoord1*UVScale01.zw);
    	float4 color2 = tex2D(Sampler2, vertexTCoord2*UVScale23.xy);
    	float4 color3 = tex2D(Sampler3, vertexTCoord3*UVScale23.zw);
    	float4 color4 = tex2D(Sampler4, vertexTCoord4*UVScale4.xy);

	//	pixelColor = (1.0-colorAlpha.r-colorAlpha.g-colorAlpha.b-colorAlpha.a)*color0*0.0000001
	//		+ colorAlpha.r*color1
	//		+ colorAlpha.g*color2
	//		+ colorAlpha.b*color3
	//		+ colorAlpha.a*color4;
    
		pixelColor = lerp(color0 ,color1, colorAlpha.r);
    	pixelColor = lerp(pixelColor ,color2, colorAlpha.g);
    	pixelColor = lerp(pixelColor ,color3, colorAlpha.b);
    	pixelColor = lerp(pixelColor ,color4, colorAlpha.a);
		
		pixelColor *= vertexColor;
}