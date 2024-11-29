// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A

#include "examen-ec-p123.h"

Ejercicio1::Ejercicio1() 
: MallaInd ("Ejercicio 1 examen")
{

    // Vértices

    vertices.push_back(vec3(0.0, 0.0, 0.0));    
    vertices.push_back(vec3(0.0, 0.0, -0.5));
    vertices.push_back(vec3(1.0, 0.0, 0.0));
    vertices.push_back(vec3(1.0, 0.0, -0.5));
    vertices.push_back(vec3(1.25, 0.0, 0.0));


    vertices.push_back(vec3(1.25, 0.25, -0.25));
    vertices.push_back(vec3(1.5, 0.25, -0.25));
    vertices.push_back(vec3(1.75, 0.25, -0.25));
    vertices.push_back(vec3(2.0, 0.25, -0.25));

    vertices.push_back(vec3(1.5, 0.0, 0.0));
    vertices.push_back(vec3(1.75, 0.0, 0.0));
    vertices.push_back(vec3(2.0, 0.0, 0.0));

    // Triángulos

    triangulos.push_back({0, 1, 2});
    triangulos.push_back({1, 2, 3});
    triangulos.push_back({2, 3, 4});
    triangulos.push_back({3, 4, 5});
    triangulos.push_back({4, 5, 9});
    triangulos.push_back({5, 6, 9});
    triangulos.push_back({6, 9, 10});
    triangulos.push_back({6, 7, 10});
    triangulos.push_back({7, 10 , 11});
    triangulos.push_back({7, 8 , 11});

    // colores 

    unsigned tam = vertices.size();
    for (int i = 0; i < tam; i++){
        if (i < 4) col_ver.push_back({0.2, 0.2, 0.2});
        else col_ver.push_back({1.0, 1.0, 1.0});

    }
    
}

Ejercicio2::Ejercicio2 ( unsigned n ) 
: MallaInd ("Ejercicio 2")
{

    assert (n >= 1);

    float angulo = (2*M_PI) / n;


    // Vértices compartidos entre todas las figuras
    vertices.push_back(vec3(0.0, 0.0, 0.0));    // 0
    vertices.push_back(vec3(0.0, 0.0, -0.5));   // 1


    for (int i=0; i < n; i++){

        vertices.push_back(vec3(1.0*cos(float(1.0)*angulo*2*i), 0.0, 0.0));
        vertices.push_back(vec3(1.0*cos(float(1.0)*angulo*2*i), 0.0, -0.5));

        vertices.push_back(vec3(1.25*cos(float(1.25)*angulo*2*i), 0.0, 0.0));

        vertices.push_back(vec3(1.25*cos(float(1.25)*angulo*2*i), 0.25 + 1.25*sin(1.25*angulo*2*i), -0.25));
        vertices.push_back(vec3(1.5*cos(float(1.5)*angulo*2*i), 0.25 + 1.5*sin(1.5*angulo*2*i), -0.25));
        vertices.push_back(vec3(1.75*cos(float(1.75)*angulo*2*i), 0.25 + 1.75*sin(1.75*angulo*2*i), -0.25));
        vertices.push_back(vec3(2.0*cos(float(2.0)*angulo*2*i), 0.25 + 2.0*sin(2.0*angulo*2*i), -0.25));

        vertices.push_back(vec3(1.5*cos(float(1.5)*angulo*2*i), 0.0, 0.0));
        vertices.push_back(vec3(1.75*cos(float(1.75)*angulo*2*i), 0.0, 0.0));
        vertices.push_back(vec3(2.0*cos(float(2.0)*angulo*2*i), 0.0, 0.0));

    }

    int j = 0;
    for (int i=0; i < n; i++){

        triangulos.push_back({0, 1, 2 + j});
        triangulos.push_back({1, 2 + j, 3 + j});
        triangulos.push_back({2 + j, 3 + j, 4 + j});
        triangulos.push_back({3 + j, 4 + j, 5 + j});
        triangulos.push_back({4 + j, 5 + j, 9 + j});
        triangulos.push_back({5 + j, 6 + j, 9 + j});
        triangulos.push_back({6 + j, 9 + j, 10 + j});
        triangulos.push_back({6 + j, 7 + j, 10 + j});
        triangulos.push_back({7 + j, 10 + j , 11 + j});
        triangulos.push_back({7 + j, 8 + j , 11 + j});

        j+= 10;

    }

}

Ejercicio3::Ejercicio3
(
    float h,
    float w
)
{

    assert (w > 1);
    assert (h > 0 and h < 0.3);

    unsigned int identificador = 1;
    float escalaPrismaInferiorW = w / 2.0f;
    float escalaPrismaInferiorH = h / 2.0f;
    float escalaPrismaSuperior = 0.3 / 2.0f;

    CuboColores *cubo = new CuboColores ();
    ponerNombre("Ejercicio 3");
    NodoGrafoEscena *objeto = new NodoGrafoEscena();

    NodoGrafoEscena *prismaInferior = new NodoGrafoEscena();
    prismaInferior->ponerNombre("prisma inferior");
    prismaInferior->ponerIdentificador(identificador);
    identificador++;
    unsigned int ind_escala = prismaInferior->agregar(scale(vec3(1.0, 1.0, 1.0)));
    prismaInferior->agregar(scale(vec3(escalaPrismaInferiorW, escalaPrismaInferiorH, escalaPrismaInferiorW)));
    prismaInferior->agregar(cubo);
    
    NodoGrafoEscena *prismaSuperior = new NodoGrafoEscena();
    prismaSuperior->ponerNombre("prisma superior");
    prismaSuperior->ponerIdentificador(identificador);
    identificador++;
    unsigned int ind_rot = prismaSuperior->agregar(rotate(0.0f, vec3(0.0, 1.0, 0.0)));
    prismaSuperior->agregar(scale(vec3(escalaPrismaSuperior, escalaPrismaSuperior, escalaPrismaSuperior)));
    prismaSuperior->agregar(translate(vec3(w - 0.15, h + 0.15 , 0.0)));
    prismaSuperior->agregar(cubo);

    objeto->agregar(prismaSuperior);
    objeto->agregar(prismaInferior);

    m_escala = prismaInferior->leerPtrMatriz(ind_escala);
    m_rot = prismaSuperior->leerPtrMatriz(ind_rot);

    agregar(objeto);

}

unsigned Ejercicio3::leerNumParametros() const {
   return 2;
} 

void Ejercicio3::actualizarEstadoParametro
(
   const unsigned iParam,
   const float t_sec
)
{
   switch (iParam)
   {

    case 0: {
        
        float A  = 0.75;
        float B = 1.4;
        float escala = A + ((B-A)/2)*( 1 + sin((M_PI/2)*t_sec));
        *m_escala = scale (vec3(1.0, escala, 1.0));
        break;

    }

    case 1: {

        float angulo = 2*(M_PI/4)*t_sec;
        *m_rot = rotate(angulo, vec3(0.0, 1.0, 0.0));
        break;
    }

   }
}