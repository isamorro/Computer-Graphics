// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A


#include "ig-aux.h"
#include "aplicacion-ig.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 


using namespace glm;

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

   // Práctica 4: creación de la tabla de normales de triángulos
   // sección 4.6.3.1
   
   for (int i = 0; i < nt; i++) {

      vec3 a = vertices[triangulos[i][1]] - vertices[triangulos[i][0]];
      vec3 b = vertices[triangulos[i][2]]- vertices[triangulos[i][0]];

      vec3 mc = cross(a, b); // producto vectorial

      vec3 nc;
      if (length(mc) != 0.0) nc = normalize(mc);
      else nc = vec3(0.0, 0.0, 0.0);
      nor_tri.push_back(nc);

   }
}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd:: calcularNormales()
{
   using namespace glm ;
   
   // Práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   calcularNormalesTriangulos();

   // sección 4.6.3.2
   nor_ver = std::vector<vec3>(vertices.size(), vec3(0.0, 0.0, 0.0));
   for (int i = 0; i < triangulos.size(); i++) {
      for (int j = 0; j < 3; j++) {

         unsigned k = triangulos[i][j];
         nor_ver[k]  = nor_ver[k] + nor_tri[i];
   
      }
   }

   for (int i = 0; i < nor_ver.size(); i++){
      if (length(nor_ver[i]) != 0.0) nor_ver[i] = normalize(nor_ver[i]);
   }
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

   // Práctica 4: visualizar las normales del objeto MallaInd

   // Si el puntero al descriptor de VAO de normales ('dvao_normales') es nulo, 
   // debemos de crear dicho descriptor, con estos pasos:
   if (dvao_normales == nullptr){
      // Para cada posición 'v_i' de un vértice en el vector 'vertices':
      for (int i=0; i < vertices.size(); i++){
         // Añadir 'v_i' al vector 'segmentos_normales'.
         segmentos_normales.push_back(vertices[i]);
         // Leer la correspondiente normal 'n_i' del vector de normales ('nor_ver').
         // Añadir 'v_i+a*n_i' al vector 'segmentos_normales'.
         float a = 0.35f; // aleatorio?
         segmentos_normales.push_back(vertices[i] + a*nor_ver[i]);
      }
      
      // Crear el objeto descriptor del VAO de normales, para ello se usa el vector 
      // 'segmentos_normales' y se tiene en cuenta que esa descriptor únicamente gestiona 
      // una tabla de atributos de vértices (la de posiciones, ya que las otras no se 
      // necesitan).
      dvao_normales = new DescrVAO(numero_atributos_cauce, new DescrVBOAtribs(ind_atrib_posiciones, segmentos_normales));
   }
   
   // Visualizar el VAO de normales, usando el método 'draw' del descriptor, con el 
   // tipo de primitiva 'GL_LINES'.
   dvao_normales->draw(GL_LINES);
}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void MallaInd::visualizarModoSeleccionGL() 
{

   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );

   // Práctica 5: visualizar la malla en modo selección 
   // Se debe escribir código para visualizar únicamente la geometría, pero usando el color 
   // obtenido a partir del identificador. El código da estos pasos:
   // 
   // 1. Leer el identificador del objeto (con 'leerIdentificador'). Si el objeto tiene 
   //    identificador (es decir, si su identificador no es -1)
   //       + Hacer push del color del cauce, con 'pushColor'.
   //       + Fijar el color del cauce (con 'fijarColor') usando un color obtenido a 
   //         partir del identificador (con 'ColorDesdeIdent'). 

   int identificador = leerIdentificador();
   if (identificador != -1) {
      cauce->pushColor();
      cauce->fijarColor(ColorDesdeIdent(identificador));
   }

   // 2. Invocar 'visualizarGeomGL' para visualizar la geometría.
   visualizarGeomGL();

   // 3. Si tiene identificador: hacer pop del color, con 'popColor'.
   if (identificador != -1) cauce->popColor();

}


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // Práctica 2: leer archivo PLY e inicializar la malla
   LeerPLY(nombre_arch, vertices, triangulos);
   
   // Práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   calcularNormales();

}

// ****************************************************************************

// ----------------------EJERCICIOS OBLIGATORIOS------------------------------

// Clase Cubo
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

   // Práctica 4
   calcularNormales();

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

   // Práctica 4
   calcularNormales();

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

// Práctica 4: Cubo24
// Cubo con 24 vértices (6 caras x 4 vertices)

