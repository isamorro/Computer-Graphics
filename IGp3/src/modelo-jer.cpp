
#include "ig-aux.h"
#include"modelo-jer.h"



// Construcción de la base

Base::Base
(
    const int num_verts_per,    // número de vertices del perfil original
    const unsigned nperfiles,   // número de perfiles
    float radio,
    float altura
) 
{

    ponerNombre("Base de la lámpara por revolución");

    std::vector<glm::vec3> perfil = std::vector<glm::vec3>();


    for (int i = 0; i < num_verts_per/2; i++){

        float y = i*(altura / ( (num_verts_per/2) - 1));
        perfil.push_back(glm::vec3(0.0, y, 0.0));

    }

    for (int i = num_verts_per/2; i < num_verts_per; i++){

        float x = i*(radio / ((num_verts_per/2) - 1));
        perfil.push_back(glm::vec3(X, altura, 0.0));

    }

    inicializar(perfil, nperfiles);
}

Lampara::Lampara()
{
    
}