// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (implementación). Clase 'MallaInd' y derivadas.
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Implementación de las clases 
// **        + MallaInd: malla indexada de triángulos (derivada de Objeto3D)
// **        + MallaPLY: malla indexada de triángulos, leída de un PLY (derivada de MallaInd)
// **        + algunas clases derivadas de MallaInd.
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************


#include "ig-aux.h"
#include "aplicacion-ig.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 


// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....

}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd:: calcularNormales()
{
   using namespace glm ;
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......


}


// --------------------------------------------------------------------------------------------

void MallaInd::visualizarGL( )
{
   // comprobar algunas precondiciones básicas
   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );
   CError();

   // si la malla no vértices o no tiene triángulos, imprimir advertencia y salir.
   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // Práctica 1: cambiar color del cauce
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer push del color actual del cauce
   //    - fijar el color en el cauce usando el color del objeto (se lee con 'leerColor()')
   if (tieneColor()){
      cauce->pushColor();
      cauce->fijarColor(cauce->leerColorActual());
   }

   // Práctica 1: crear el descriptor de VAO, si no está creado
   //  Si el puntero 'dvao' es nulo, crear el descriptor de VAO
   //   * en primer lugar se crea el descriptor de VAO, con su constructor 
   //     (se le pasa como parámetro la tabla de posiciones y el número de atributos del cauce). 
   //   * se añade el descriptor de VBO con la tabla de índices (la tabla de triángulos),
   //   * finalmente se añaden al VAO los descriptores VBOs con tablas de atributos 
   //     que no estén vacías
   //  Si el VAO ya está creado, (dvao no nulo), no hay que hacer nada.
   if (dvao == nullptr){

      // tablas de posiciones y colores de vértices (posiciones en 2D, con Z=0)
      dvao = new DescrVAO (numero_atributos_cauce, new DescrVBOAtribs (ind_atrib_posiciones, vertices));
      dvao->agregar(new DescrVBOInds (triangulos));
     
      if (col_ver.size() > 0) 
         dvao->agregar(new DescrVBOAtribs(ind_atrib_colores, col_ver));
      if (nor_ver.size() > 0)
         dvao->agregar(new DescrVBOAtribs (ind_atrib_normales, nor_ver));
      if (cc_tt_ver.size() > 0)
         dvao->agregar(new DescrVBOAtribs(ind_atrib_coord_text, cc_tt_ver));
   }


   // Práctica 1: visualizar el VAO usando el método 'draw' de 'DescrVAO'

   dvao->draw(GL_TRIANGLES); // @param mode (GLenum) modo de visualización (GL_TRIANGLES, GL_LINES, GL_POINTS,  GL_LINE_STRIP o GL_LINE_LOOP)

   // Práctica 1: restaurar color anterior del cauce 
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer 'pop' del color actual del cauce

   if (tieneColor())
      cauce->popColor();
   

}

// -----------------------------------------------------------------------------
// Visualizar el objeto con OpenGL
// usa las tablas de normales, colores y coordenadas de textura, si no están vacías.
      
void MallaInd::visualizarGeomGL( )
{
   // Comprobar que el descriptor de VAO ya está creado
   // (es decir, este método únicamente se podrá invocar después de que 
   // se haya llamado a 'visualizaGL')
   
   assert( dvao != nullptr );

   // Práctica 1: visualizar únicamente la geometría del objeto 
   //    1. Desactivar todas las tablas de atributos del VAO (que no estén vacías)

   if (col_ver.size() > 0) dvao->habilitarAtrib(ind_atrib_colores, 0);
   if (nor_ver.size() > 0) dvao->habilitarAtrib(ind_atrib_normales, 0);
   if (cc_tt_ver.size() > 0) dvao->habilitarAtrib(ind_atrib_coord_text, 0);

   //    2. Dibujar la malla (únicamente visualizará los triángulos), se usa el método 'draw' del VAO (dvao)
   dvao->draw(GL_TRIANGLES);
   
   //    3. Volver a activar todos los atributos para los cuales la tabla no esté vacía
   if (col_ver.size() > 0) dvao->habilitarAtrib(ind_atrib_colores, 1);
   if (nor_ver.size() > 0) dvao->habilitarAtrib(ind_atrib_normales, 1);
   if (cc_tt_ver.size() > 0) dvao->habilitarAtrib(ind_atrib_coord_text, 1);

}

