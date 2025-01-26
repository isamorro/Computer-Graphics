// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A

#ifndef SELECCION_H
#define SELECCION_H

#include "objeto3d.h"
#include "escena.h"


// calcula un color usando un identificador entero no negativo
glm::vec4 ColorDesdeIdent( const int ident )  ; // 0 ≤ ident < 2^24

// leer un identificador entero codificado en el color de un pixel en el
// framebuffer activo actualmente
int LeerIdentEnPixel( int xpix, int ypix );




#endif // SELECCION_H
