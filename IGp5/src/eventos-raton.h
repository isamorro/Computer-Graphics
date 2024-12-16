// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A

#ifndef EVENTOS_RATON_H 
#define EVENTOS_RATON_H 

#include "ig-aux.h"  // include cabeceras de opengl / glfw / glew



// --------------------------------------------------------------------
// función gestora del evento de hacer scroll
// (se registra con 'glfwSetScrollCallback'

void FGE_Scroll( GLFWwindow* window, double xoffset, double yoffset  );

// --------------------------------------------------------------------
// función gestora del evento de pulsar/levantar tecla del ratón
// (se registra con 'glfwSetMouseButtonCallback'

void FGE_PulsarLevantarBotonRaton( GLFWwindow* window, int button, int action, int mods );

// --------------------------------------------------------------------
// función gestora del evento de ratón movido a una nueva posición
// (se registra con 'glfwSetCursorPosCallback'

void FGE_MovimientoRaton( GLFWwindow* window, double xpos, double ypos );
#endif 