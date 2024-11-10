// *********************************************************************
// ** 
// ** Isabel Morro Tabares, 79095945A
// ** Curso 2024/2025
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** Declaración de la clases necesarias para crear el objeto jerárquico
// *********************************************************************

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
            float altura,
            float punto_inf_izq,
            float punto_inf_izq_Y,
            float punto_inf_izq_Z
        );
};


class Cabezal : public MallaInd {

    public:

        // Constructor
        Cabezal
        (
            float ancho,                
            float altura,
            float fondo,
            float centro_X,
            float centro_Y,
            float centro_Z
        );
};

class BrazoVertical : public MallaInd {

    public:

        // Constructor
        BrazoVertical
        (
            float altura,
            float anchura,
            float extremo_inf_delantero_izq_X,
            float extremo_inf_delantero_izq_Y,
            float extremo_inf_delantero_izq_Z
        );
};

class BrazoHorizontal : public MallaInd {

    public:

        // Constructor
        BrazoHorizontal
        (
            float altura,
            float anchura,
            float fondo,
            float extremo_inf_delantero_izq_X,
            float extremo_inf_delantero_izq_Y,
            float extremo_inf_delantero_izq_Z
        );
};


class Lampara : public NodoGrafoEscena {

    // protected:

    //     mat4 *m_rot_cabezal = nullptr;
    //     mat4 *m_tras_brazos = nullptr;
    //     mat4 *m_rot_brazos = nullptr;
    //     mat4 *m_rot_base = nullptr;
    //     mat4 *m_tras_base = nullptr;  

    public:
        
        // Redefinición de métodos de Objeto3D

        // unsigned leerNumParametros() const;
        // virtual void actualizarEstadoParametro
        // ( 
        //     const unsigned iParam, 
        //     const float t_sec 
        // );

        // Constructor
        Lampara();

};


#endif