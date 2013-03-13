// EditTerrain.fx

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
    in float3 modelColor0 : COLOR,
    in float2 modelTCoord0 : TEXCOORD0,
    out float4 clipPosition : POSITION,
    out float4 vertexColor0 : COLOR,
    out float2 vertexTCoord0 : TEXCOORD0,
	uniform float4x4 gPVWMatrix,
	uniform float4 gShineEmissive,
	uniform float4 gShineAmbient,
	uniform float4 gShineDiffuse,
	uniform float4 gLightColour,
	uniform float4 gLightAttenuation,
	uniform float4 gLightModelDirection
)
{
    // transform
    clipPosition = mul(gPVWMatrix, float4(modelPosition,1.0f));
	
	vertexColor0.rgb = modelColor0.rgb + gShineEmissive.rgb
		+ gLightColour.rgb*gShineAmbient.rgb*gLightAttenuation[3]
		+ gLightColour.rgb*gShineDiffuse.rgb*max(0, dot(modelNormal, -gLightModelDirection.xyz))
			*gLightAttenuation[3];
	vertexColor0.a = gShineDiffuse.a;

    // pass texture coord
	vertexTCoord0 = modelTCoord0;
}

void p_EditTerrain
(
    in float4 vertexColor0 : COLOR,
    in float2 vertexTCoord0 : TEXCOORD0,
    out float4 pixelColor : COLOR,
	uniform float4 UVScale01,
	uniform float4 UVScale23,
	uniform float4 UVScale4
)
{
    	// texture	
    	float4 color0 = tex2D(Sampler0, vertexTCoord0*UVScale01.xy);
    	float4 colorAlpha = tex2D(SamplerAlpha, vertexTCoord0);
    	float4 color1 = tex2D(Sampler1, vertexTCoord0*UVScale01.zw);
    	float4 color2 = tex2D(Sampler2, vertexTCoord0*UVScale23.xy);
    	float4 color3 = tex2D(Sampler3, vertexTCoord0*UVScale23.zw);
    	float4 color4 = tex2D(Sampler4, vertexTCoord0*UVScale4.xy);

	//	pixelColor = (1.0-colorAlpha.r-colorAlpha.g-colorAlpha.b-colorAlpha.a)*color0*0.0000001
	//		+ colorAlpha.r*color1
	//		+ colorAlpha.g*color2
	//		+ colorAlpha.b*color3
	//		+ colorAlpha.a*color4;
    
		pixelColor = lerp(color0 ,color1, colorAlpha.r);
    	pixelColor = lerp(pixelColor ,color2, colorAlpha.g);
    	pixelColor = lerp(pixelColor ,color3, colorAlpha.b);
    	pixelColor = lerp(pixelColor ,color4, colorAlpha.a);
		
		pixelColor *= vertexColor0;
}