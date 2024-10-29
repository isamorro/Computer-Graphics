
#include "ig-aux.h"
#include"modelo-jer.h"



// Forma un cilindro con tapa arriba

Base::Base
(
    const int num_verts_per,    // número de vertices del perfil original
    const unsigned nperfiles,   // número de perfiles
    float radio,                // tamaño del radio de la base
    float altura                // altura de la base
) 
{

    ponerNombre("Base de la lámpara por revolución");

    std::vector<glm::vec3> perfil = std::vector<glm::vec3>();

    // n / 2 vértices para la altura
    for (int i = 0; i < num_verts_per/2; i++){

        float y = i*(altura / ( (num_verts_per/2) - 1));
        perfil.push_back(glm::vec3(0.0, y, 0.0));

    }

    // n / 2 vértices del (0, altura , 0 ) al (radio, altura, 0)
    for (int i = num_verts_per/2; i < num_verts_per; i++){

        float x = i*(radio / ((num_verts_per/2) - 1));
        perfil.push_back(glm::vec3(X, altura, 0.0));

    }

    inicializar(perfil, nperfiles);
}

// Forma una semiesfera por revolución
Cabezal::Cabezal
(
    const int num_verts_per,    // número de vértices del perfil original
    const unsigned nperfiles,   // número de perfiles
    float radio,                // radio del cabeza
    float centro
)
{

    ponerNombre("Cabezal de la lámpara por revolución");

    std::vector<glm::vec3> perfil = std::vector<glm::vec3>();

    perfil.push_back(glm::vec3(0.0, radio, 0.0));

    for(int i=0; i < num_verts_per; i++){

        float angulo = ((i+1)*M_PI) / num_verts_per;

        std::vector<std::vector<float>> matriz_rotacion = 
        {   
            {cos(angulo), -sin(angulo), 0},
            {sin(angulo), cos(angulo), 0},
            {0, 0, 1},
        };

        glm::vec3 vertice = {
            matriz_rotacion[0][0] * 0.0 + matriz_rotacion[0][1] * -radio + matriz_rotacion[0][2] * 0.0,
            matriz_rotacion[1][0] * 0.0 + matriz_rotacion[1][1] * -radio + matriz_rotacion[1][2] * 0.0,
            matriz_rotacion[2][0] * 0.0 + matriz_rotacion[2][1] * -radio + matriz_rotacion[2][2] * 0.0,
        };

        perfil.push_back(vertice);
    }

    inicializar(perfil, nperfiles);

}


Lampara::Lampara()
{
    
}