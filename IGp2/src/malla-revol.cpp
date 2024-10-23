// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas creadas por revolución de un perfil (implementación). Clase 'MallaRevol' y derivadas.
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Implementación de las clases 
// **    + MallaRevol: malla indexada de triángulos obtenida por 
// **      revolución de un perfil (derivada de MallaInd)
// **    + MallaRevolPLY: malla indexada de triángulos, obtenida 
// **      por revolución de un perfil leído de un PLY (derivada de MallaRevol)
// **    + algunas clases derivadas de MallaRevol
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
#include "lector-ply.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************

// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<glm::vec3> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   using namespace glm ;
   
   // Práctica 2: implementar algoritmo de creación de malla de revolución
   // Escribir el algoritmo de creación de una malla indexada por revolución de un 
   // perfil, según se describe en el guion de prácticas.

   //Partimos de las tablas de vértices y triángulos vacías
   vertices=std::vector<glm::vec3>();
   triangulos=std::vector<glm::uvec3>();
   unsigned int m=perfil.size();
   unsigned int n=num_copias;

   //Completamos vértices
   for(unsigned int i=0; i<n; i++){
      for(unsigned int j=0; j<m; j++){
         //obtener las coordenadas del punto perfil[j] girado 2pi*i/(n-1) sobre Y
         glm::vec3 q,p_j=perfil[j];
         float c=cos(float(2*M_PI*i)/(n-1));
         float s=sin(float(2*M_PI*i)/(n-1));
         q[0]=c*p_j[0]+s*p_j[2];
         q[1]=p_j[1];
         q[2]=-s*p_j[0]+c*p_j[2];

         vertices.push_back(q);
      }
   }

   //Completamos triangulos
   for(unsigned int i=0; i<n-1; i++){
      for(unsigned int j=0; j<m-1; j++){
         unsigned int k=i*m +j;
         triangulos.push_back({k, k+m, k+m+1});
         triangulos.push_back({k, k+m+1, k+1});
      }
   }
}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // Práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   
   std::vector<glm::vec3> perfil;
   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles);
}


// ----------------------EJERCICIOS OBLIGATORIOS------------------------------

// Base de centro el origen
// Centro y altura valen 1

Cilidndro::Cilidndro
(
   const int num_verts_per,   // número de vertices del perfil original
   const unsigned nperfiles   // número de perfiles
) 
{

   ponerNombre( "cilindro por revolución");

   std::vector<glm::vec3> perfil = std::vector<glm::vec3>();

   for(int i=0; i<num_verts_per; i++){
      float y = i*(1.0/(num_verts_per-1));
      perfil.push_back(glm::vec3(1.0,y,0.0));
   }
   
   inicializar(perfil,nperfiles);

}

// -----------------------------------------------------------------------------

// Base de centro el origen
// Centro y altura valen 1

Cono::Cono
(
   const int num_verts_per,   // número de vertices del perfil original
   const unsigned nperfiles   // número de perfiles
)
{

   ponerNombre("cono por revolución");

   std::vector<glm::vec3> perfil = std::vector<glm::vec3>();

   for (int i=0; i < num_verts_per; i++){

      // Calculamos la altura de forma equidistante con el eje central de referencia
      float y = i*(1.0/(num_verts_per -1));
      // Calculamos el punto x de forma equidistante a lo largo del radio del cono
      // Calculamos desde radio hasta el centro
      float x = (num_verts_per - 1 - i)*(1.0/(num_verts_per - 1));
      perfil.push_back(glm::vec3(x, y, 0.0));
   }

   inicializar(perfil, nperfiles);
}

// -----------------------------------------------------------------------------

// Base de centro el origen
// Radio vale 1

Esfera::Esfera
(
   const int num_verts_per,   // número de vertices del perfil original
   const unsigned nperfiles   // número de perfiles  
)
{

   ponerNombre("esfera por revolución");
   
   float radio = 1;
   float pi = M_PI;
   std::vector<glm::vec3> perfil = std::vector<glm::vec3>();

   perfil.push_back(glm::vec3(0.0, -radio, 0.0));

   for(int i=0; i < num_verts_per; i++){

      float angulo = ((i+1)*pi) / num_verts_per;

      std::vector<std::vector<float>> matriz_rotacion = 
      {  {cos(angulo), -sin(angulo), 0},
         {sin(angulo), cos(angulo), 0},
         {0, 0, 1},
      };

      glm::vec3 vertice = {
         matriz_rotacion[0][0] * 0.0 + matriz_rotacion[0][1] * -radio + matriz_rotacion[0][2] * 0.0,
         matriz_rotacion[1][0] * 0.0 + matriz_rotacion[1][1] * -radio + matriz_rotacion[1][2] * 0.0,
         matriz_rotacion[2][0] * 0.0 + matriz_rotacion[2][1] * -radio + matriz_rotacion[2][2] * 0.0,
      };

      perfil.push_back(vertice);
   }

   inicializar(perfil, nperfiles);
}



