// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A

#ifndef IG_MALLAIND_HPP
#define IG_MALLAIND_HPP

#include <vector>       // usar std::vector
#include <ig-aux.h>
#include <vaos-vbos.h>

#include "objeto3d.h"   // declaración de 'Objeto3D'


// ---------------------------------------------------------------------
// clase para objetos gráficos genéricos

class MallaInd : public Objeto3D
{
   
   protected:
      // COMPLETAR: incluir aquí las variables y métodos privados que sean
      // necesarios para una malla indexada (y que no aparezcan ya declarados en esta plantilla)
      // ......

      std::vector<glm::vec3>  vertices ;
      std::vector<glm::uvec3> triangulos ;

      std::vector<glm::vec3> col_ver ;   // colores de los vértices
      std::vector<glm::vec3> nor_ver ;   // normales de vértices
      std::vector<glm::vec3> nor_tri ;   // normales de triángulos
      std::vector<glm::vec2> cc_tt_ver ; // coordenadas de textura de los vértices
      
      // descriptor del VAO con los vértices, triángulos y atributos de esta malla indexada
      // (se crea bajo demanda en 'visualizarGL')
      DescrVAO * dvao = nullptr  ;

      // VAO con los segmentos de las normales (vis. con GL_LINES)
      // ( se crea bajo demanda en 'visualizarNormales')
      DescrVAO * dvao_normales = nullptr ;

      std::vector<glm::vec3> segmentos_normales ; // guarda los segmentos de normales
      

      // normales de triángulos y vértices
      void calcularNormales();

      // calculo de las normales de triángulos (solo si no están creadas ya)
      void calcularNormalesTriangulos() ;



   public:
      // crea una malla vacía (nombre: "malla indexada nueva vacía")
      MallaInd() ;

      // crea una malla vacía con un nombre concreto:
      MallaInd( const std::string & nombreIni );

      // Visualizar el objeto con OpenGL
      // usa las tablas de normales, colores y coordenadas de textura, si no están vacías.
      virtual void visualizarGL(  ) ;

      // Visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...
      // (se supone que el estado de OpenGL está fijado antes de esta llamada de alguna forma adecuada)
      virtual void visualizarGeomGL(  ) ;

      // Visualizar las normales del objeto, si no tiene tabla de normales imprime advertencia y no hace nada.
      virtual void visualizarNormalesGL() ;

      // visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
      // basados en los identificadores de los objetos
      virtual void visualizarModoSeleccionGL() ;

      // métodos para acceder a las tablas de una malla (acceso de lectura)
      const std::vector<glm::vec3> & refVertices()   const { return vertices ;  } 
      const std::vector<glm::uvec3> & refTriangulos() const { return triangulos ; }
      


     
} ;
// ---------------------------------------------------------------------
// Clase para mallas obtenidas de un archivo 'ply'
// es un tipo de malla indexada que define un nuevo constructor
// que recibe el nombre del archivo ply como parámetro

class MallaPLY : public MallaInd
{
   public:
      MallaPLY( const std::string & nombre_arch ) ;
} ;


// ---------------------------------------------------------------------

class Cubo : public MallaInd
{
   public:
      Cubo();
};

// ---------------------------------------------------------------------

class Tetraedro : public MallaInd
{
   public:
      Tetraedro();
};

// ---------------------------------------------------------------------

class CuboColores : public MallaInd
{
   public:
      CuboColores();
};

// ----------------------EJERCICIOS OPCIONALES------------------------------

// Ejercicio 1 Práctica 1

class EstrellaX : public MallaInd
{
   public:
      EstrellaX(unsigned int n);
};

class EstrellaY : public MallaInd
{
   public:
      EstrellaY(unsigned int n);
};

class EstrellaZ : public MallaInd
{
   public:
      EstrellaZ(unsigned int n);
};

// ---------------------------------------------------------------------
// Ejercicio 2 Práctica 1

class CasaX : public MallaInd
{
   public:
      CasaX();
};

// ---------------------------------------------------------------------
// Ejercicio 3 Práctica 1

class MallaTriangulo : public MallaInd
{
   public:
      MallaTriangulo();
};

class MallaCuadrado : public MallaInd
{
   public:
      MallaCuadrado();
};

class MallaPiramide2 : public MallaInd
{
   public:
      MallaPiramide2();
};

// ---------------------------------------------------------------------
// Ejercicio 1 Práctica 2

class PiramideEstrellaZ : public MallaInd
{
   public: 
   PiramideEstrellaZ
   (
      unsigned n 
   );
};

// ---------------------------------------------------------------------
// Ejercicio 2 Práctica 2

class RejillaY : public MallaInd 
{
   public:
   RejillaY 
   (
      unsigned n,
      unsigned m
   );
};

// ---------------------------------------------------------------------
// Ejercicio 3 Práctica 2

class MallaTorre : public MallaInd
{
   public:
   MallaTorre
   (
      int n
   );
};


#endif
