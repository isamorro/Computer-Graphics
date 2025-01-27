// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A

#include "ig-aux.h"

#include "objeto3d.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include "camara.h"
#include "materiales-luces.h"
#include "escena.h"
#include "modelo-jer.h"
#include "latapeones.h"
#include "examen-ec-p45.h"


// -----------------------------------------------------------------------------------------------

Escena::Escena()
{
   // Práctica 4: inicializar la colección de fuentes y el material inicial 
   // Se debe dar un valor inicial adecuado a las variables de instancia 'col_fuentes' y 'material_ini'
   
   // Para 'col_fuentes', se usará una instancia de 'Col2Fuentes'
   col_fuentes = new Col2Fuentes();
   // Se deben de elegir los parámetros del material.
   material_ini = new Material(0.4f, 0.8f, 0.0f, 2.0f); 


   // Práctica 5: añadir varias cámaras perspectiva y ortogonales al vector de cámaras de la escena

   // Añadir sentencias 'push_back' para añadir varias cámaras al vector 'camaras'.
   // Eliminar este 'push_back' de la cámara orbital simple ('CamaraOrbitalSimple') por varias cámaras de 3 modos ('Camara3Modos')
   // camaras.push_back( new CamaraOrbitalSimple() );
   
   // Camara3Modos(const bool perspectiva_ini (perspectiva (true) como cámara real, u ortográfica (false) como planos técnicos), 
   //              const glm::vec3 &origen_ini (posición del observador), 
   //              const float ratio_vp_ini (alto / ancho, se suele dear en 1),
   //              const glm::vec3 &punto_aten_ini (punto de atención, hacia donde mira la cámara), 
   //              const float fovy_grad_ini = (70.0F) (apertura vertical de campo, en grados)

   camaras.push_back(new Camara3Modos(true, *(new vec3({2.0, 2.0, 2.0})), 1.0, *(new vec3({0.0, 0.0, 0.0})), 60.0));
   camaras.push_back(new Camara3Modos(false, *(new vec3({5.0, 5.0, 5.0})), 1.0, *(new vec3({0.0, 0.0, 0.0})), 60.0));
   camaras.push_back(new Camara3Modos(false, *(new vec3({-2.5, 2.5, 2.5})), 1.0, *(new vec3({0.0, 0.0, 0.0})), 50.0));
   camaras.push_back(new Camara3Modos(true, *(new vec3({5.0, -2.5, 5.0})), 1.0, *(new vec3({0.5, 3.0, 0.0}))));

}
// -----------------------------------------------------------------------------------------------
// visualiza la escena en la ventana actual, usando la configuración especificada en 'cv'
// (pone 'apl->modo_selecion' a 'false' y queda así)

