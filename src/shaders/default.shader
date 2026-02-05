#shader vertex
#version 460 core

// Grid position are in xy clipped space
vec3 gridPlane[6] = vec3[](
    vec3(1, 1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
    vec3(-1, -1, 0), vec3(1, 1, 0), vec3(1, -1, 0)
);

// normal vertice projection
void main() {
    vec3 p = gridPlane[gl_VertexID].xyz;
    gl_Position = vec4(p, 1.0); // using directly the clipped coordinates
}

#shader fragment
#version 460 core

uniform int width;
uniform int height;

layout(rgba8ui, binding = 0) uniform uimage2D pixelData;

out vec4 FragColor;

vec3 colors[4] = {vec3(0.0,0.0,0.0), vec3(1.0,1.0,0.0), vec3(0.5,0.5,0.5), vec3(0.0,0.0,0.6)};

void main() {
    ivec2 texelCoord = ivec2(gl_FragCoord.xy);

    uvec4 data = imageLoad(pixelData, texelCoord);

    FragColor = vec4(colors[data.r], 1.0);
}

