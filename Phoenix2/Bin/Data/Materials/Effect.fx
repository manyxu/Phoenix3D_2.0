// Effect.fx
#include "Head.fx"

sampler2D BaseSampler;

void v_Effect
(
    in float3 modelPosition : POSITION,
    in float2 modelTCoord : TEXCOORD0,
    in float4 modelColor : COLOR,
    out float4 clipPosition : POSITION,
    out float2 vertexTCoord : TEXCOORD0,
    out float4 vertexColor : COLOR
)
{
    // transform
    clipPosition = mul(gPVWMatrix, float4(modelPosition,1.0f));

    // pass texture coord
    vertexTCoord = modelTCoord;

    // pass vertex color
    vertexColor = modelColor;
}

void p_Effect
(
    in float2 vertexTCoord : TEXCOORD0,
    in float4 vertexColor : COLOR,
    out float4 pixelColor : COLOR
)
{
    pixelColor = tex2D(BaseSampler, vertexTCoord);
    pixelColor *= vertexColor;
}
