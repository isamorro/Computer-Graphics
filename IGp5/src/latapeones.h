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

class Peon : public NodoGrafoEscena {

    public:
        Peon (int nperfiles);
        bool cuandoClick( const glm::vec3 & centro_wc) override;

    protected:
        glm::mat4 *pm_tras = nullptr;
};

class Lata : public NodoGrafoEscena {

    public:
        Lata(const std::string &nombre_archivo);

};

class LataPeones : public NodoGrafoEscena {

    public:
        LataPeones();
};

class VariasLatasPeones : public LataPeones {

    public:
        VariasLatasPeones();
};

#endif