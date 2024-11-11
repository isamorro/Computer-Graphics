// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A

#ifndef ANIMACION_H
#define ANIMACION_H

#include "objeto3d.h"
#include "ig-aux.h"

// #####################################
// Funciones usadas para animacion:
// ####################################



// Función  que actuliza periodicamente el estado del objeto
// Si el objeto no tiene parámetros: no hace nada y devuelve false
// En otro caso:
//    calcula el tiempo real transcurrido desde la última llamada a esta función
//    actualiza el estado del objeto, usando ese tiempo transcurrido

bool ActualizarEstado( Objeto3D & objeto ) ;

// devuelve true sii las nimaciones están activadas
bool AnimacionesActivadas() ;

// gestiona una tecla correspondiente a animaciones (se llama cuando se pulsa una
// tecla la vez que la tecla 'A' está pulsada)
bool ProcesarTeclaAnimacion( Objeto3D * objeto, int glfw_key ) ;

#endif // ANIMACION_H
