#version 410

out vec4 out_color;
in vec3 vertex_position;
in vec3 vertex_normale;
in vec2 vertex_uv;
//uniform vec3 light_direction;
uniform sampler2D bato_texture;

void main()
{
    vec4 texture_color = texture(bato_texture, vertex_uv);

    vec3 light_direction = vec3(0.,0.,-1.);
    float light_intensity = max(-dot(vertex_normale,light_direction), 0.);
    out_color = vec4(texture_color.rgb * light_intensity, texture_color.a);


    //out_color = vec4(vertex_uv.x, vertex_uv.y, 0., 1.);
    //vec4(vec3(light_intensity), 1.);




 // out_color = vec4(1.,1.,0.,1.);
 // out_color = vec4(vertex_position, 1.);

 // out_color = vec4(0.25,0.75,0.25,0.5); //bateau fantome hehehehehehehe
 // out_color = vec4(vertex_normale, 1.);

 // //const vec3 light_direction = normalize(vec3(0.2, 0.3, -1.));

 // //out_color = vec4(vec3(0.5,0.5,0.5)*(dot(vertex_normale,light_direction)+0.3), 1.);
 // out_color = vec4(0.9,0.,0.,1.);

 // out_color = out_color*dot(out_color,light_direction);
}