Cubo24::Cubo24()
{
   
   vertices =
      { 
         {+1.0, -1.0, +1.0}, 
         {+1.0, +1.0, +1.0}, 
         {+1.0, +1.0, -1.0}, 
         {+1.0, -1.0, -1.0}, 

         {-1.0, -1.0, +1.0}, 
         {-1.0, +1.0, +1.0}, 
         {+1.0, +1.0, +1.0}, 
         {+1.0, -1.0, +1.0}, 

         {-1.0, -1.0, -1.0}, 
         {-1.0, +1.0, -1.0}, 
         {-1.0, +1.0, +1.0}, 
         {-1.0, -1.0, +1.0}, 

         {+1.0, -1.0, -1.0}, 
         {+1.0, +1.0, -1.0}, 
         {-1.0, +1.0, -1.0}, 
         {-1.0, -1.0, -1.0}, 


         {+1.0, +1.0, +1.0}, 
         {-1.0, +1.0, +1.0}, 
         {-1.0, +1.0, -1.0}, 
         {+1.0, +1.0, -1.0}, 

         {+1.0, -1.0, +1.0}, 
         {-1.0, -1.0, +1.0}, 
         {-1.0, -1.0, -1.0}, 
         {+1.0, -1.0, -1.0} 
      };

   triangulos =
      {
         {0, 3, 2},
         {0, 2, 1},

         {4, 7, 6},
         {4, 6, 5},

         {8, 11, 10},
         {8, 10, 9},

         {12, 15, 14},
         {12, 14, 13},

         {16, 19, 18},
         {16, 18, 17},

         {20, 22, 23},
         {20, 21, 22}
      };

   // Asignamos valores a las tablas de coordenadas de texturas explícitamente
   // t3 diap 134

   //  Modificado despues de la entrega
   // for (int i=0; i < 6; i++){
   //    cc_tt_ver.push_back({0, 1});
   //    cc_tt_ver.push_back({1, 1});
   //    cc_tt_ver.push_back({1, 0});
   //    cc_tt_ver.push_back({0, 0});
   // }

   for (int i=0; i < 6; i++){
      cc_tt_ver.push_back({0.0, 1.0});
      cc_tt_ver.push_back({0.0, 0.0});
      cc_tt_ver.push_back({1.0, 0.0});
      cc_tt_ver.push_back({1.0, 1.0});
   }

   calcularNormales();

}

// ----------------------EJERCICIOS OPCIONALES------------------------------

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

      if (i % 2 == 0) {

         vertices.push_back( {centroX,
                              centroY + radio_exterior*sin(angulo*2*i),
                              centroZ + radio_exterior*cos(angulo*2*i)});
      }

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

      if (i % 2 == 0) {
         // X: x=centro_x+radio*cos(angulo*i)
         // Y: y=centro_y+radio*sin(angulo*i)
         // Z: z=0
         vertices.push_back( {centroX + radio_exterior*cos(angulo*2*i),
                              centroY,
                              centroZ + radio_exterior*sin(angulo*2*i)});
      }

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

      if (i % 2 == 0) {
         // X: x=centro_x+radio*cos(angulo*i)
         // Y: y=centro_y+radio*sin(angulo*i)
         // Z: z=0
         vertices.push_back( {centroX + radio_exterior*cos(angulo*2*i),
                              centroY + radio_exterior*sin(angulo*2*i),
                              centroZ});
      }

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

// -----------------------------------------------------------------------------------------------

// Ejercicio 1 Práctica 2

PiramideEstrellaZ::PiramideEstrellaZ
(
   unsigned n
)
: MallaInd ("piramide estrella Z con mallas indexadas")
{
   // CALCULO DE LA BASE (ESTRELLA-Z)

   float num_vertices = 2*n + 1;
   float num_triangulos = 2*n;
   float centroX, centroY, radio_exterior = 0.5f;
   float radio_interior = radio_exterior / 2.0f;
   float pi = M_PI;

   // Calculamos medida de los ángulos: 2*pi*radio_ext / n
   float angulo = (2*pi*radio_exterior) / n;

   // Calculamos los vértices
   for (int i=0; i < num_vertices-1; i++){

      // Interiores
      if (i % 2 == 0) {

         vertices.push_back( {centroX + radio_exterior*cos(angulo*2*i),
                              centroY + radio_exterior*sin(angulo*2*i),
                              0.0f});
      }

      // Exteriores
      else {

         vertices.push_back( {centroX + (radio_interior)*cos(angulo*2*i),
                              centroY + (radio_interior)*sin(angulo*2*i),
                              0.0f});
      }
   }

   vertices.push_back({centroX, centroY, 0.0f});
   vertices.push_back({centroX, centroY, 0.55f});

   // Calculamos los triángulos 
   for (int i=0; i < num_triangulos; i++){
      
      triangulos.push_back({i, (i+1)%(2*n), 2*n});
      // AÑADIDO DE ESTE EJERCICIO 
      triangulos.push_back({i, (i+1)%(2*n), 2*n + 1});
   }
  
   for (int i=1;i<2*n+2; i++) col_ver.push_back(vertices[i]);
   
   col_ver.push_back({1.0f,1.0f,1.0f});

};

