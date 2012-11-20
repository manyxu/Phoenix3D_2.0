// StdPerPixel.fx

sampler2D Sampler0;

void v_StdPerPixel
(
    in float3 modelPosition : POSITION,
    in float3 modelNormal : NORMAL,
    in float4 modelColor : COLOR,
    in float2 modelTCoord0 : TEXCOORD0,
    out float4 clipPosition : POSITION,
    out float4 vertexColor : COLOR,
    out float2 vertexTCoord0 : TEXCOORD0,
    out float3 vertexPosition : TEXCOORD1,
    out float3 vertexNormal  : TEXCOORD2,
    uniform float4x4 PVWMatrix
)
{
    // transform
    clipPosition = mul(PVWMatrix, float4(modelPosition,1.0f));

    // vertexPos
    vertexPosition = modelPosition;

    // normal
    vertexNormal = modelNormal;

    // color
    vertexColor = modelColor;

    // pass texture coord
    vertexTCoord0 = modelTCoord0;

}

void p_StdPerPixel
(
    in float4 vertexColor : COLOR,
    in float2 vertexTCoord0 : TEXCOORD0,
    in float3 vertexPosition : TEXCOORD1,
    in float3 vertexNormal : TEXCOORD2,
    out float4 pixelColor : COLOR,
    uniform float3 CameraModelPosition,
    uniform float3 MaterialEmissive,
    uniform float3 MaterialAmbient,
    uniform float4 MaterialDiffuse,
    uniform float4 MaterialSpecular,
    uniform float3 LightModelDirection,
    uniform float3 LightAmbient,
    uniform float3 LightDiffuse,
    uniform float3 LightSpecular,
    uniform float4 LightAttenuation
)
{
    // texture	
    float4 color0 = tex2D(Sampler0, vertexTCoord0);

    // lighting
    float3 normal = normalize(vertexNormal);
    float NDotL = -dot(normal, LightModelDirection);
    float3 viewVector = normalize(CameraModelPosition - vertexPosition);
    float3 halfVector = normalize(viewVector - LightModelDirection);
    float NDotH = dot(normal, halfVector);
    float4 lighting = lit(NDotL, NDotH, MaterialSpecular.a);

    float3 color = MaterialAmbient*LightAmbient
        + lighting.y*MaterialDiffuse.rgb*LightDiffuse
        + lighting.z*MaterialSpecular.rgb*LightSpecular;

    color = MaterialEmissive + LightAttenuation.w*color;

    color0.rgb *= color;
    color0.a = MaterialDiffuse.a;

    pixelColor = color0;
}