#shader vertex
#version 330 core

// Grid position are in xy clipped space
vec3 gridPlane[6] = vec3[](
    vec3(1, 1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
    vec3(-1, -1, 0), vec3(1, 1, 0), vec3(1, -1, 0)
);

// normal vertice projection
void main() {
    vec3 p = gridPlane[gl_VertexID].xyz;
    gl_Position = vec4(p, 1.0); // using directly the clipped coordinates}
}

#shader fragment
#version 330 core


out vec4 FragColor;


void main() {
    gl_FragColor = vec4(1.0f,0.0f,0.0f,1.0f);

}