// -----------------------------------------------------------------------------------------------

// Ejercicio 2 Práctica 2

RejillaY::RejillaY
(
   unsigned n,
   unsigned m
) 
: MallaInd ("RejillaY por mallas indexadas") {

   float y = 0.0f;
   float dist_x = 1.0 / (n-1);
   float dist_z = 1.0 / (m-1);

   for (int i=0; i < n; i++){
      for (int j=0; j < m; j++){
         vertices.push_back({i*dist_x, y, j*dist_z});
      }
   }

   for(int i=0; i < n-1; i++){
      for(int j=0; j < m-1; j++){
         triangulos.push_back({i*m+j,i*m+j+1,(i+1)*m+j});
         triangulos.push_back({i*m+j+1,(i+1)*m+j+1,(i+1)*m+j});
      }
   }

   for (int i=0; i < n*m; i++) col_ver.push_back(vertices[i]);
}

// ---------------------------------------------------------------------
// Ejercicio 3 Práctica 2

MallaTorre::MallaTorre 
(
   int n
)
: MallaInd ("MallaTorre por mallas indexadas")
{

   // Para que tenga como máximo altura 1
   //float dist = 1.0 / n;

   float dist = 0.5;

   for (int i=0; i < n+1; i++){
      float y = i*dist;
      vertices.push_back({-0.5, y, 0.5});
      vertices.push_back({-0.5, y, -0.5});
      vertices.push_back({0.5, y, -0.5});
      vertices.push_back({0.5, y, 0.5});
   }

   int j = 0;

   for (int i=0; i < n; i++){
      
      triangulos.push_back({j, 1+j, 4+j});
      triangulos.push_back({j+4, j+5, j+1});

      triangulos.push_back({1+j, 5+j, 2+j});
      triangulos.push_back({5+j, 6+j, 2+j});

      triangulos.push_back({2+j, 6+j, 3+j});
      triangulos.push_back({6+j, 7+j, 3+j});

      triangulos.push_back({3+j, 7+j, j});
      triangulos.push_back({7+j, 4+j, j});
      
      j += 4;
   }

}

// ---------------------------------------------------------------------
// Ejercicio 1 Práctica 4

MallaDiscoP4::MallaDiscoP4()
{
   // Dado por profesor
   ponerColor({1.0, 1.0, 1.0});

   // ni son las 23 circunferencias
   const unsigned ni = 23, nj = 31;

   for( unsigned i= 0 ; i < ni ; i++ )
   for( unsigned j= 0 ; j < nj ; j++ )
   {
      const float
         fi = float(i)/float(ni-1),
         fj = float(j)/float(nj-1),
         ai = 2.0*M_PI*fi,
         x = fj * cos( ai ),
         y = fj * sin( ai ),
         z = 0.0 ;
      vertices.push_back({ x, y, z });

      // Ej 1 :  TRANSFORMACIÓN CARTESIANA

      /*
         Como tiene radio uno, multiplicamos cada componente por 0.5 para que la circunferencia
         tenga diámetro 1, como está centrada en el (0,0) tenemos que desplazarla para que 
         su centro sea (0.5, 0.5)    

         r = fj
         tita = 2*M_PI*fi
         (u,v)=(0.5×(1+rcosθ),0.5×(1+rsinθ))  

      */

      // La circunferencia esta centrada en el (0, 0), si no sumaramos uno, lo que hace es que cada cuarto de la circunferencia
      // toma parte de la foto, en vez de estar esta centrada y aparecer una sola vez en la circunferencia
         // cc_tt_ver.push_back({0.5 * (fj * cos(2.0 * M_PI * fi)), 0.5 * (fj * sin(2.0 * M_PI * fi))});

      // Si no multiplicamos por 0.5, los cuadrados salen mucho más pequeños, y nos vuelven a salir cuatro imágenes en
      // la circunferencia
      // a menor valor de la multiplicación, más grande salen
         // cc_tt_ver.push_back({(1.0 + fj * cos(2.0 * M_PI * fi)), (1.0 + fj * sin(2.0 * M_PI * fi))});
      
      // Respuesta correcta del ejercicio
      // cc_tt_ver.push_back({0.5 * (1.0 + fj * cos(2.0 * M_PI * fi)), 0.5 * (1.0 + fj * sin(2.0 * M_PI * fi))});
      
     
      // Ej 2 : COORDENADAS POLARES DIRECTAS (ESTIRAMIENTO RADIAL)

      /*
         Así generamos la deformación de esa forma. 

         fj es la posición radial, la distancia desde el origen hasta el punto
         fi es la posición angular, el ángulo que conecta el origen del punto con la   
            dirección horizontal positiva en sentido antihorario

         Por ejemplo cuando fi = 0 para todo fj, estamos cogiendo la primera fila de la imagen

      */

      // Respuesta correcta del ejercicio
      // cc_tt_ver.push_back({fj, fi});
   
   }


   for( unsigned i= 0 ; i < ni-1 ; i++ )
   for( unsigned j= 0 ; j < nj-1 ; j++ )
   {
      triangulos.push_back({ i*nj+j, i*nj+(j+1), (i+1)*nj+(j+1) });
      triangulos.push_back({ i*nj+j, (i+1)*nj+(j+1), (i+1)*nj+j });
   }
}

