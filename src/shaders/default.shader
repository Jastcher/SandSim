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

const uint AIR   = 0u;
const uint SAND  = 1u;
const uint STONE = 2u;
const uint WATER = 3u;

const vec3 AIR_COLOR   = vec3(0.0, 0.0, 0.0);
const vec3 SAND_COLOR  = vec3(1.0, 1.0, 0.0);
const vec3 STONE_COLOR = vec3(0.2, 0.2, 0.2);
const vec3 WATER_COLOR = vec3(0.0, 0.0, 0.8);

void main() {
    ivec2 texelCoord = ivec2(gl_FragCoord.xy);

    uvec4 data = imageLoad(pixelData, texelCoord);

    vec3 outColor = AIR_COLOR;

    switch (data.r) {
        case AIR:
            outColor = AIR_COLOR;
            break;

        case SAND:
            outColor = SAND_COLOR;
            break;

        case STONE:
            outColor = STONE_COLOR;
            break;

        case WATER:
            outColor = WATER_COLOR;
            break;

        default:
            outColor = vec3(1.0, 0.0, 1.0); // magenta = debug error color
            break;
    }

    FragColor = vec4(outColor, 1.0);
    //FragColor = vec4(1.0,0.0,0.0, 1.0);
}