void Escena::visualizarGL( )
{
   assert( aplicacionIG != nullptr );
   assert( aplicacionIG->cauce != nullptr );

   using namespace std ;
   CError();
   
   // recuperar el cauce del objeto 'apl' (simplemente para acortar notación)
   Cauce * cauce = aplicacionIG->cauce ;

   // desactivar el modo de selección, por si acaso
   aplicacionIG->modo_seleccion = false ;

   // activar el cauce
   cauce->activar() ;
   CError();

   // recuperar la cámara actual de esta escena y: 
   //   (1) fijar la camara actual del contexto de visualización  
   //   (2) fijar las matrices 'modelview' y 'projection' en el 
   //       cauce gráfico (es decir: activar la cámara actual)
   CamaraInteractiva * camara = camaras[ind_camara_actual] ; assert( camara != nullptr );

   const float ratio_vp = float(aplicacionIG->ventana_tam_y)/float(aplicacionIG->ventana_tam_x) ;
   
   //cout << "Escena::visualizarGL: dimen " << apl->ventana_tam_x << " x " << apl->ventana_tam_y << ", y/x == " << ratio_vp << endl ;

   camara->fijarRatioViewport( ratio_vp );
   //cout << endl << __FUNCTION__ << ": índice cámara actual == " << ind_camara_actual << endl ;
   camara->activar( *cauce ) ;
   CError();

   // dibujar los ejes, si procede
   if ( aplicacionIG->dibujar_ejes  )
      DibujarEjesSolido( *cauce ) ; // ver 'ig-aux.cpp' para la definición.

   // fijar el color por defecto (inicial) en el cauce para dibujar los objetos 
   // (es blanco debido a que el fondo se rellena con un color oscuro y debe contrastar).
   cauce->fijarColor( 1.0, 1.0, 1.0 );
   
   // fijar el modo de normales (útil para la práctica 4)
   cauce->fijarUsarNormalesTri( aplicacionIG->usar_normales_tri );

   // Práctica 1: Configurar el modo de polígonos con 'glPolygonMode'
   // Usar 'glPolygonMode' en función del modo guardado en 'apl->modo_visu', 
   // que puede ser: puntos,lineas o relleno.
   
   switch(aplicacionIG->modo_visu){

      case ModosVisu::lineas:
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         break;
      case ModosVisu::puntos:
         glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
         break;
      case ModosVisu::relleno:
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         break;
      default:
         throw std::invalid_argument("Error en VisualizarGL");
   }

   CError();

   if ( aplicacionIG->iluminacion )
   {
      // Práctica 4: activar evaluación del MIL (y desactivar texturas)
      
      // habilitar evaluación del MIL en el cauce (fijarEvalMIL)
      cauce->fijarEvalMIL( true );
      // activar la colección de fuentes de la escena
      col_fuentes->activar();
      // activar el material inicial (usando 'pila_materiales')
      aplicacionIG->pila_materiales->activar(material_ini);

   }
   else // si la iluminación no está activada, deshabilitar MIL y texturas
   {  
      cauce->fijarEvalMIL( false );
      cauce->fijarEvalText( false );
   }

   //log("recupero objeto");
   CError();

   // recuperar el objeto actual de esta escena
   Objeto3D * objeto = objetos[ind_objeto_actual] ; assert( objeto != nullptr );

   // Práctica 1: visualizar el objeto actual ('objeto')
   objeto->visualizarGL();

   // Visualizar las aristas del objeto, si procede (es decir: en modo relleno, con 
   // visualización de aristas activada)

   if ( aplicacionIG->dibujar_aristas && aplicacionIG->modo_visu == ModosVisu::relleno ) 
   {
      // desactivar iluminación y texturas (podrían estarlo a partir de prác. 4)
      cauce->fijarEvalMIL( false );
      cauce->fijarEvalText( false );

      // Práctica 1: visualizar únicamente las aristas del objeto actual
      // - hay que invocar 'visualizarGeomGL' para el objeto actual de la escena ('objeto')
      // - antes de eso debemos de poner el cauce en un estado adecuado:
      //      - fijar el color a negro
      //      - fijar el modo de polígonos a modo 'lineas'
      aplicacionIG->cauce->fijarColor(0,0,0);
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      objeto->visualizarGeomGL();
   }
   

}
// -----------------------------------------------------------------------------------------------
// visualiza el objeto actual de la cámara, pero en modo selección 