// EJERCICIO ADICIONAL EXAMEN P4

Piramide::Piramide(){

   vertices = {

      // base 
      {1.0, 0.0, 1.0},
      {1.0, 0.0, -1.0},
      {-1.0, 0.0, -1.0},
      {-1.0, 0.0, 1.0},

      // punta
      {0.0, 1.0, 0.0},

      // base
      {1.0, 0.0, 1.0},
      {1.0, 0.0, -1.0},
      {-1.0, 0.0, -1.0},
      {-1.0, 0.0, 1.0},
      
      // punta
      {0.0, 1.0, 0.0},
   };

   triangulos = {
      {0, 1, 4},
      {2, 3, 4},
      
      {8, 5, 9},
      {6, 7, 9},
   };

   // Piramide rayada en vertical

   cc_tt_ver = {
      
      {0.0, 0.0}, // inferior-izquierda
      {1.0, 0.0}, // inferior derecha
      {1.0, 1.0}, 
      {0.0, 1.0},
      {0.5, 0.5},

      // esta la meto al reves, asi tiene esa forma la pirámide
      {1.0, 0.0},
      {1.0, 1.0},
      {0.0, 1.0},
      {0.0, 0.0},
      {0.5, 0.5},
   };

   // Piramide rayada en horizontal

   // cc_tt_ver = {
   //    {0.0, 0.0},
   //    {0.0, 1.0},
   //    {1.0, 1.0},
   //    {1.0, 0.0},
   //    {0.5, 0.5},

   //    {0.0,1.0},
   //    {1.0,1.0},
   //    {1.0,0.0},
   //    {0.0,0.0},
   //    {0.5,0.5},
   // };
}

// ****************************************************************************  

MallaEXP4::MallaEXP4(){

   vertices = {
      
      {cos( (2.0*M_PI) / 3.0 ), 0.0, -sin( (2.0*M_PI) / 3.0 )}, // -0.5, 0.0, -0.866
      {1.0, 0.0, 0.0},
      {0.0, 1.0, 0.0},
      {cos( (2.0*M_PI) / 3.0 ), 0.0, sin( (2.0*M_PI) / 3.0 )}, // -0.5, 0.0, 0.866

      {cos( (2.0*M_PI) / 3.0 ), 0.0, -sin( (2.0*M_PI) / 3.0 )}, // -0.5, 0.0, -0.866
      {1.0, 0.0, 0.0},
      {0.0, 1.0, 0.0},
      {cos( (2.0*M_PI) / 3.0 ), 0.0, sin( (2.0*M_PI) / 3.0 )}, // -0.5, 0.0, 0.866

      {cos( (2.0*M_PI) / 3.0 ), 0.0, -sin( (2.0*M_PI) / 3.0 )}, // -0.5, 0.0, -0.866
      {1.0, 0.0, 0.0},
      {0.0, 1.0, 0.0},
      {cos( (2.0*M_PI) / 3.0 ), 0.0, sin( (2.0*M_PI) / 3.0 )},  // -0.5, 0.0, 0.866
   
   };

   triangulos = {
      {0, 2, 1},
      {4, 5, 3},
      {6, 8, 7},
      {9, 10, 11},
   };

   // Rayas hacia arriba

   cc_tt_ver = {
      {1.0, 1.0-0.0},
      {0.0, 1.0-0.0},
      {0.5, 1.0-1.0},

      {0.0, 1.0-0.0},
      {0.5, 1.0-1.0},
      {1.0, 1.0-0.0},

      {0.5, 1.0-1.0},
      {1.0, 1.0-0.0},
      {0.0, 1.0-0.0},

      {1.0, 1.0-0.0},
      {0.5, 1.0-1.0},
      {0.0, 1.0-0.0},
   };

   // Rayas hacia el lado

   // cc_tt_ver = {
   //    {0.0, 0.0},
   //    {0.0, 1.0},
   //    {1.0, 0.5},

   //    {1.0, 0.5},
   //    {0.0, 0.0},
   //    {0.0, 1.0},

   //    {1.0, 0.5},
   //    {0.0, 1.0},
   //    {0.0, 0.0},

   //    {0.0, 0.0},
   //    {1.0, 0.5},
   //    {0.0, 1.0},
   // };

   calcularNormales();
}