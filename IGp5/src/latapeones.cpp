// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A

#include "latapeones.h"

using namespace glm;
using namespace std;

Lata::Lata()
{

    NodoGrafoEscena *objeto = new NodoGrafoEscena();
    unsigned int identificador = 1;

// Perfil parte central

    NodoGrafoEscena *perfil = new NodoGrafoEscena();
    perfil->ponerIdentificador(identificador);
    identificador++;
    Textura* lataCoke = new Textura("lata-coke.jpg");
    // material difuso-especular
    Material *materialPerfil = new Material (lataCoke, 0.75, 0.65, 0.25, 50.0);
    perfil->agregar(materialPerfil);
    perfil->agregar(new MallaRevolPLY("lata-pcue.ply", 50));

// Tapa superior metálica
    NodoGrafoEscena *tapa = new NodoGrafoEscena();
    tapa->ponerIdentificador(identificador);
    identificador++;
    // sin textura, material difuso-especular
    Material *materialTapa = new Material(0.35, 0.45, 0.25, 0.50);
    tapa->agregar(materialTapa);
    tapa->agregar(new MallaRevolPLY("lata-psup.ply", 50));

// Base inferior metálica
    NodoGrafoEscena *base = new NodoGrafoEscena();
    base->ponerIdentificador(identificador);
    // mismo material que tapa superior metálica
    base->agregar(materialTapa);
    base->agregar(new MallaRevolPLY("lata-pinf.ply", 50));

    objeto->agregar(perfil);
    objeto->agregar(tapa);
    objeto->agregar(base);
    agregar(objeto);
}

LataPeones::LataPeones(){


    NodoGrafoEscena *objeto = new NodoGrafoEscena();
    MallaRevolPLY *mallaPeon = new MallaRevolPLY("peon.ply", 50);
    unsigned int identificador = 1;

// PEONES

// Peón Madera
    NodoGrafoEscena *peonMadera = new NodoGrafoEscena();
    peonMadera->ponerNombre("Peón de madera");
    peonMadera->ponerIdentificador(identificador);
    identificador++;
    // textura madera difuso-especular
    TexturaXY *textMadera = new TexturaXY("text-madera.jpg");
    peonMadera->agregar(translate(vec3(0.0, 0.2, 1.0)));
    peonMadera->agregar(scale(vec3(0.15, 0.15, 0.15)));
    peonMadera->agregar(new Material (textMadera, 0.5, 0.6, 0.5, 50.0));
    peonMadera->agregar(mallaPeon);

// Peón Blanco
    NodoGrafoEscena *peonBlanco = new NodoGrafoEscena();
    peonBlanco->ponerNombre("Peón de color blanco");
    peonBlanco->ponerIdentificador(identificador);
    identificador++;
    peonBlanco->agregar(translate(vec3(0.4, 0.2, 1.0)));
    peonBlanco->agregar(scale(vec3(0.15, 0.15, 0.15)));
    // difuso de color blanco
    peonBlanco->agregar(new Material (0.5, 0.2, 0.5, 5.0));
    peonBlanco->agregar(mallaPeon);

// Peón Negro
    NodoGrafoEscena *peonNegro = new NodoGrafoEscena();
    peonNegro->ponerNombre("Peón de color negro");
    peonNegro->ponerIdentificador(identificador);
    identificador++;
    peonNegro->agregar(translate(vec3(0.8, 0.2, 1.0)));
    peonNegro->agregar(scale(vec3(0.15, 0.15, 0.15)));
    // especular sin apenas reflectividad difusa
    peonNegro->agregar(new Material (0.01, 0.2, 0.5, 50.0));
    peonNegro->agregar(mallaPeon);

// LATA

    Lata *lata = new Lata();
    lata->ponerNombre("lata");
    lata->ponerIdentificador(identificador);
    // lata->agregar(scale(vec3(1.2, 1.2, 1.2)));

// OBJETO

    objeto->agregar(peonMadera);
    objeto->agregar(peonBlanco);
    objeto->agregar(peonNegro);
    objeto->agregar(lata);

    agregar(objeto);
}