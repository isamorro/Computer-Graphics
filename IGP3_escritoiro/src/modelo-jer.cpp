// *********************************************************************
// ** 
// ** Isabel Morro Tabares, 79095945A
// ** Curso 2024/2025
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** Implementación de la clases necesarias para crear el objeto jerárquico
// *********************************************************************


#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "malla-revol.h"
#include "modelo-jer.h"


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
        perfil.push_back(glm::vec3(x, altura, 0.0));

    }

    inicializar(perfil, nperfiles);
}

// Forma una semiesfera por revolución
Cabezal::Cabezal
(
    const int num_verts_per,    // número de vértices del perfil original
    const unsigned nperfiles,   // número de perfiles
    float radio,                // radio del cabeza
    float centro_X,
    float centro_Y,
    float centro_Z
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

    // Reescalamos a la posición que queremos 

    for (size_t i=0; i < vertices.size(); i++){
        vertices[i].x += centro_X;
        vertices[i].y += centro_Y;
        vertices[i].z += centro_Z;
    }

    inicializar(perfil, nperfiles);

}

// Forma los brazos de la lámpara por Mallas Indexadas

Brazo::Brazo
(
    float altura,
    float anchura,
    float extremo_inf_delantero_izq_X,
    float extremo_inf_delantero_izq_Z
)
{

    ponerNombre("Brazo de la lámpara por mallas indexadas");

   for (int i=0; i < 2; i++){
      float y = i*altura;
      vertices.push_back({extremo_inf_delantero_izq_X, y, extremo_inf_delantero_izq_Z});
      vertices.push_back({extremo_inf_delantero_izq_X, y, extremo_inf_delantero_izq_Z - anchura});
      vertices.push_back({extremo_inf_delantero_izq_X + anchura, y, extremo_inf_delantero_izq_Z - anchura});
      vertices.push_back({extremo_inf_delantero_izq_X + anchura, y, extremo_inf_delantero_izq_Z});
   }

    // Base

    triangulos.push_back({1, 2, 3});
    triangulos.push_back({1, 3, 4});

    // Caras Laterales

    triangulos.push_back({1, 4, 8});
    triangulos.push_back({1, 5, 8});

    triangulos.push_back({1, 2, 5});
    triangulos.push_back({5, 6, 2});

    triangulos.push_back({2, 6, 3});
    triangulos.push_back({6, 7, 3});

    triangulos.push_back({3, 7, 4});
    triangulos.push_back({7, 8, 4});

    // Tapa

    triangulos.push_back({5, 6, 7});
    triangulos.push_back({5, 7, 8});

}

Lampara::Lampara()
{

    // identificador
    unsigned identificador = 1;
    
    ponerNombre("Lampara");
    NodoGrafoEscena *lampara = new NodoGrafoEscena();


    //// BASE de la lámpara

    NodoGrafoEscena *base = new NodoGrafoEscena();
    base->ponerNombre("Base de la lámpara");
    base->ponerIdentificador(identificador);
    identificador++;

        // rotaciones etc etc
    
    base->agregar(new Base(100, 10, 0.5, 0.5));

    //// BRAZO INFERIOR de la lámpara

    NodoGrafoEscena *brazo_inferior = new NodoGrafoEscena();
    brazo_inferior->ponerNombre("Brazo inferior de la lámpara");
    brazo_inferior->ponerIdentificador(identificador);
    identificador++;

        // ...
    
    brazo_inferior->agregar(new Brazo(0.75, 0.25, 0.65, 0.25));

    //// BRAZO SUPERIOR de la lámpara

    NodoGrafoEscena *brazo_superior = new NodoGrafoEscena();
    brazo_superior->ponerNombre("Brazo superior de la lámpara");
    brazo_superior->ponerIdentificador(identificador);
    identificador++;

        // ...
    
    brazo_superior->agregar(new Brazo(0.5, 0.25, 0.65, 1.25));

    //// CABEZAL de la lámpara

    NodoGrafoEscena *cabezal = new NodoGrafoEscena();
    cabezal->ponerNombre("Cabezal de la lámpara");
    cabezal->ponerIdentificador(identificador);
    identificador++;

        // ...
    
    cabezal->agregar(new Cabezal(100, 10, 0.3, 0.35, 1.75, 0.125));

    //// LÁMPARA

    lampara->agregar(base);
    agregar(lampara);

}