// -----------------------------------------------------------------------------
// Visualizar las normales del objeto, si no tiene tabla de normales imprime 
// advertencia y no hace nada.

void MallaInd::visualizarNormalesGL(  )
{
   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );

   if ( nor_ver.size() == 0 )
   {
      cout << "Advertencia: intentando dibujar normales de una malla que no tiene tabla (" << leerNombre() << ")." << endl ;
      return ;
   }  

   if( nor_ver.size() != vertices.size() )
   {
      cout << "Error visu. normales: tabla de normales no vacía y de tamaño distinto a la de vértices." << endl ;
      cout << "Nombre del objeto        : " << leerNombre() << endl ;
      cout << "Tamaño tabla vértices    : " << vertices.size() << endl ;
      cout << "Tamaño tabla de normales : " << nor_ver.size() << endl ;
      exit(1);
   }
   CError();

   // COMPLETAR: práctica 4: visualizar las normales del objeto MallaInd
   // 
   // *1* Si el puntero al descriptor de VAO de normales ('dvao_normales') es nulo, 
   //    debemos de crear dicho descriptor, con estos pasos:
   //
   //       * Para cada posición 'v_i' de un vértice en el vector 'vertices':
   //             - Leer la correspondiente normal 'n_i' del vector de normales ('nor_ver').
   //             - Añadir 'v_i' al vector 'segmentos_normales'.
   //             - Añadir 'v_i+a*n_i' al vector 'segmentos_normales'.
   //
   //       * Crear el objeto descriptor del VAO de normales, para ello se usa el vector 
   //          'segmentos_normales' y se tiene en cuenta que esa descriptor únicamente gestiona 
   //          una tabla de atributos de vértices (la de posiciones, ya que las otras no se 
   //          necesitan).
   // 
   // *2* Visualizar el VAO de normales, usando el método 'draw' del descriptor, con el 
   //       tipo de primitiva 'GL_LINES'.

   //  ..........

}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void MallaInd::visualizarModoSeleccionGL() 
{

   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar la malla en modo selección 
   //
   // Se debe escribir código para visualizar únicamente la geometría, pero usando el color 
   // obtenido a partir del identificador. El código da estos pasos:
   // 
   // 1. Leer el identificador del objeto (con 'leerIdentificador'). Si el objeto tiene 
   //    identificador (es decir, si su identificador no es -1)
   //       + Hacer push del color del cauce, con 'pushColor'.
   //       + Fijar el color del cauce (con 'fijarColor') usando un color obtenido a 
   //         partir del identificador (con 'ColorDesdeIdent'). 
   // 2. Invocar 'visualizarGeomGL' para visualizar la geometría.
   // 3. Si tiene identificador: hacer pop del color, con 'popColor'.
   //

}


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................


   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................

}

// ****************************************************************************
// Clase 'Cubo

Cubo::Cubo()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

}

// -----------------------------------------------------------------------------------------------

Tetraedro::Tetraedro() : MallaInd ("tetraedro de 4 vértices")
{
   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { +1.0, -1.0, -1.0 }, // 1
         { +0.0, +1.0, -1.0 }, // 2
         { +0.0, +0.0, +1.0 }, // 3
      } ;

   triangulos = {
      {0,1,2}, {0,1,3}, {1,2,3}, {0,2,3}
   };


   glm::vec3 colorTetraedro = {0.342, 0.567, 0.475};
   ponerColor(colorTetraedro);
}

// -----------------------------------------------------------------------------------------------

