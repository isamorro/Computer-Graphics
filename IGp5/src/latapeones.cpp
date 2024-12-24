// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A

#include "latapeones.h"

using namespace glm;
using namespace std;

Peon::Peon(int nperfiles) {
    pm_tras = leerPtrMatriz(agregar(translate(vec3(0.0, 0.0, 0.0))));
    agregar(new MallaRevolPLY("peon.ply", nperfiles));
}

bool Peon::cuandoClick(const glm::vec3 & centro_oc) {
    *pm_tras = translate(vec3(0.0, 0.0, 1.0));
    return true;
}

Lata::Lata(const std::string &nombre_archivo)
{

    NodoGrafoEscena *objeto = new NodoGrafoEscena();

// Perfil parte central

    NodoGrafoEscena *perfil = new NodoGrafoEscena();
    // perfil->ponerIdentificador(identificador); // 1
    // identificador++;
    Textura* lataCoke = new Textura(nombre_archivo);
    // material difuso-especular
    Material *materialPerfil = new Material (lataCoke, 0.75, 0.65, 0.25, 50.0);
    perfil->agregar(materialPerfil);
    perfil->agregar(new MallaRevolPLY("lata-pcue.ply", 50));

// Tapa superior metálica
    NodoGrafoEscena *tapa = new NodoGrafoEscena();
    // tapa->ponerIdentificador(identificador);
    // identificador++; // 2
    // sin textura, material difuso-especular
    Material *materialTapa = new Material(0.35, 0.45, 0.25, 0.50);
    tapa->agregar(materialTapa);
    tapa->agregar(new MallaRevolPLY("lata-psup.ply", 50));

// Base inferior metálica
    NodoGrafoEscena *base = new NodoGrafoEscena();
    // base->ponerIdentificador(identificador); // 3
    // mismo material que tapa superior metálica
    base->agregar(materialTapa);
    base->agregar(new MallaRevolPLY("lata-pinf.ply", 50));

    objeto->agregar(perfil);
    objeto->agregar(tapa);
    objeto->agregar(base);
    agregar(objeto);
}

LataPeones::LataPeones()
{

    NodoGrafoEscena *objeto = new NodoGrafoEscena();
    Peon *mallaPeon = new Peon(50);
    unsigned int identificador = 1;

// PEONES

// Peón Madera
    NodoGrafoEscena *peonMadera = new NodoGrafoEscena();
    peonMadera->ponerNombre("Peón de madera (usa textura de madera)");
    peonMadera->ponerIdentificador(identificador); // 1
    identificador++;
    // textura madera difuso-especular
    TexturaXY *textMadera = new TexturaXY("text-madera.jpg");
    peonMadera->agregar(translate(vec3(0.0, 0.2, 1.0)));
    peonMadera->agregar(scale(vec3(0.15, 0.15, 0.15)));
    peonMadera->agregar(new Material (textMadera, 0.5, 0.6, 0.5, 50.0));
    peonMadera->agregar(mallaPeon);

// Peón Blanco
    NodoGrafoEscena *peonBlanco = new NodoGrafoEscena();
    peonBlanco->ponerNombre("Peón blanco (material difuso blanco)");
    peonBlanco->ponerIdentificador(identificador);
    identificador++; // 2
    peonBlanco->agregar(translate(vec3(0.4, 0.2, 1.0)));
    peonBlanco->agregar(scale(vec3(0.15, 0.15, 0.15)));
    // difuso de color blanco
    peonBlanco->agregar(new Material (0.5, 0.2, 0.5, 5.0));
    peonBlanco->agregar(mallaPeon);

// Peón Negro
    NodoGrafoEscena *peonNegro = new NodoGrafoEscena();
    peonNegro->ponerNombre("Peón negro (material especular, sin apenas componente difusa)");
    peonNegro->ponerIdentificador(identificador); // 3
    identificador++;
    peonNegro->agregar(translate(vec3(0.8, 0.2, 1.0)));
    peonNegro->agregar(scale(vec3(0.15, 0.15, 0.15)));
    // especular sin apenas reflectividad difusa
    peonNegro->agregar(new Material (0.01, 0.2, 0.5, 50.0));
    peonNegro->agregar(mallaPeon);

// LATA

    Lata *lataCocacola = new Lata("lata-coke.jpg");
    lataCocacola->ponerNombre("lata de Coca-Cola (textura de lata de Coca-Cola)");
    lataCocacola->ponerIdentificador(identificador); // 4

// OBJETO

    objeto->agregar(peonMadera);
    objeto->agregar(peonBlanco);
    objeto->agregar(peonNegro);
    objeto->agregar(lataCocacola);

    agregar(objeto);
}

VariasLatasPeones::VariasLatasPeones()
{

    unsigned identificador = 5;

    NodoGrafoEscena *lataPepsi = new NodoGrafoEscena();
    lataPepsi->ponerNombre("Lata de Pepsi (textura de lata de Pepsi)");
    lataPepsi->ponerIdentificador(identificador); // 5
    identificador++;
    lataPepsi->agregar(translate(vec3(1.0, 0.0, 0.0)));
    lataPepsi->agregar(new Lata("lata-pepsi.jpg"));

    NodoGrafoEscena *lataUGR = new NodoGrafoEscena();
    lataUGR->ponerNombre("Lata de la UGR (textura con el escudo de la UGR)");
    lataUGR->ponerIdentificador(identificador); // 6
    lataUGR->agregar(translate(vec3(2.0, 0.0, 0.0)));
    lataUGR->agregar(new Lata ("window-icon.jpg"));

    agregar(lataPepsi);
    agregar(lataUGR);

}