
#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP

#include "grafo-escena.h"
#include "ig-aux.h"
#include "malla-revol.h"
#include "malla-ind.h"

using namespace glm;
using namespace std;

// Realización de la figura 3.9 (lámpara de escritorio)

// MODELO JERÁRQUICO

class Base : public MallaRevol {

    public:

        // Constructor
        Base
        (
            const int num_verts_per, 
            const unsigned nperfiles,
            float radio,
            float altura
        );
};


class Cabezal : public MallaRevol {

    public:

        // Constructor
        Cabezal
        (
            const int num_verts_per, 
            const unsigned nperfiles,
            float radio,
            float altura
        );
};

class BrazoInferior : public MallaInd {

    public:

        // Constructor
        BrazoInferior
        (
            float longitud,
            float anchura
        );
};

class BrazoSuperior : public MallaInd {

    public:

        // Constructor
        BrazoSuperior
        (
            float longitud,
            float anchura
        );
};

class Lampara : public NodoGrafoEscena {

    protected:

        mat4 *m_rot_cabezal = nullptr;
        mat4 *m_tras_brazos = nullptr;
        mat4 *m_rot_brazos = nullptr;
        mat4 *m_rot_base = nullptr;
        mat4 *m_tras_base = nullptr;  

    public:
        
        // Redefinición de métodos de Objeto3D
        unsigned leerNumParametros() const;
        virtual void actualizarEstadoParametro
        ( 
            const unsigned iParam, 
            const float t_sec 
        );

        // Constructor
        Lampara();

};


#endif