#version 410

layout(location = 0) in vec2 in_position;

uniform float aspect_ratio;

void main()
{
    vec2 position = in_position;
    position +=0.4;
    position.x /= aspect_ratio;


    gl_Position = vec4(position, 0., 1.); // Ici on utilise maintenant `position` et non plus `in_position`
}