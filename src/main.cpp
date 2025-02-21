#include <fstream>
#include <iostream>
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

#include "opengl-framework/opengl-framework.hpp" // Inclue la librairie qui va nous servir à faire du rendu

int main()
{
    //Debug
    //std::ifstream vShader;
    //std::string vertexCode;
    //vShader.open(".\\res\\vertex.glsl");
    //std::stringstream vertexStream;
    //vertexStream << vShader.rdbuf();
    //vShader.close();
    //vertexCode = vertexStream.str();
    //std::cout << "Debut\n"<< vertexCode << "\nFin" << std::endl;

    //return 0;
    //debug

    // Initialisation
    gl::init("Rendering couscous"); // On crée une fenêtre et on choisit son nom
    gl::maximize_window(); // On peut la maximiser si on veut

    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE); // On peut configurer l'équation qui mélange deux couleurs, comme pour faire différents blend mode dans Photoshop. Cette équation-ci donne le blending "normal" entre pixels transparents.

    auto camera = gl::Camera{};
    gl::set_events_callbacks({camera.events_callbacks()});

    auto const shader = gl::Shader{{
        .vertex   = gl::ShaderSource::File{"res/vertex.glsl"},
        .fragment = gl::ShaderSource::File{"res/fragment.glsl"},
    }};

    auto const triangle_mesh = gl::Mesh{{
        .vertex_buffers = {{
            .layout = {gl::VertexAttribute::Position2D{0 /*Index de l'attribut dans le shader, on en reparle juste après*/}},
            .data   = {
                -1.f, -1.f, // Position2D du 1er sommet
                +1.f, -1.f, // Position2D du 2ème sommet
                 0.f, +1.f  // Position2D du 3ème sommet
            },
        }},
    }};

    auto const rectangle_mesh = gl::Mesh{{
        .vertex_buffers = {{
            .layout = {gl::VertexAttribute::Position3D{0}},
            .data   = {
                -0.5f, -0.5f, -0.5, // Position3D du 1er sommet
                +0.5f, -0.5f, -0.5f // Position3D du 2ème sommet
                +0.5f, +0.5f, +0.5f// Position3D du 3ème sommet
                -0.5f, +0.5f, +0.5f  // Position3D du 4ème sommet
            },
        }},
        .index_buffer   = {
            0, 1, 2, // Indices du premier triangle : on utilise le 1er, 2ème et 3ème sommet
            0, 2, 3  // Indices du deuxième triangle : on utilise le 1er, 3ème et 4ème sommet
        },
    }};

    // Rendu à chaque frame
    while (gl::window_is_open())
    {
        glClearColor(0.f, 0.f, 1.f, 1.f); // Choisis la couleur à utiliser. Les paramètres sont R, G, B, A avec des valeurs qui vont de 0 à 1
        glClear(GL_COLOR_BUFFER_BIT); // Exécute concrètement l'action d'appliquer sur tout l'écran la couleur choisie au-dessus

        shader.bind(); // On a besoin qu'un shader soit bind (i.e. "actif") avant de draw(). On en reparle dans la section d'après.

        shader.set_uniform("aspect_ratio", gl::framebuffer_aspect_ratio());
        shader.set_uniform("positionIG", gl::time_in_seconds());

        rectangle_mesh.draw(); // C'est ce qu'on appelle un "draw call" : on envoie l'instruction à la carte graphique de dessiner notre mesh.

        glm::mat4 const view_matrix = camera.view_matrix();
        gl::set_events_callbacks({
            camera.events_callbacks(),
            {
                .on_mouse_pressed = [&](gl::MousePressedEvent const& e) {
                    std::cout << "Mouse pressed at " << e.position.x << " " << e.position.y << '\n';
                },
            },
        });

        glm::mat4 const projection_matrix = glm::infinitePerspective(glm::radians(45.f), gl::framebuffer_aspect_ratio(), 0.001f);
        glm::mat4 const rotation = glm::rotate(glm::mat4{1.f}, gl::time_in_seconds() /*angle de la rotation*/, glm::vec3{0.f, 0.f, 1.f} /* axe autour duquel on tourne */);
        glm::mat4 const translation = glm::translate(glm::mat4{1.f}, glm::vec3{0.f, 1.f, 0.f} /* déplacement */);

        glm::mat4 const model_matrix = rotation*translation;
        shader.set_uniform("mat",projection_matrix*view_matrix*model_matrix);
    }

}