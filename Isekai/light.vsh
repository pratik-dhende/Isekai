// Defines.
#define NUM_LIGHTS 4

// Globals.
cbuffer MatrixBuffer {
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer LightPositionBuffer {
    float4 lightPosition[NUM_LIGHTS];
};

// Typedefs.
struct VertexInput {
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct PixelInput {
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 lightPos[NUM_LIGHTS]: TEXCOORD1;
};

// Vertex Shader.
PixelInput LightVertexShader(VertexInput input) {
    PixelInput output;
    float4 worldPosition;

    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    // Store the texture coordinates for the pixel shader.
    output.tex = input.tex;

    // Calculate the normal vector against the world matrix only.
    output.normal = mul(input.normal, (float3x3)worldMatrix);

    // Normalize the vector
    output.normal = normalize(output.normal);

    // Calculate the position of the vertex in the world.
    worldPosition = mul(input.position, worldMatrix);
    
    for (int i = 0; i < NUM_LIGHTS; i++)
    {
        // Determine the light positions based on the position of the lights and the position of the vertex in the world.
        output.lightPos[i] = lightPosition[i].xyz - worldPosition.xyz;
        
        // Normalize the light position vectors.
        output.lightPos[i] = normalize(output.lightPos[i]);
    }

    return output;
}