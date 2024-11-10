// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A

#include "aplicacion-ig.h"



// evita la necesidad de escribir std::
using namespace std ;

// ---------------------------------------------------------------------
// punto de entrada al programa

int main( int argc, char *argv[] )
{   
   
   using namespace std ;
   cout << "Prácticas de IG (GIM+GIADE) - curso 2024-25 (" << NOMBRE_OS << ")" << endl ;

   // Crear el objeto 'apl' con las variables globales de la aplicación 
   // y los diversos parámetros de configuración
   aplicacionIG = new AplicacionIG(); 
   assert( aplicacionIG != nullptr );

   // ejecuta el bucle principal de eventos y visualización 
   aplicacionIG->buclePrincipalGLFW();  

   // se ha terminado normalmente el programa (sin errores)
   delete aplicacionIG ;
   cout << "Programa terminado normalmente." << endl ;
   return 0;
}