CuboColores::CuboColores() : MallaInd ("cubo de colores de 8 vértices") 
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;

   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   col_ver = {
      // (R, G, B)
      {0.0, 0.0, 0.0}, // 0
      {0.0, 0.0, 1.0}, // 1
      {0.0, 1.0, 0.0}, // 2
      {0.0, 1.0, 1.0}, // 3
      {1.0, 0.0, 0.0}, // 4
      {1.0, 0.0, 1.0}, // 5
      {1.0, 1.0, 0.0}, // 6
      {1.0, 1.0, 1.0}, // 7
   };  
}

// -----------------------------------------------------------------------------------------------

// Ejercicio 1: Ordinaria 20.21

EstrellaX::EstrellaX(unsigned int n) : MallaInd ("EstrellaX") {

   float num_vertices = 2*n + 1;
   float num_triangulos = 2*n;

   float centroX = 0.0f;
   float centroY = 0.5f;
   float centroZ = 0.5f;
   float radio_exterior = 0.5f;
   float radio_interior = radio_exterior / 2.0f;
   float pi = M_PI;

   // Calculamos medida de los ángulos: 2*pi*radio_ext / n
   float angulo = (2*pi*radio_exterior) / n;

   // Calculamos los vértices
   for (int i=0; i < num_vertices-1; i++){

      // Interiores
      if (i % 2 == 0) {

         vertices.push_back( {centroX,
                              centroY + radio_exterior*sin(angulo*2*i),
                              centroZ + radio_exterior*cos(angulo*2*i)});
      }

      // Exteriores
      else {

         vertices.push_back( {centroX,
                              centroY + (radio_interior)*sin(angulo*2*i),
                              centroZ + (radio_interior)*cos(angulo*2*i) });
      }
   }

   vertices.push_back({centroX, centroY, centroZ});

   // Calculamos los triángulos 
   for (int i=0; i < num_triangulos; i++){
      triangulos.push_back({i, (i+1)%(2*n), 2*n});
   }

   // Ponermos colores
   for (int i=0; i < num_vertices; i++){
      col_ver.push_back(vertices[i]);
   }

};


EstrellaY::EstrellaY(unsigned int n) : MallaInd ("EstrellaY") {

   float num_vertices = 2*n + 1;
   float num_triangulos = 2*n;

   float centroX = 0.5f;
   float centroY = 0.0f;
   float centroZ = 0.5f;
   float radio_exterior = 0.5f;
   float radio_interior = radio_exterior / 2.0f;
   float pi = M_PI;

   // Calculamos medida de los ángulos: 2*pi*radio_ext / n
   float angulo = (2*pi*radio_exterior) / n;

   // Calculamos los vértices
   for (int i=0; i < num_vertices-1; i++){

      // Interiores
      if (i % 2 == 0) {
         // X: x=centro_x+radio*cos(angulo*i)
         // Y: y=centro_y+radio*sin(angulo*i)
         // Z: z=0
         vertices.push_back( {centroX + radio_exterior*cos(angulo*2*i),
                              centroY,
                              centroZ + radio_exterior*sin(angulo*2*i)});
      }

      // Exteriores
      else {

         vertices.push_back( {centroX + (radio_interior)*cos(angulo*2*i),
                              centroY,
                              centroZ + (radio_interior)*sin(angulo*2*i)});
      }
   }

   vertices.push_back({centroX, centroY, centroZ});

   // Calculamos los triángulos 
   for (int i=0; i < num_triangulos; i++){
      triangulos.push_back({2*n, (i+1)%(2*n), i});
   }

   // Ponermos colores
   for (int i=0; i < num_vertices; i++){
      col_ver.push_back(vertices[i]);
   }

};


