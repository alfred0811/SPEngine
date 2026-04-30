// simple shader that takes a position and renders the shape as yellow

// define expected vertex data
struct VS_INPUT
{
    float3 position : POSITION;
};

// output of vertex function that gets interpolated through the rasterizer and used in Pixel function
struct VS_OUTPUT
{
    float4 position : SV_Position;
};

// Vertex function applies effects to vertex
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = float4(input.position, 1.0f);
    return output;
}

// Pixel function, interpolated screen position of the pixel, what color should it
float4 PS(VS_OUTPUT input) : SV_Target
{
    return float4(1, 1, 0, 1); // yellow
}