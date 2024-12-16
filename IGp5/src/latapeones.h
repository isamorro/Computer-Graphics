// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A

#ifndef LATAPEONES_HPP
#define LATAPEONES_HPP

#include "grafo-escena.h"
#include "ig-aux.h"
#include "malla-revol.h"
#include "malla-ind.h"
#include "materiales-luces.h"

using namespace glm;
using namespace std;

class Lata : public NodoGrafoEscena {

    public:
        Lata();

};

class LataPeones : public NodoGrafoEscena {

    public:
        LataPeones();

};

#endif