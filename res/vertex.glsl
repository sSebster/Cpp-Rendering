#version 410

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normale;

uniform float aspect_ratio;
uniform float positionIG;
uniform mat4 mat;

out vec3 vertex_position;
out vec3 vertex_normale;
out vec2 vertex_uv;

void main()
{

    //vec2 position = in_position;
    //position.x += sin(positionIG)/2;
    //position.y += cos(positionIG)/2;
    //position.x /= aspect_ratio;

    vertex_position = in_position;
    vertex_normale = in_normale;
    vertex_uv = in_uv;

    gl_Position = mat * vec4(vertex_position, 1.);
}