void Escena::visualizarGL_Seleccion(  )
{
   // Comprobar algunas precondiciones y recuperar el cauce (para acortar la anotación)
   assert( aplicacionIG != nullptr );
   assert( aplicacionIG->cauce != nullptr );
   Cauce * cauce = aplicacionIG->cauce ;
   CError();

   // Práctica 5: visualizar el objeto raiz de esta escena en modo selección
   // (1) Configurar estado de OpenGL:
   //       + fijar el viewport (con 'glViewport') usando el tamaño de la ventana (guardado en 'apl'), 
   //       + fijar el modo de polígonos a 'relleno', con 'glPolygonMode'
   glViewport(0, 0, aplicacionIG->ventana_tam_x, aplicacionIG->ventana_tam_y);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


   // (2) Activar  y configurar el cauce:
   //      + Activar el cauce (con el método 'activar')
   //      + Desactivar iluminación y texturas en el cauce
   //      + Poner el color actual del cauce a '0' (por defecto los objetos no son seleccionables)
   cauce->activar();
   cauce->fijarEvalMIL(false);
   cauce->fijarEvalText(false);
   cauce->fijarColor(vec4(0.0, 0.0, 0.0, 1.0));

   // (3) Limpiar el framebuffer (color y profundidad) con color (0,0,0) (para indicar que en ningún pixel hay nada seleccionable)
   glClearColor(0,0,0,1);
   glClear(GL_DEPTH_BUFFER_BIT);

   // (4) Recuperar la cámara actual (con 'camaraActual') y activarla en el cauce, 
   camaraActual()->activar(*cauce);

   // (5) Recuperar (con 'objetoActual') el objeto raíz actual de esta escena y 
   //     visualizarlo con 'visualizarModoSeleccionGL'.
   objetoActual()->visualizarModoSeleccionGL();

}

// -----------------------------------------------------------------------------------------------
// visualiza las normales del objeto actual de la escena

void Escena::visualizarNormales(  )
{
   // comprobar precondiciones
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );

   // Práctica 4: visualizar normales del objeto actual de la escena 
   // 1. Configurar el cauce de la forma adecuada, es decir:
   //      * Desactivar la iluminación (con 'fijarEvalMIL')
   cauce->fijarEvalMIL(false);
   //      * Desactivar el uso de texturas (con 'fijarEvalText')
   cauce->fijarEvalText(false);
   //      * fijar el color (con 'fijarColor') 
   cauce->fijarColor(1.0, 1.0, 1.0);

   // 2. Visualizar las normales del objeto actual de la escena (con el método 'visualizarNormalesGL')
   objetoActual()->visualizarNormalesGL();

}


// -----------------------------------------------------------------------------------------------
// pasa la cámara actual a la siguiente

void Escena::siguienteCamara()
{
   assert( ind_camara_actual < camaras.size() );
   ind_camara_actual = (ind_camara_actual+1 ) % camaras.size();
   using namespace std ;
   cout << "Cámara actual cambiada a: " << (ind_camara_actual+1) << "/" << camaras.size() << ": " << camaras[ind_camara_actual]->descripcion() << endl ;
}

// -----------------------------------------------------------------------------------------------
// pasa el objeto actual al siguiente

void Escena::siguienteObjeto()
{
   if ( objetos.size() == 0 )
      return ;
   assert( ind_objeto_actual < objetos.size() );
   ind_objeto_actual = (ind_objeto_actual+1 ) % objetos.size();
   using namespace std ;
   cout << "Objeto actual cambiado a: " << objetoActual()->leerNombre()
        << " (" << (ind_objeto_actual+1) << "/" << objetos.size() << ")." << endl  ;
}

// -----------------------------------------------------------------------------------------------
// devuelve puntero al objeto actual

Objeto3D * Escena::objetoActual()
{
   assert( ind_objeto_actual < objetos.size() );
   assert( objetos[ind_objeto_actual] != nullptr );
   return objetos[ind_objeto_actual] ;
}
// -----------------------------------------------------------------------------------------------
// devuelve un puntero a la cámara actual

CamaraInteractiva * Escena::camaraActual()
{
   assert( ind_camara_actual < camaras.size() );
   assert( camaras[ind_camara_actual] != nullptr );
   return camaras[ind_camara_actual] ;
}
// -----------------------------------------------------------------------------------------------
// devuelve un puntero a la colección de fuentes actual

ColFuentesLuz * Escena::colFuentes()
{
   assert( col_fuentes != nullptr );
   return col_fuentes ;
}
// -----------------------------------------------------------------------------------------------

constexpr bool lunes = false ;

