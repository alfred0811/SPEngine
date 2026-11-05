// simple shader that applies a series of post-processing effects to the final rendered image. It includes effects such as bloom, color grading, and vignette. The shader takes in the rendered scene as a texture and applies the desired effects based on user-defined parameters. The output is a final image that can be displayed on the screen or saved to a file.
cbuffer PostProcessingBuffer : register(b0)
{
    int mode;
    float param0;
    float param1;
    float param2;
}

Texture2D textureMap0 : register(t0);
Texture2D textureMap1 : register(t1);
Texture2D textureMap2 : register(t2);
Texture2D textureMap3 : register(t3);

SamplerState textureSampler : register(s0);

struct VS_INPUT
{
    float3 position : POSITIONT;
    float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_Position;
    float2 texCoord : TEXCOORD;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = float4(input.position, 1.0f);
    output.texCoord = input.texCoord;
    return output;
}
float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 finalColor = 0.0f;
    if (mode == 0) // none
    {
        finalColor = textureMap0.Sample(textureSampler, input.texCoord);
    }
    return finalColor;
}