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

layout(rgba8, binding = 0) uniform image2D pixelData;

out vec4 FragColor;

void main() {
    ivec2 texelCoord = ivec2(gl_FragCoord.xy);

    vec4 data = imageLoad(pixelData, texelCoord);

    data.r += 0.01; 
    if(data.r > 1.0) data.r = 0.0;

    imageStore(pixelData, texelCoord, data);

    FragColor = vec4(data.r, 0.0f, 0.0f, 1.0f);
    //float r = gl_FragCoord.x/width * 10;
    //FragColor = vec4(round(r)/10.0f,0.0f,0.0f,1.0f);
    //FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);

}
