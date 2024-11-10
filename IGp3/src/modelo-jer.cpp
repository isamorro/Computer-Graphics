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


// Forma un cilindro con ambas tapas

Base::Base
(
    const int num_verts_per,    // número de vertices del perfil original
    const unsigned nperfiles,   // número de perfiles
    float radio,                // tamaño del radio de la base
    float altura,               // altura de la base
    float punto_inf_izq_X,
    float punto_inf_izq_Y,
    float punto_inf_izq_Z

) 
{

    ponerNombre("Base de la lámpara por revolución");

    std::vector<glm::vec3> perfil = std::vector<glm::vec3>();

    perfil.push_back({punto_inf_izq_X, punto_inf_izq_Y, punto_inf_izq_Z});
    perfil.push_back({punto_inf_izq_X, punto_inf_izq_Y + altura, punto_inf_izq_Z});
    perfil.push_back({punto_inf_izq_X + radio, punto_inf_izq_Y + altura, punto_inf_izq_Z});
    perfil.push_back({punto_inf_izq_X + radio, punto_inf_izq_Y, punto_inf_izq_Z});

    inicializar(perfil, nperfiles);
}

Cabezal::Cabezal
(
    float ancho,                
    float altura,
    float fondo,
    float centro_X,
    float centro_Y,
    float centro_Z
)
{

    ponerNombre("Cabezal de la lámpara por revolución");

    
    vertices.push_back({centro_X, centro_Y, centro_Z});

    vertices.push_back({centro_X - ancho/2, centro_Y - altura, centro_Z + fondo/2});
    vertices.push_back({centro_X - ancho/2, centro_Y - altura, centro_Z - fondo/2});
    vertices.push_back({centro_X + ancho/2, centro_Y - altura, centro_Z - fondo/2});
    vertices.push_back({centro_X + ancho/2, centro_Y - altura, centro_Z + fondo/2});


    triangulos.push_back({0, 1, 2});
    triangulos.push_back({0, 2, 3});
    triangulos.push_back({0, 3, 4});
    triangulos.push_back({0, 1, 4});

    triangulos.push_back({1, 2, 3});
    triangulos.push_back({1, 3, 4});

}

// Forma los brazos de la lámpara por Mallas Indexadas

BrazoVertical::BrazoVertical
(
    float altura,
    float anchura,
    float extremo_inf_delantero_izq_X,
    float extremo_inf_delantero_izq_Y,
    float extremo_inf_delantero_izq_Z
)
{

    ponerNombre("Brazo de la lámpara por mallas indexadas");

   for (int i=0; i < 2; i++){
      float y = i*altura + extremo_inf_delantero_izq_Y;
      vertices.push_back({extremo_inf_delantero_izq_X, y, extremo_inf_delantero_izq_Z});
      vertices.push_back({extremo_inf_delantero_izq_X, y, extremo_inf_delantero_izq_Z - anchura});
      vertices.push_back({extremo_inf_delantero_izq_X + anchura, y, extremo_inf_delantero_izq_Z - anchura});
      vertices.push_back({extremo_inf_delantero_izq_X + anchura, y, extremo_inf_delantero_izq_Z});
   }

    // Base

    triangulos.push_back({0, 1, 2});
    triangulos.push_back({0, 2, 3});

    // Caras Laterales

    triangulos.push_back({0, 3, 7});
    triangulos.push_back({0, 4, 7});

    triangulos.push_back({0, 1, 4});
    triangulos.push_back({4, 5, 1});

    triangulos.push_back({1, 5, 2});
    triangulos.push_back({5, 6, 2});

    triangulos.push_back({2, 6, 3});
    triangulos.push_back({6, 7, 3});

    // Tapa

    triangulos.push_back({4, 5, 6});
    triangulos.push_back({4, 6, 7});

}

BrazoHorizontal::BrazoHorizontal
(
    float altura,
    float anchura,
    float fondo,
    float extremo_inf_delantero_izq_X,
    float extremo_inf_delantero_izq_Y,
    float extremo_inf_delantero_izq_Z
)
{

    ponerNombre("Brazo de la lámpara por mallas indexadas");

   for (int i=0; i < 2; i++){
      float y = i*altura + extremo_inf_delantero_izq_Y;
      vertices.push_back({extremo_inf_delantero_izq_X, y, extremo_inf_delantero_izq_Z});
      vertices.push_back({extremo_inf_delantero_izq_X, y, extremo_inf_delantero_izq_Z - fondo});
      vertices.push_back({extremo_inf_delantero_izq_X + anchura, y, extremo_inf_delantero_izq_Z - fondo});
      vertices.push_back({extremo_inf_delantero_izq_X + anchura, y, extremo_inf_delantero_izq_Z});
   }

    // Base

    triangulos.push_back({0, 1, 2});
    triangulos.push_back({0, 2, 3});

    // Caras Laterales

    triangulos.push_back({0, 3, 7});
    triangulos.push_back({0, 4, 7});

    triangulos.push_back({0, 1, 4});
    triangulos.push_back({4, 5, 1});

    triangulos.push_back({1, 5, 2});
    triangulos.push_back({5, 6, 2});

    triangulos.push_back({2, 6, 3});
    triangulos.push_back({6, 7, 3});

    // Tapa

    triangulos.push_back({4, 5, 6});
    triangulos.push_back({4, 6, 7});

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

        // ...
    
    base->agregar(new Base(4, 10, 0.5, 0.25, 0, 0, 0));


    //// BRAZO INFERIOR de la lámpara

    NodoGrafoEscena *brazo_inferior = new NodoGrafoEscena();
    brazo_inferior->ponerNombre("Brazo inferior de la lámpara");
    brazo_inferior->ponerIdentificador(identificador);
    identificador++;

        // ...
    
    brazo_inferior->agregar(new BrazoVertical(1, 0.25, 0.15, 0.25, 0.25));

    //// BRAZO SUPERIOR de la lámpara

    NodoGrafoEscena *brazo_superior = new NodoGrafoEscena();
    brazo_superior->ponerNombre("Brazo superior de la lámpara");
    brazo_superior->ponerIdentificador(identificador);
    identificador++;

        // ...
    
    brazo_superior->agregar(new BrazoVertical(0.8, 0.25, 0.15, 1.25, 0.25));

    //// BRAZO LATERAL de la lámpara

    NodoGrafoEscena *brazo_lateral = new NodoGrafoEscena();
    brazo_lateral->ponerNombre("Brazo lateral de la lámpara");
    brazo_lateral->ponerIdentificador(identificador);
    identificador++;

        // ...
    
    brazo_lateral->agregar(new BrazoHorizontal(0.15, 0.45, 0.25, -0.30, 1.9, 0.25));

    //// CABEZAL de la lámpara

    NodoGrafoEscena *cabezal = new NodoGrafoEscena();
    cabezal->ponerNombre("Cabezal de la lámpara");
    cabezal->ponerIdentificador(identificador);
    identificador++;

        // ...
    
    cabezal->agregar(new Cabezal(0.4, 0.5, 0.4, -0.3, 1.9, 0.125));

    //// LÁMPARA
    
   
    lampara->agregar(base);
    base->agregar(brazo_inferior);
    brazo_inferior->agregar(brazo_superior);
    brazo_superior->agregar(brazo_lateral);
    brazo_lateral->agregar(cabezal);
    
    agregar(lampara);

}

