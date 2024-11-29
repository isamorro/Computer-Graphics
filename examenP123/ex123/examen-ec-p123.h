// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A

#ifndef EXAMEN_EC_P123_HPP
#define EXAMEN_EC_P123_HPP

#include "malla-ind.h"
#include "grafo-escena.h"


class Ejercicio1 : public MallaInd {

    public:
    
        Ejercicio1();

};

class Ejercicio2 : public MallaInd {


    public:

        Ejercicio2 (unsigned n);

};

class Ejercicio3 : public NodoGrafoEscena
{

    protected:

        mat4 *m_rot = nullptr;
        mat4 *m_escala = nullptr;

    public:

        Ejercicio3
        (
            float h,
            float w
        );

        // Redefinición de métodos de Objeto3D

        unsigned leerNumParametros() const;

        virtual void actualizarEstadoParametro
        ( 
            const unsigned iParam, 
            const float t_sec 
        );

};


#endif