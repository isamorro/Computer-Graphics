// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A

#include "ig-aux.h"  
#include "grafo-escena.h"
#include "aplicacion-ig.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 
#include "malla-ind.h"
#include "malla-revol.h"


// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != nullptr );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const glm::mat4 & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new glm::mat4() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != nullptr );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

NodoGrafoEscena::NodoGrafoEscena()
{

}

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL(  )
{
   using namespace std ;
   assert( aplicacionIG != nullptr );

   //cout << "Entra " << __FUNCTION__ << ": " << leerNombre() << endl ;

    // comprobar que hay un cauce y una pila de materiales y recuperarlos.
   Cauce *          cauce           = aplicacionIG->cauce ;           assert( cauce != nullptr );
   PilaMateriales * pila_materiales = aplicacionIG->pila_materiales ; assert( pila_materiales != nullptr );

   // Práctica 3: implementar la visualización del nodo

   // 1. Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //     - hacer push del color actual del cauce (con 'pushColor') y después
   //     - fijar el color en el cauce (con 'fijarColor'), usando el color del objeto (se lee con 'leerColor()')
   
   if (tieneColor()){
      cauce->pushColor();
      cauce->fijarColor(leerColor());
   }
   
   // Práctica 4: al inicio, hacer 'push' de la pila de materiales (guarda material actual en la pila)
   // Diapositiva 211 tema 3
   if (aplicacionIG->iluminacion) pila_materiales->push(); 

   // 2. Guardar copia de la matriz de modelado (con 'pushMM'), 

   cauce->pushMM();

   // 3. Para cada entrada del vector de entradas (diapositiva 183 tema 2)

   for (unsigned i=0; i < entradas.size(); i++){
      switch(entradas[i].tipo)
      {
         
         // si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGL'
         case TipoEntNGE::objeto:
            entradas[i].objeto->visualizarGL();
            break;
         
         // si la entrada es de tipo transformación: componer la matriz
         case TipoEntNGE::transformacion:
            cauce->compMM(*(entradas[i].matriz));
            break;

         // Práctica 4: si una entrada es de tipo material, activarlo usando a pila de materiales
         // Diapositiva 211 tema 3
         case TipoEntNGE::material:
         if (aplicacionIG->iluminacion)
            pila_materiales->activar(entradas[i].material);
      }
   }


   // 4. Restaurar la copia guardada de la matriz de modelado (modelview)
   cauce->popMM();

   // 5. Si el objeto tiene color asignado:
   // restaurar el color original a la entrada (con 'popColor')
   if (tieneColor()) {
      cauce->popColor();
   }


   // Práctica 4: añadir gestión de los materiales cuando la iluminación está activada    
   // Al finalizar, hacer 'pop' de la pila de materiales (restaura el material activo al inicio)
   // Diapositiva 211 tema 3
   if (aplicacionIG->iluminacion) pila_materiales->pop();

}

// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...

void NodoGrafoEscena::visualizarGeomGL(  )
{
   using namespace std ;
   // comprobar que hay un cauce 
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce; assert( cauce != nullptr );
  
   // Práctica 3: implementar la visualización del nodo (ignorando colores)
   
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', pero más simple,
   
   // 1. Guardar copia de la matriz de modelado (con 'pushMM'), 
   
   cauce->pushMM();
   
   // 2. Para cada entrada del vector de entradas:
   //         - Si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGeomGL'.
   //         - Si la entrada es de tipo transformación: componer la matriz (con 'compMM').
   
   for (unsigned i = 0; i < entradas.size(); i++){
      switch (entradas[i].tipo)
      {
         case TipoEntNGE::objeto:
            entradas[i].objeto->visualizarGL();
            break;

         case TipoEntNGE::transformacion:
            cauce->compMM(*(entradas[i].matriz));
            break;
      }
   }
   
   //   3. Restaurar la copia guardada de la matriz de modelado (con 'popMM')
   
   cauce->popMM();

}

// -----------------------------------------------------------------------------
// Visualizar las normales de los objetos del nodo

