// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A

#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP

#include "grafo-escena.h"
#include "ig-aux.h"
#include "malla-revol.h"
#include "malla-ind.h"

using namespace glm;
using namespace std;


/*****************************************************************************/

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

/*****************************************************************************/

class Cabezal : public MallaInd {

    public:

        // Constructor
        Cabezal
        (
            float ancho,                
            float altura,
            float fondo

        );
};

/*****************************************************************************/

class Rectangulo : public MallaInd {

    public:

        // Constructor
        Rectangulo
        (
            float altura,
            float anchura,
            float fondo
        );
};

/*****************************************************************************/

class Lampara : public NodoGrafoEscena {

    protected:

        mat4 *m_traslacion_brazo_lateral = nullptr;
        mat4 *m_rotacion_cabezal = nullptr;
        mat4 *m_scale_bombilla = nullptr;
        mat4 *m_traslacion_lampara = nullptr;        

    public:

        // Constructor
        Lampara();
        
        // Redefinición de métodos de Objeto3D

        unsigned leerNumParametros() const;

        virtual void actualizarEstadoParametro
        ( 
            const unsigned iParam, 
            const float t_sec 
        );
        
};


#endif