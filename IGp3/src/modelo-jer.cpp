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

/*****************************************************************************/

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

    perfil.push_back({0.0, 0.0, 0.0});
    perfil.push_back({0.0, altura, 0.0});
    perfil.push_back({ radio, altura, 0.0});
    perfil.push_back({ radio, 0.0, 0.0});

    inicializar(perfil, nperfiles);
}


/*****************************************************************************/

Cabezal::Cabezal
(
    float ancho,                
    float altura,
    float fondo
)
{

    ponerNombre("Cabezal de la lámpara por revolución");

    
    vertices.push_back({0.0, altura, 0.0});

    vertices.push_back({-ancho/2,  0.0, fondo/2});
    vertices.push_back({-ancho/2,  0.0, - fondo/2});
    vertices.push_back({ancho/2,  0.0,  - fondo/2});
    vertices.push_back({ancho/2,  0.0,  fondo/2});


    triangulos.push_back({0, 1, 2});
    triangulos.push_back({0, 2, 3});
    triangulos.push_back({0, 3, 4});
    triangulos.push_back({0, 1, 4});

    triangulos.push_back({1, 2, 3});
    triangulos.push_back({1, 3, 4});

}


/*****************************************************************************/

Rectangulo::Rectangulo
(
    float altura,
    float anchura,
    float fondo
)
{

    ponerNombre("Retangulo que forma parte de la lámpara por mallas indexadas");

   
    vertices.push_back({-anchura/2, 0.0, fondo/2});
    vertices.push_back({-anchura/2, 0.0, -fondo/2});
    vertices.push_back({anchura/2, 0.0, -fondo/2});
    vertices.push_back({anchura/2, 0.0, fondo/2});
   
    vertices.push_back({-anchura/2, altura, fondo/2});
    vertices.push_back({-anchura/2, altura, -fondo/2});
    vertices.push_back({anchura/2, altura, -fondo/2});
    vertices.push_back({anchura/2, altura, fondo/2});

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

/*****************************************************************************/

Lampara::Lampara()
{


    unsigned identificador = 1;
    
    ponerNombre("Lampara");
    NodoGrafoEscena *lampara = new NodoGrafoEscena();


//// BASE de la lámpara

    NodoGrafoEscena *base = new NodoGrafoEscena();
    base->ponerNombre("Base de la lámpara");
    base->ponerIdentificador(identificador);
    identificador++;

    base->ponerColor({0.4, 0.2, 0.0}); // marrón oscuro
    base->agregar(translate(vec3(0.3, 0.0, -0.125)));
    base->agregar(new Base(4, 10, 0.5, 0.25));


//// BRAZO INFERIOR de la lámpara

    NodoGrafoEscena *brazo_inferior = new NodoGrafoEscena();
    brazo_inferior->ponerNombre("Brazo inferior de la lámpara");
    brazo_inferior->ponerIdentificador(identificador);
    identificador++;

    brazo_inferior->ponerColor({0.9, 0.7, 0.4}); // marrón claro
    brazo_inferior->agregar(translate(vec3(0.275, 0.25, 0.125)));
    brazo_inferior->agregar(new Rectangulo(1, 0.25, 0.25));

//// BRAZO SUPERIOR de la lámpara

    NodoGrafoEscena *brazo_superior = new NodoGrafoEscena();
    brazo_superior->ponerNombre("Brazo superior de la lámpara");
    brazo_superior->ponerIdentificador(identificador);
    identificador++;

    brazo_superior->ponerColor({0.9, 0.7, 0.4}); // marrón claro
    brazo_superior->agregar(new Rectangulo(2, 0.25, 0.25));

//// BRAZO LATERAL de la lámpara

    NodoGrafoEscena *brazo_lateral = new NodoGrafoEscena();
    brazo_lateral->ponerNombre("Brazo lateral de la lámpara");
    brazo_lateral->ponerIdentificador(identificador);
    identificador++;

    unsigned indice_traslacion_b_lat = brazo_lateral->agregar(translate(vec3{0.0, 0.0, 0.0}));  // 0
    
    brazo_lateral->ponerColor({0.9, 0.7, 0.4}); // marrón claro
    brazo_lateral->agregar(translate(vec3(-0.45, 1.8, 0.0)));
    brazo_lateral->agregar(new Rectangulo(0.15, 0.65, 0.25));

//// CABEZAL de la lámpara

    NodoGrafoEscena *cabezal = new NodoGrafoEscena();
    cabezal->ponerNombre("Cabezal de la lámpara");
    cabezal->ponerIdentificador(identificador);
    identificador++;

    unsigned indice_rotacion_cabezal = cabezal->agregar(rotate(0.0f, vec3(0.0, 1.0, 0.0)));     // 1
    
    cabezal->ponerColor({0.4, 0.2, 0.0}); // marron oscuro
    cabezal->agregar(translate(vec3(-0.3, -0.5, 0.0)));
    cabezal->agregar(new Cabezal(0.4, 0.5, 0.4));

//// BOMBILLA DE LA LAMPARA

    NodoGrafoEscena *bombilla = new NodoGrafoEscena();
    bombilla->ponerNombre("Bombilla de la lámpara");
    bombilla->ponerIdentificador(identificador);
    identificador++;

    unsigned indice_scale_bombilla = bombilla->agregar(scale(vec3(1.0, 1.0, 1.0)));             // 2

    bombilla->ponerColor({1.0, 1.0, 0.0}); // amarillo
    bombilla->agregar(translate(vec3(0.0, -0.1, 0.0)));
    bombilla->agregar(new Rectangulo(0.1, 0.1, 0.1));


//// INTERRUPTOR

    NodoGrafoEscena *interruptor = new NodoGrafoEscena();
    interruptor->ponerNombre("Interruptor de la lámpara");
    interruptor->ponerIdentificador(identificador);
    identificador++;

    interruptor->ponerColor({0.4, 0.2, 0.0});
    interruptor->agregar(translate(vec3(-0.2, 0.8, 0.0)));
    interruptor->agregar(new Rectangulo(0.15, 0.15, 0.05));



//// LÁMPARA

    unsigned indice_traslacion_base = lampara->agregar(translate(vec3(0.0, 0.0, 0.0)));         // 3
   
    cabezal->agregar(bombilla);
    brazo_lateral->agregar(cabezal);
    brazo_superior->agregar(brazo_lateral);
    brazo_inferior->agregar(brazo_superior);
    brazo_inferior->agregar(interruptor);
    base->agregar(brazo_inferior);
    lampara->agregar(base);
    

    m_traslacion_brazo_lateral = brazo_lateral->leerPtrMatriz(indice_traslacion_b_lat); 
    m_rotacion_cabezal = cabezal->leerPtrMatriz(indice_rotacion_cabezal);               
    m_scale_bombilla = bombilla->leerPtrMatriz(indice_scale_bombilla);
    agregar(lampara);
    m_traslacion_base = lampara->leerPtrMatriz(indice_traslacion_base);                 

}


unsigned Lampara::leerNumParametros() const
{
    return 4;
}

void Lampara::actualizarEstadoParametro
(
    const unsigned iParam, 
    const float t_sec    
)
{
    switch (iParam) 
    {
     
        case 0: {

            float A = -0.5;
            float B = 0.0;
            *m_traslacion_brazo_lateral = translate(vec3(0.0, A + ((B-A)/2)*(1 + sin((M_PI/2)*t_sec)), 0.0));
        
            break;
        }


        case 1: {            

            float angulo = 2*(M_PI/4)*t_sec;
            *m_rotacion_cabezal = translate(vec3(-0.3, -0.5, 0.0))*rotate(angulo, vec3(0.0, 1.0, 0.0))*translate(vec3(0.3, 0.5, 0.0));

            break;
        }

        case 2: {

            float A  = 0.75;
            float B = 1.4;
            float escala = A + ((B-A)/2)*( 1 + sin((M_PI/2)*t_sec));
            *m_scale_bombilla = scale (vec3(escala, escala, escala));

            break;
        }

        case 3:{
        
            float A = 0.0;
            float B = 1.0;
            *m_traslacion_base = translate(vec3(A + ((B-A)/2)*(1 + sin((M_PI/2)*t_sec)),0.0,0.0));

            break;
        }
    }
}