// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A

#ifndef GRAFO_ESCENA_HPP
#define GRAFO_ESCENA_HPP

//#include <tup_mat.h>   

#include "objeto3d.h"
#include "malla-ind.h" // para poder usar clase MallaInd
#include "materiales-luces.h"

using namespace glm;

//using namespace tup_mat ;

// *********************************************************************
// declaración adelantada de estructura para un nodo del grafo de escena

class NodoGrafoEscena ;

// *********************************************************************
// tipo enumerado con los tipos de entradas del nodo del grafo de escena

enum class TipoEntNGE { objeto, transformacion, material, noInicializado } ;

// *********************************************************************
// Entrada del nodo del Grafo de Escena

struct EntradaNGE
{
   TipoEntNGE tipo = TipoEntNGE::noInicializado ;   // objeto, transformacion, material
   union
   {  Objeto3D  * objeto = nullptr ;  // ptr. a un objeto (no propietario)
      glm::mat4 * matriz   ;  // ptr. a matriz 4x4 transf. (propietario)
      Material  * material ; // ptr. a material (no propietario)
   } ;
   // constructores (uno por tipo)
   EntradaNGE() = delete ; // prohibe constructor sin parámetros
   EntradaNGE( Objeto3D        * pObjeto   );      // (copia solo puntero)
   EntradaNGE( const glm::mat4 & pMatriz   ); // (crea copia en el heap)
   EntradaNGE( Material        * pMaterial );    // (copia solo puntero)
   ~EntradaNGE() ;
} ;

// *********************************************************************
// Nodo del grafo de escena: es un objeto 3D parametrizado, que contiene una lista de entradas

class NodoGrafoEscena : public Objeto3D
{
   protected:
 
   // Práctica 3: definir variables y métodos privados del nodo
   std::vector<EntradaNGE> entradas ; // vector de entradas

   public:

   NodoGrafoEscena() ;

   // visualiza usando OpenGL
   virtual void visualizarGL(  ) ;

   // visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...
   // (se supone que el estado de OpenGL está fijado antes de esta llamada de alguna forma adecuada)
   virtual void visualizarGeomGL(  ) ;

   // visualizar las normales de los objetos del nodo
   virtual void visualizarNormalesGL () ;

   // visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
   // basados en los identificadores de los objetos
   virtual void visualizarModoSeleccionGL()  ;

   // añadir una entrada al final, hace copia de la entrada
   // devuelve indice de la entrada dentro del vector de entradas
   unsigned agregar( const EntradaNGE & entrada );

   // construir una entrada y añadirla (al final)
   unsigned agregar( Objeto3D *        pObjeto ); // objeto (copia solo puntero)
   unsigned agregar( const glm::mat4 & pMatriz ); // matriz (copia objeto)
   unsigned agregar( Material *        pMaterial ); // material (copia solo puntero)

   // devuelve el puntero a la matriz en la i-ésima entrada
   glm::mat4 * leerPtrMatriz( unsigned iEnt );

   // método para buscar un objeto con un identificador
   virtual bool buscarObjeto( const int ident_busc, const glm::mat4 & mmodelado,
                    Objeto3D ** objeto, glm::vec3 & centro_wc )  ;

   // si 'centro_calculado' es 'false', recalcula el centro usando los centros
   // de los hijos (el punto medio de la caja englobante de los centros de hijos)
   virtual void calcularCentroOC() ;


} ;

// *********************************************************************
// Práctica 4: NodoCubo24

class NodoCubo24 : public NodoGrafoEscena {

   public:
      NodoCubo24();

};

// *********************************************************************
// EJERCICIOS OPCIONALES PRÁCTICA 3

// EJERCICIO 1 

class GrafoEstrellaX : public NodoGrafoEscena {

   protected:

      mat4 *m_rotacion = nullptr;

   public:
   
      // Constructor

      GrafoEstrellaX(unsigned n);

      // Redefinición de métodos de Objeto3D

      unsigned leerNumParametros() const;

      virtual void actualizarEstadoParametro
      ( 
         const unsigned iParam, 
         const float t_sec 
      );

};

// EJERCICIO 2

class GrafoCubos : public NodoGrafoEscena {

   protected:

      mat4 *m_cubo1 = nullptr;
      mat4 *m_cubo2 = nullptr;
      mat4 *m_cubo3 = nullptr;
      mat4 *m_cubo4 = nullptr;
      mat4 *m_cubo5 = nullptr;
      mat4 *m_cubo6 = nullptr;

   public:

      // Constructor

      GrafoCubos();

      // Redefinición de métodos de Objeto3D

      unsigned leerNumParametros() const;

      virtual void actualizarEstadoParametro
      ( 
         const unsigned iParam, 
         const float t_sec 
      );

};

// *********************************************************************
// EJERCICIOS OPCIONALES PRÁCTICA 4

// EJERCICIO 1 

class NodoDiscoP4 : public NodoGrafoEscena 
{

   public:
      NodoDiscoP4();

};



#endif // GRAFO_ESCENA_HPP