EstrellaZ::EstrellaZ(unsigned int n) : MallaInd ("EstrellaZ") {

   float num_vertices = 2*n + 1;
   float num_triangulos = 2*n;

   float centroX = 0.5f;
   float centroY = 0.5f;
   float centroZ = 0.0f;
   float radio_exterior = 0.5f;
   float radio_interior = radio_exterior / 2.0f;
   float pi = M_PI;

   // Calculamos medida de los ángulos: 2*pi*radio_ext / n
   float angulo = (2*pi*radio_exterior) / n;

   // Calculamos los vértices
   for (int i=0; i < num_vertices-1; i++){

      // Interiores
      if (i % 2 == 0) {
         // X: x=centro_x+radio*cos(angulo*i)
         // Y: y=centro_y+radio*sin(angulo*i)
         // Z: z=0
         vertices.push_back( {centroX + radio_exterior*cos(angulo*2*i),
                              centroY + radio_exterior*sin(angulo*2*i),
                              centroZ});
      }

      // Exteriores
      else {

         vertices.push_back( {centroX + (radio_interior)*cos(angulo*2*i),
                              centroY + (radio_interior)*sin(angulo*2*i),
                              centroZ});
      }
   }

   vertices.push_back({centroX, centroY, centroZ});

   // Calculamos los triángulos 
   for (int i=0; i < num_triangulos; i++){
      triangulos.push_back({i, (i+1)%(2*n), 2*n});
   }

   // Ponermos colores
   for (int i=0; i < num_vertices; i++){
      col_ver.push_back(vertices[i]);
   }

};

// -----------------------------------------------------------------------------------------------

// Ejercicio 2: Ordinaria 20-21

CasaX::CasaX()
: MallaInd ("CasaX") {

   vertices =
      {  { 0.0, 0.0, 0.0 }, // 0
         { 0.0, 0.0, 0.3 }, // 1
         { 0.0, 0.5, 0.0 }, // 2
         { 0.0, 0.5, 0.3 }, // 3
         { 0.5, 0.0, 0.0 }, // 4
         { 0.5, 0.0, 0.3 }, // 5
         { 0.5, 0.5, 0.0 }, // 6
         { 0.5, 0.5, 0.3 }, // 7
      } ;

   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   // Añadimos arista superior
   vertices.push_back({0.0, 0.75, 0.15});  // 8
   vertices.push_back({0.5, 0.75, 0.15});  // 9

   // Añadimos los 6 triángulos
   triangulos.push_back({3,8,7});
   triangulos.push_back({7,8,9});
   triangulos.push_back({6,7,9});
   triangulos.push_back({2,6,9});
   triangulos.push_back({2,9,8});
   triangulos.push_back({2,3,8});

   // Añadimos color a la casa
   for (int i=0; i < vertices.size(); i++)
      col_ver.push_back(vertices[i]);

};

// -----------------------------------------------------------------------------------------------

// Ejercicio 3: Extraordinaria 20-21

MallaTriangulo::MallaTriangulo() 
: MallaInd ("malla triangulo") {

   vertices =
   {
      { -0.5, 0.0, 0.0 },  // 0
      { +0.5, 0.0, 0.0 },  // 1
      { 0.0, sqrt(2), 0.0} // 2
   };

   triangulos =
   {
      {0, 1, 2}
   };

};

MallaCuadrado::MallaCuadrado()
: MallaInd ("malla cuadrado") {

   vertices = 
   {
      { -1.0, 0.0, 0.0},   // 0
      { +1.0, 0.0, 0.0},   // 1
      { -1.0, +2.0, 0.0},  // 2
      { +1.0, +2.0, 0.0}   // 3

   };

   triangulos =
   {
      { 0, 2, 3},
      { 0, 1, 3}

   };

};

MallaPiramide2::MallaPiramide2()
: MallaInd ("piramide 2") {


   vertices = 
   {
      { 0.0, 0.0, 0.0},   // 0
      { 0.0, 0.0, 0.5},   // 1
      { 0.5, 0.0, 0.5},   // 2
      { 0.5, 0.0, 1.0},   // 3
      { 1.0, 0.0, 1.0},   // 4
      { 1.0, 0.0, 0.0},   // 5
      { 0.5, 1.0, 0.5}    // 6
   };

      triangulos =
   {
      { 0, 1, 6},
      { 1, 2, 6},
      { 2, 3, 6},
      { 3, 4, 6},
      { 4, 5, 6},
      { 0, 5, 6},

      { 0, 1, 2},
      { 2, 3, 4},
      { 2, 4, 5},
      { 0, 2, 5}

   };

};