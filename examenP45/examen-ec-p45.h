// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A 

#ifndef EXAMEN_EC_P45_HPP
#define EXAMEN_EC_P45_HPP

#include "malla-ind.h"
#include "grafo-escena.h"

// Ejercicio práctica 4

class Piramide : public MallaInd
{
   public:
      Piramide();
};

class PiramideNodo : public NodoGrafoEscena {
   public:
      PiramideNodo();
};

// Ejercicio práctica 5

class MallaP5 : public MallaInd {
    public:
        MallaP5 (glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

};

class TrianguloNodo : public NodoGrafoEscena {

    public:
        TrianguloNodo(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
        bool cuandoClick( const glm::vec3 & centro_wc) override;

};

class NodoP5 : public NodoGrafoEscena {
    public:
        NodoP5();

};

#endif