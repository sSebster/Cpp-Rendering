#version 410

layout(location = 0) in vec3 in_position;

in vec2 in_uv;
out vec2 uv;

uniform float aspect_ratio;
uniform float positionIG;
uniform mat4 mat;

out vec3 vertex_position;

void main()
{

    //vec2 position = in_position;
    //position.x += sin(positionIG)/2;
    //position.y += cos(positionIG)/2;
    //position.x /= aspect_ratio;

    vertex_position = in_position;

    gl_Position = vec4(vertex_position, 1.);
    gl_Position = mat * gl_Position;

    uv = in_uv;
}