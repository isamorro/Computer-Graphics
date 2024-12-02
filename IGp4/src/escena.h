// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A

#ifndef ESCENA_H
#define ESCENA_H


#include <vector>
#include "aplicacion-ig.h"
// #include "objeto3d.h"
// #include "camara.h"


// *************************************************************************
// Clase Escena
// -----------------
// Clase para objetos visualizables de tipo escena: incluye objetos, cámaras,
// un material inicial, una colección de fuentes de luz, etc...


class Escena
{
   public:

   // crea una escena con una cámara orbital simple, materiales y luces por defecto.
   Escena() ;

   // visualiza el objeto actual de la escena
   void visualizarGL(  ) ;

   // visualiza el objeto actual de la escena, pero en modo selección 
   void visualizarGL_Seleccion(  );

   // pasa la cámara actual a la siguiente
   void siguienteCamara() ;

   // devuelve un puntero a la cámara actual
   CamaraInteractiva * camaraActual() ;

   // pasa el objeto actual al siguiente
   void siguienteObjeto() ;

   // devuelve puntero al objeto actual
   Objeto3D * objetoActual();

   // devuelve un puntero a la colección de fuentes actual
   ColFuentesLuz * colFuentes();

   // visualiza las normales del objeto actual de la escena
   void visualizarNormales();
  

   protected:
   // vector de objetos (alternativos: se visualiza uno de ellos nada más)
   std::vector<Objeto3D *> objetos ;

   // vector de cámaras (se usa una en cada momento)
   std::vector<CamaraInteractiva *> camaras ;

   // material por defecto que se activa antes de dibujar (con iluminación activada)
   Material * material_ini = nullptr ;

   // colección de fuentes de luz que se usarán para dibujar, (con iluminación activada)
   ColFuentesLuz * col_fuentes = nullptr ;

   // índice de la cámara activa (en el vector 'camaras')
   unsigned ind_camara_actual = 0 ;

   // índice del objeto activo (en el vector 'objetos')
   unsigned ind_objeto_actual = 0 ;

} ;


// -------------------------------------------------------------------------
// clase derivada de 'Escena', define un constructor que permite añadir
// al array de objetos de la escena los objetos que se indican en la práctica 1

class Escena1 : public Escena
{
   public:
      Escena1() ;
} ;

class Escena2 : public Escena
{
   public:
      Escena2();
};

class Escena3 : public Escena
{

   public:
      Escena3();

};

class Escena4 : public Escena
{

   public:
      Escena4();

};


#endif // ESCENA_H
