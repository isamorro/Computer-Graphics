// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A

#include "ig-aux.h"
#include "lector-ply.h"
#include "malla-revol.h"

using namespace std ;
using namespace glm;

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

// Práctica 4: sección 4.6.2.1 

   // calculamos m_1..m_n-2
   vector<vec3> vec_m;
   for (int i = 0; i < perfil.size() - 1; i++){

      float v1 = (perfil[i+i] - perfil[i])[0];
      float v2 = (perfil[i+i] - perfil[i])[1];

      vec3 m_aux (vec3(v2, -v1, 0.0f)); // rotado 90 grados
      if (length(m_aux) != 0.0) m_aux = normalize(m_aux); // normalizado
      vec_m.push_back(m_aux);
   }
   
   // calculamos las normales de los vectores n_0..n_n-1
   vector<vec3> vec_n;
   vec_n.push_back(vec_m[0]);
   for (int i = 1; i < perfil.size() - 1; i++) 
      vec_n.push_back(normalize(vec_m[i-1] + vec_m[i]));
   vec_n.push_back(vec_m[perfil.size()-2]);


// Práctica 4: sección 4.6.2.2

   // cálculo de las coordenadas de textura de los vértices
   
   vector<float> d;
   for (int i = 0; i < perfil.size()-1; i++)
      d.push_back(sqrt(length(perfil[i+1] - perfil[i])));
   
   vector<float> suma_numerador;
   suma_numerador.push_back(0.0f);
   for (int i=1; i < perfil.size(); i++)
      suma_numerador.push_back(suma_numerador[i-1] + d[i-1]);
   float suma_denominador = suma_numerador[perfil.size()-1];

   vector<float> t;
   t.push_back(0.0f);
   for (int i=1; i < perfil.size(); i++)
      t.push_back(suma_numerador[i]/suma_denominador);


// Práctica 2: implementar algoritmo de creación de malla de revolución

   // Escribir el algoritmo de creación de una malla indexada por revolución de un 
   // perfil, según se describe en el guion de prácticas.

   // Partimos de las tablas de vértices y triángulos vacías
   vertices=std::vector<glm::vec3>();
   triangulos=std::vector<glm::uvec3>();
   unsigned int m=perfil.size();
   unsigned int n=num_copias;

   // Completamos vértices
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

         // Práctica 4: añadimos normales (sección 4.6..2.1)
         vec3 aux = vec3(vec_n[j][0] * cos(float(2*M_PI*i)/(n-1)), 
                         vec_n[j][1], 
                         -vec_n[j][0] * sin(float(2*M_PI*i)/(n-1)));
         if (length(aux) != 0.0) normalize(aux);
         nor_ver.push_back(aux);

         // Práctica 4: añadimos coordenadas de texturas (sección 4.6.2.2)
         cc_tt_ver.push_back({float(i) / (n -1), 1 - t[j]});

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

   float altura = 1.0f;
   float radio = 1.0f; 

   for (int i=0; i < num_verts_per; i++){

      // Calculamos la altura de forma equidistante con el eje central de referencia
      float y = i*(altura/(num_verts_per -1));
      // Calculamos el punto x de forma equidistante a lo largo del radio del cono
      // Calculamos desde radio hasta el centro
      float x = (num_verts_per - 1 - i)*(radio/(num_verts_per - 1));
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

