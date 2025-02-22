#version 410

out vec4 out_color;
in vec2 vertex_position;
uniform sampler2D my_texture;

in vec2 uv;

void main()
{
    out_color = vec4(1.,1.,0.,1.);
    //out_color = vec4(vertex_position, 1.);
    //out_color = vec4(uv.x, uv.y, 0., 1.); //debug uv

    vec4 texture_color = texture(my_texture, uv);
    out_color = texture_color;
}