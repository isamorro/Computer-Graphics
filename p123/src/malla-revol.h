// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A

#ifndef IG_MALLAREVOL_HPP
#define IG_MALLAREVOL_HPP

#include <vector>          // usar std::vector
#include <string>

#include "malla-ind.h"   // declaración de 'Objeto3D'
// ---------------------------------------------------------------------
// clase para mallas indexadas obtenidas a partir de la revolución de un perfil

class MallaRevol : public MallaInd
{
   private:



   protected: //

   MallaRevol() {} // solo usable desde clases derivadas con constructores especificos

   // Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
   // a partir de un perfil y el número de copias que queremos de dicho perfil.
   void inicializar
   (
      const std::vector<glm::vec3> & perfil,     // tabla de vértices del perfil original
      const unsigned                 num_copias  // número de copias del perfil
   ) ;
} ;

// ----------------------EJERCICIOS OBLIGATORIOS------------------------------

class MallaRevolPLY : public MallaRevol
{
   public:
   MallaRevolPLY( const std::string & nombre_arch,
                  const unsigned nperfiles ) ;
} ;

class Cilidndro : public MallaRevol
{
   public:
   Cilidndro 
   (
      const int num_verts_per,   // número de vertices del perfil original(m)
      const unsigned nperfiles   // número de perfiles (n)
   );
};

class Cono : public MallaRevol
{
   public:
   Cono
   (
      const int num_verts_per,   // número de vértices dle perfil original (m)
      const unsigned nperfiles  // número de perfiles (n)
   );

};

class Esfera : public MallaRevol
{
   public:
   Esfera 
   (
      const int num_verts_per,   // número de vértices del perfil original (m)
      const unsigned nperfiles   // número de perfiles (n)
   );
};

#endif