void NodoGrafoEscena::visualizarNormalesGL(  )
{
   using namespace std ;

   // comprobar que hay un cauce 
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce; assert( cauce != nullptr );
  

   // Práctica 4: visualizar las normales del nodo del grafo de escena
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', teniendo 
   // en cuenta estos puntos:

   // usar push/pop de la matriz de modelado al inicio/fin (al igual que en visualizatGL)
   cauce->pushMM();

   // recorrer las entradas, llamando recursivamente a 'visualizarNormalesGL' en los nodos u objetos hijos
   // ignorar las entradas de tipo material, y la gestión de materiales (se usa sin iluminación)
   // ignorar el color o identificador del nodo (se supone que el color ya está prefijado antes de la llamada)
   for (int i=0; i < entradas.size(); i++){
      switch (entradas[i].tipo)
      {
         case TipoEntNGE::objeto:
            entradas[i].objeto->visualizarNormalesGL();
            break;
         
         case TipoEntNGE::transformacion:
            cauce->compMM(*entradas[i].matriz);
            break;
      }
   }
   
   cauce->popMM();
}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void NodoGrafoEscena::visualizarModoSeleccionGL()
{
   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar este nodo en modo selección.
   //
   // Se debe escribir código para dar estos pasos:
   // 
   // 2. Leer identificador (con 'leerIdentificador'), si el identificador no es -1 
   //      + Guardar una copia del color actual del cauce (con 'pushColor')
   //      + Fijar el color del cauce de acuerdo al identificador, (usar 'ColorDesdeIdent'). 
   // 3. Guardar una copia de la matriz de modelado (con 'pushMM')
   // 4. Recorrer la lista de nodos y procesar las entradas transformación o subobjeto:
   //      + Para las entradas subobjeto, invocar recursivamente a 'visualizarModoSeleccionGL'
   //      + Para las entradas transformación, componer la matriz (con 'compMM')
   // 5. Restaurar la matriz de modelado original (con 'popMM')   
   // 6. Si el identificador no es -1, restaurar el color previo del cauce (con 'popColor')
   //
   // ........


}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
   // Práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada
   
   entradas.push_back(entrada);
   return entradas.size() - 1 ;

}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const glm::mat4 & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
glm::mat4 * NodoGrafoEscena::leerPtrMatriz( unsigned indice )
{

   // Práctica 3: leer un puntero a una matriz en una entrada de un nodo
   // (diap 193)

   assert( indice < entradas.size() );
   assert( entradas[indice].tipo == TipoEntNGE::transformacion );
   assert( entradas[indice].matriz != nullptr );
   
   return entradas[indice].matriz ;
}

// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{
   using namespace std ;
   using namespace glm ;

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   // ........

}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto
(
   const int          ident_busc, // identificador a buscar
   const glm::mat4 &  mmodelado,  // matriz de modelado
   Objeto3D       **  objeto,     // (salida) puntero al puntero al objeto
   glm::vec3 &        centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{
   using namespace std ;
   using namespace glm ;
   
   assert( 0 < ident_busc );

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:

   // 1. calcula el centro del objeto, (solo la primera vez)
   // ........


   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   // ........


   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   // ........


   // ni este nodo ni ningún hijo es el buscado: terminar
   return false ;
}

// *********************************************************************
// Práctica 4: NodoCubo24

NodoCubo24::NodoCubo24()
{

   Textura *ugr = new Textura ("window-icon.jpg");
   agregar( new Material(ugr, 0.5, 0.3, 0.7, 100.0));
   agregar(new Cubo24());

}

// *********************************************************************
// EJERCICIOS OPCIONALES PRÁCTICA 3

// EJERCICIO 1

GrafoEstrellaX::GrafoEstrellaX(unsigned n){

   assert (n>1);

   unsigned identificador = 1;
   float radio  = 1.3f;
   float angulo = (2*M_PI) / n;
   float escala_estrella = radio / 0.5f;
   float escala_cono_radio = 0.14f / 1.3f;
   float escala_cono_altura = 0.15f / 1.3f;

   ponerNombre("GrafoEstrellax");
   NodoGrafoEscena *grafo = new NodoGrafoEscena();

   NodoGrafoEscena *estrella = new NodoGrafoEscena();
   estrella->ponerNombre("nodo de la estrella");
   estrella->ponerIdentificador(identificador);
   identificador++;
   unsigned indice_rotacion = estrella->agregar(rotate(0.0f, vec3(1.0, 0.0, 0.0)));
   estrella->agregar(scale(vec3(escala_estrella, escala_estrella, escala_estrella)));
   estrella->agregar(rotate(float(M_PI/2), vec3(0.0, 1.0, 0.0)));
   estrella->agregar(translate(vec3(-0.5, -0.5, 0.0)));
   estrella->agregar(new EstrellaZ(2*n));


   Cono *cono = new Cono(100, 10);
   for (int i=0; i < n; i++){

      NodoGrafoEscena *nodo = new NodoGrafoEscena();
      
      nodo->ponerNombre("Nodo " + identificador),
      nodo->ponerIdentificador(identificador);
      identificador++;

      nodo->agregar(translate(vec3(0.5, 0.5, 0.0)));
      nodo->agregar(translate(vec3(0.5*cos(angulo*i), 0.5*sin(angulo*i), 0.0)));
      nodo->agregar(rotate(float(angulo*i) + float(-M_PI/2), vec3(0.0, 0.0, 1.0)));
      nodo->agregar(scale(vec3(escala_cono_radio, escala_cono_altura, escala_cono_radio)));
     
      nodo->agregar(cono);
      estrella->agregar(nodo);
   }

   m_rotacion = estrella->leerPtrMatriz(indice_rotacion);

   grafo->agregar(estrella);
   agregar(grafo);

}

unsigned GrafoEstrellaX::leerNumParametros() const
{
    return 1;
}

void GrafoEstrellaX::actualizarEstadoParametro
(
    const unsigned iParam, 
    const float t_sec    
)
{
    switch (iParam) 
    {
     
        case 0: {            

            float angulo = 2.5*(2*M_PI)*t_sec;
            *m_rotacion = rotate(angulo, vec3(1.0, 0.0, 0.0));

            break;
        }
    }
}

// EJERCICIO 2

GrafoCubos::GrafoCubos(){


   ponerNombre(" GrafoCubos ");
   NodoGrafoEscena *objeto = new NodoGrafoEscena();
   
   unsigned identificador = 1;

// Cubo Central

   NodoGrafoEscena *cuboCentral = new NodoGrafoEscena();
   cuboCentral->ponerIdentificador(identificador);
   identificador++;

   cuboCentral->agregar(new CuboColores());

// Rejilla del Cubo Central

   // Rejilla parte de abajo
   NodoGrafoEscena *rejilla1 = new NodoGrafoEscena();
   rejilla1->ponerIdentificador(identificador);
   identificador++;
   rejilla1->agregar(translate(vec3(-1, -1, -1)));
   rejilla1->agregar(scale(vec3(2.0, 2.0, 2.0)));
   rejilla1->agregar(new RejillaY(5, 5));   

   // Rejilla parte de arriba
   NodoGrafoEscena *rejilla2 = new NodoGrafoEscena();
   rejilla2->ponerIdentificador(identificador);
   identificador++;
   rejilla2->agregar(translate(vec3(-1.0, 1.0, -1.0)));
   rejilla2->agregar(scale(vec3(2.0, 2.0, 2.0)));
   rejilla2->agregar(new RejillaY(5,5));

   // Rejilla lateral derecho
   NodoGrafoEscena *rejilla3 = new NodoGrafoEscena();
   rejilla3->ponerIdentificador(identificador);
   identificador++;
   rejilla3->agregar(rotate(float(M_PI/2), vec3(0.0, 0.0, 1.0)));
   rejilla3->agregar(translate(vec3(-1.0, -1.0, -1.0)));
   rejilla3->agregar(scale(vec3(2.0, 2.0, 2.0)));
   rejilla3->agregar(new RejillaY(5, 5));

   // Rejilla lateral izquierdo
   NodoGrafoEscena *rejilla4 = new NodoGrafoEscena();
   rejilla4->ponerIdentificador(identificador);
   identificador++;
   rejilla4->agregar(rotate(float(M_PI/2), vec3(0.0, 0.0, 1.0)));
   rejilla4->agregar(translate(vec3(-1.0, 1.0, -1.0)));
   rejilla4->agregar(scale(vec3(2.0, 2.0, 2.0)));
   rejilla4->agregar(new RejillaY(5, 5));

   // Rejilla frontal
   NodoGrafoEscena *rejilla5 = new NodoGrafoEscena();
   rejilla5->ponerIdentificador(identificador);
   identificador++;
   rejilla5->agregar(rotate(float(M_PI/2), vec3(1.0, 0.0, 0.0)));
   rejilla5->agregar(translate(vec3(-1.0, 1.0, -1.0)));
   rejilla5->agregar(scale(vec3(2.0, 2.0, 2.0)));
   rejilla5->agregar(new RejillaY(5, 5));

   // Rejilla trasera
   NodoGrafoEscena *rejilla6 = new NodoGrafoEscena();
   rejilla6->ponerIdentificador(identificador);
   identificador++;
   rejilla6->agregar(rotate(float(M_PI/2), vec3(1.0, 0.0, 0.0)));
   rejilla6->agregar(translate(vec3(-1.0, -1.0, -1.0)));
   rejilla6->agregar(scale(vec3(2.0, 2.0, 2.0)));
   rejilla6->agregar(new RejillaY(5, 5));


// Cubos laterales

   NodoGrafoEscena *cubo1 = new NodoGrafoEscena();
   cubo1->ponerIdentificador(identificador);
   identificador++;
   cubo1->agregar(translate(vec3(0.0, -1.4, 0.0)));
   cubo1->agregar(scale(vec3(0.25, 0.4, 0.25)));
   unsigned ind1 = cubo1->agregar(rotate(0.0f, vec3(0.0, 1.0, 0.0)));
   cubo1->agregar(new Cubo());

   NodoGrafoEscena *cubo2 = new NodoGrafoEscena();
   cubo2->ponerIdentificador(identificador);
   identificador++;
   cubo2->agregar(translate(vec3(0.0, 1.4, 0.0)));
   cubo2->agregar(scale(vec3(0.25, 0.4, 0.25)));
   unsigned ind2 = cubo2->agregar(rotate(0.0f, vec3(0.0, 1.0, 0.0)));
   cubo2->agregar(new Cubo());

   NodoGrafoEscena *cubo3 = new NodoGrafoEscena();
   cubo3->ponerIdentificador(identificador);
   identificador++;
   cubo3->agregar(translate(vec3(0.0, 0.0, 1.4)));
   cubo3->agregar(scale(vec3(0.25, 0.25, 0.4)));
   unsigned ind3 = cubo3->agregar(rotate(0.0f, vec3(0.0, 0.0, 1.0)));
   cubo3->agregar(new Cubo());  

   NodoGrafoEscena *cubo4 = new NodoGrafoEscena();
   cubo4->ponerIdentificador(identificador);
   identificador++;
   cubo4->agregar(translate(vec3(0.0, 0.0, -1.4)));
   cubo4->agregar(scale(vec3(0.25, 0.25, 0.4)));
   unsigned ind4 = cubo4->agregar(rotate(0.0f, vec3(0.0, 0.0, 1.0)));
   cubo4->agregar(new Cubo());

   NodoGrafoEscena *cubo5 = new NodoGrafoEscena();
   cubo5->ponerIdentificador(identificador);
   identificador++;
   cubo5->agregar(translate(vec3(1.4, 0.0, 0.0)));
   cubo5->agregar(scale(vec3(0.4, 0.25, 0.25)));
   unsigned ind5 = cubo5->agregar(rotate(0.0f, vec3(1.0, 0.0, 0.0)));
   cubo5->agregar(new Cubo());

   NodoGrafoEscena *cubo6 = new NodoGrafoEscena();
   cubo6->ponerIdentificador(identificador);
   identificador++;
   cubo6->agregar(translate(vec3(-1.4, 0.0, 0.0)));
   cubo6->agregar(scale(vec3(0.4, 0.25, 0.25)));
   unsigned ind6 = cubo6->agregar(rotate(0.0f, vec3(1.0, 0.0, 0.0)));
   cubo6->agregar(new Cubo());

   // Agregamos las rejillas al cubo

   cuboCentral->agregar(rejilla1);  // abajo
   cuboCentral->agregar(rejilla2);  // arriba
   cuboCentral->agregar(rejilla3);  // derecha
   cuboCentral->agregar(rejilla4);  // izquierda
   cuboCentral->agregar(rejilla5);  // frontal
   cuboCentral->agregar(rejilla6);  // fondo

   // Agregamos cubos 

   objeto->agregar(cubo1);
   objeto->agregar(cubo2);
   objeto->agregar(cubo3);
   objeto->agregar(cubo4);
   objeto->agregar(cubo5);
   objeto->agregar(cubo6);

   // Movimientos de los cubosy to

   m_cubo1 = cubo1->leerPtrMatriz(ind1);
   m_cubo2 = cubo2->leerPtrMatriz(ind2);
   m_cubo3 = cubo3->leerPtrMatriz(ind3);
   m_cubo4 = cubo4->leerPtrMatriz(ind4);
   m_cubo5 = cubo5->leerPtrMatriz(ind5);
   m_cubo6 = cubo6->leerPtrMatriz(ind6);

   objeto->agregar(cuboCentral);
   agregar(objeto);
}

unsigned GrafoCubos::leerNumParametros() const {
   return 6;
} 

void GrafoCubos::actualizarEstadoParametro
(
   const unsigned iParam,
   const float t_sec
)
{
   switch (iParam)
   {
      case 0: {
         
         float angulo = 2.5*t_sec;

         *m_cubo1 = rotate(angulo, vec3(0.0, 1.0, 0.0));
         *m_cubo2 = rotate(angulo, vec3(0.0, 1.0, 0.0));
         
         *m_cubo3 = rotate(angulo, vec3(0.0, 0.0, 1.0));
         *m_cubo4 = rotate(angulo, vec3(0.0, 0.0, 1.0));

         *m_cubo5 = rotate(angulo, vec3(1.0, 0.0, 0.0));
         *m_cubo6 = rotate(angulo, vec3(1.0, 0.0, 0.0));

         break;
      }
   }
}

// *********************************************************************
// EJERCICIOS OPCIONALES PRÁCTICA 4

// EJERCICIO 1

NodoDiscoP4::NodoDiscoP4()
{

   Textura *cuadricula = new Textura ("cuadricula.jpg");
   Material *material = new Material(cuadricula, 0.5, 0.8, 0.2, 100.0);

   ponerNombre("Nodo ejercicio adicional práctica 4, examen 27 enero");
   agregar(material);
   agregar( new MallaDiscoP4() );

}
