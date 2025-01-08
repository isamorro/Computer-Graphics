// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A


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

PrismaRectangular::PrismaRectangular
(
    float altura,
    float anchura,
    float fondo
)
{

    ponerNombre("Retangulo que forma parte de la lámpara por mallas indexadas");

    float x = anchura/2;
    float y = altura;
    float z = fondo/2;
   

    vertices =
        {
            {x, 0.0, z}, 
            {x, y, z}, 
            {x, y, -z}, 
            {x, 0.0, -z}, 

            {-x, 0.0, z}, 
            {-x, y, z}, 
            {x, y, z}, 
            {x, 0.0, z}, 

            {-x, 0.0, -z}, 
            {-x, y, -z}, 
            {-x, y, z}, 
            {-x, 0.0, z}, 

            {x, 0.0, -z}, 
            {x, y, -z}, 
            {-x, y, -z}, 
            {-x, 0.0, -z}, 

            {x, y, z}, 
            {-x, y, z}, 
            {-x, y, -z}, 
            {x, y, -z}, 

            {x, 0.0, z}, 
            {-x, 0.0, z}, 
            {-x, 0.0, -z}, 
            {x, 0.0, -z} 
        };

    triangulos =
        {
            {0, 3, 2},
            {0, 2, 1},

            {4, 7, 6},
            {4, 6, 5},

            {8, 11, 10},
            {8, 10, 9},

            {12, 15, 14},
            {12, 14, 13},

            {16, 19, 18},
            {16, 18, 17},

            {20, 22, 23},
            {20, 21, 22}
        };

    // Asignamos valores a las tablas de coordenadas de texturas explícitamente
    // t3 diap 134

    for (int i=0; i < 6; i++){
        cc_tt_ver.push_back({0, 1});
        cc_tt_ver.push_back({1, 1});
        cc_tt_ver.push_back({1, 0});
        cc_tt_ver.push_back({0, 0});
    }

    calcularNormales();

}

/*****************************************************************************/

Lampara::Lampara()
{

    unsigned identificador = 1;
    
    ponerNombre("Lampara");
    NodoGrafoEscena *lampara = new NodoGrafoEscena();

//// MATERIALES Y TEXTURAS

    Textura* textMarmol = new Textura("text-marmol-negro.jpg");
    Material *matMarmol = new Material (textMarmol, 0.5, 0.6, 0.5, 50.0);

    // material difuso
    Material *matBrazoInferior = new Material (0.0, 1.0, 0.5, 50.0);

    TexturaXY *textMetalOscuro = new TexturaXY("text-metalico-oscuro.jpg");
    // material pseudo-especular
    Material *matMetal = new Material (textMetalOscuro, 0.0, 0.0, 1.0, 5.0);

    Textura *textPlasticoBlanco = new Textura ("text-plastico-blanco.jpg");
    Material *matBombilla = new Material(textPlasticoBlanco, 0.5, 0.6, 0.5, 50.0);

//// BASE de la lámpara

    NodoGrafoEscena *base = new NodoGrafoEscena();
    base->ponerNombre("Base de la lámpara");
    base->ponerIdentificador(identificador); // 1
    identificador++;

    base->agregar(matMarmol);
    base->agregar(translate(vec3(0.3, 0.0, -0.125)));
    base->agregar(new Base(4, 10, 0.5, 0.25));

//// BRAZO INFERIOR de la lámpara

    NodoGrafoEscena *brazo_inferior = new NodoGrafoEscena();
    brazo_inferior->ponerNombre("Brazo inferior de la lámpara");
    brazo_inferior->ponerIdentificador(identificador); // 2
    identificador++;

    brazo_inferior->agregar(matBrazoInferior);
    brazo_inferior->agregar(translate(vec3(0.275, 0.25, 0.125)));
    brazo_inferior->agregar(new PrismaRectangular(1, 0.25, 0.25));

//// BRAZO SUPERIOR de la lámpara

    NodoGrafoEscena *brazo_superior = new NodoGrafoEscena();
    brazo_superior->ponerNombre("Brazo superior de la lámpara");
    brazo_superior->ponerIdentificador(identificador); // 3
    identificador++;

    brazo_superior->agregar(matMetal);    
    brazo_superior->agregar(new PrismaRectangular(2, 0.25, 0.25));

//// BRAZO LATERAL de la lámpara

    NodoGrafoEscena *brazo_lateral = new NodoGrafoEscena();
    brazo_lateral->ponerNombre("Brazo lateral de la lámpara");
    brazo_lateral->ponerIdentificador(identificador); // 4
    identificador++;

    unsigned indice_traslacion_b_lat = brazo_lateral->agregar(translate(vec3{0.0, 0.0, 0.0}));  // 0
    
    brazo_lateral->agregar(translate(vec3(-0.45, 1.8, 0.0)));
    brazo_lateral->agregar(new PrismaRectangular(0.15, 0.65, 0.25));

//// CABEZAL de la lámpara

    NodoGrafoEscena *cabezal = new NodoGrafoEscena();
    cabezal->ponerNombre("Cabezal de la lámpara");
    cabezal->ponerIdentificador(identificador); // 5
    identificador++;

    unsigned indice_rotacion_cabezal = cabezal->agregar(rotate(0.0f, vec3(0.0, 1.0, 0.0)));     // 1
    
    cabezal->agregar(translate(vec3(-0.3, -0.5, 0.0)));
    cabezal->agregar(new Cabezal(0.4, 0.5, 0.4));

//// BOMBILLA DE LA LAMPARA

    NodoGrafoEscena *bombilla = new NodoGrafoEscena();
    bombilla->ponerNombre("Bombilla de la lámpara");
    bombilla->ponerIdentificador(identificador); // 6
    identificador++;

    unsigned indice_scale_bombilla = bombilla->agregar(scale(vec3(1.0, 1.0, 1.0)));             // 2

    bombilla->agregar(matBombilla);
    bombilla->agregar(translate(vec3(0.0, -0.1, 0.0)));
    bombilla->agregar(new PrismaRectangular(0.1, 0.1, 0.1));

//// INTERRUPTOR

    NodoGrafoEscena *interruptor = new NodoGrafoEscena();
    interruptor->ponerNombre("Interruptor de la lámpara");
    interruptor->ponerIdentificador(identificador); // 7
    identificador++;

    interruptor->agregar(matMarmol);
    interruptor->agregar(translate(vec3(-0.2, 0.8, 0.0)));
    interruptor->agregar(new PrismaRectangular(0.15, 0.15, 0.05));

//// LÁMPARA

    unsigned indice_traslacion_lampara = lampara->agregar(translate(vec3(0.0, 0.0, 0.0)));         // 3
   
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
    m_traslacion_lampara = lampara->leerPtrMatriz(indice_traslacion_lampara);                 

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
            *m_traslacion_lampara = translate(vec3(A + ((B-A)/2)*(1 + sin((M_PI/2)*t_sec)),0.0,0.0));

            break;
        }
    }
}