Escena1::Escena1()
{
   using namespace std ;
   cout << "Creando objetos de la práctica 1." << endl ;

   // ----------------------EJERCICIOS OBLIGATORIOS------------------------------
   objetos.push_back(new Cubo());
   objetos.push_back(new Tetraedro());
   objetos.push_back(new CuboColores());
   objetos.push_back(new EstrellaZ(5));


   // ----------------------EJERCICIOS OPCIONALES------------------------------
   objetos.push_back(new EstrellaY(7));
   objetos.push_back(new EstrellaX(5));
   objetos.push_back(new CasaX());
   objetos.push_back(new MallaTriangulo());
   objetos.push_back(new MallaCuadrado());
   objetos.push_back(new MallaPiramide2());

}

// -------------------------------------------------------------------------
// Práctica 2

Escena2::Escena2(){

   using namespace std;
   cout << "Creando objetos de la práctica 2." << endl;

   // objetos.push_back(new MallaPLY("../materiales/plys/beethoven.ply"));
   // objetos.push_back(new MallaPLY("../materiales/plys/big_dodge.ply"));

   int nperfiles = 100; // Número de perfiles
   int nveper = 10; // Número de vértices por perfil
   
   objetos.push_back(new MallaRevolPLY("peon.ply",nperfiles));

   // ----------------------EJERCICIOS OBLIGATORIOS------------------------------
   objetos.push_back(new Cilidndro(nveper,nperfiles));
   objetos.push_back(new Cono(nveper, nperfiles));
   objetos.push_back(new Esfera(nveper, nperfiles));

   // ----------------------EJERCICIOS OPCIONALES------------------------------
   objetos.push_back(new PiramideEstrellaZ(10));
   objetos.push_back(new RejillaY(10, 10));
   objetos.push_back(new MallaTorre(5));


}


// -------------------------------------------------------------------------
// Práctica 3: completar constructor de 'Escena3'
//
// Añadir la implementación del constructor de la clase Escena3 para construir
// los objetos que se indican en los guiones de las práctica 3

Escena3::Escena3() 
{
   using namespace std;
   cout << "Creando objetos de la práctica 3." << endl;

   // ----------------------EJERCICIOS OBLIGATORIOS------------------------------
   objetos.push_back(new Lampara());

   // ----------------------EJERCICIOS OPCIONALES------------------------------  
   objetos.push_back(new GrafoEstrellaX(6));
   objetos.push_back(new GrafoCubos());

}


// ----------------------------------------------------------------------------
// Práctica 4: escribir implementación del constructor de 'Escena4'. 
//
// Añadir la implementación del constructor de la clase Escena4 para construir
// los objetos que se indican en el guion de la práctica 4

Escena4::Escena4(){

   using namespace std;
   cout << "Creando objetos de la práctica 4." << endl;

   // // ----------------------EJERCICIOS OBLIGATORIOS------------------------------
   // objetos.push_back(new LataPeones());
   // objetos.push_back(new NodoCubo24());

   // // ----------------------EJERCICIOS OPCIONALES------------------------------
   // objetos.push_back(new NodoDiscoP4());
   // objetos.push_back(new NodoEJ3(true));
   // objetos.push_back(new NodoEJ3(false));

   objetos.push_back(new PiramideNodo());
}


// ----------------------------------------------------------------------
// Práctica 5: escribir implementación del constructor de 'Escena5'.
// 
// Añadir la implementación del constructor de la clase Escena5 para construir
// los objetos que se indican en el guion de la práctica 5

Escena5::Escena5(){

   using namespace std;
   cout << "Creando objetos de la práctica 5." << endl;

   // // ----------------------EJERCICIOS OBLIGATORIOS------------------------------
   // objetos.push_back(new VariasLatasPeones());

   // // ----------------------EJERCICIOS OPCIONALES------------------------------
   // objetos.push_back(new GrafoEsferasP5());
   // objetos.push_back(new GrafoEsferasP5_2());

   objetos.push_back(new NodoP5());

}


