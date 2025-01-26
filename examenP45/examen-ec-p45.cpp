// Nombre: Isabel, Apellidos: Morro Tabares, Titulación: GIM
// Email: isabelmorro@correo.ugr.es, DNI: 79095945A 

#include "examen-ec-p45.h"


// Ejercicio práctica 4

Piramide::Piramide(){

   vertices = {

      {1.0, 0.0, 1.0},   // 0
      {1.0, 0.0, -1.0},  // 1
      {-1.0, 0.0, -1.0}, // 2
      {-1.0, 0.0, 1.0},  // 3
      {0.0, 2.0, 0.0},   // 4
      {1.0, 0.0, 1.0},   // 5
      {1.0, 0.0, -1.0},  // 6
      {-1.0, 0.0, -1.0}, // 7
      {-1.0, 0.0, 1.0},  // 8
      {0.0, 2.0, 0.0},   // 9
      {1.0, 0.0, 1.0},   // 10
      {1.0, 0.0, -1.0},  // 11
      {-1.0, 0.0, -1.0}, // 12
      {-1.0, 0.0, 1.0},  // 13
   };

   triangulos = {

      {0, 1, 4}, 
      {2, 3, 4}, 
      {8, 5, 9}, 
      {6, 7, 9},
      {10 ,11, 12},
      {10, 12, 13}
   };

   cc_tt_ver = {
      
      {0.0, 1.0}, // 0 
      {1.0, 1.0}, // 1
      {0.0, 1.0}, // 2
      {1.0, 1.0}, // 3
      {0.5, 0.0}, // 4

      {1.0, 1.0}, // 5
      {0.0, 1.0}, // 6
      {1.0, 1.0}, // 7
      {0.0, 1.0}, // 8
      {0.5, 0.0}, // 9

      {0.0, 0.0}, // 10
      {1.0, 0.0}, // 11
      {1.0, 1.0}, // 12
      {0.0, 1.0}  // 13
   };

   calcularNormales();

}

PiramideNodo::PiramideNodo(){

   Textura *textura = new Textura("window-icon.jpg");
   Material *material = new Material(textura, 0.7, 0.5, 0, 30.0);

   ponerNombre("Piramide");
   agregar(material);
   agregar(new Piramide());

}

// Ejercicio práctica 5

MallaP5::MallaP5 (glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {

    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);

    ponerColor(glm::vec3(1.0, 1.0, 1.0));
    triangulos.push_back({0, 1, 2});
    calcularNormales();

}

TrianguloNodo::TrianguloNodo(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3){

    ponerColor(glm::vec3(1.0,1.0,1.0));
    agregar(new MallaP5 (v1, v2, v3));
}

bool TrianguloNodo::cuandoClick(const glm::vec3 & centro_wc){

   if(leerColor() == glm::vec3(1.0,1.0,1.0)) ponerColor(glm::vec3(1.0,0.0,0.0)); // rojo
   else ponerColor(glm::vec3(1.0,1.0,1.0));
}

NodoP5::NodoP5(){

    NodoGrafoEscena *objeto = new NodoGrafoEscena();
    unsigned int identificador = 1;

    NodoGrafoEscena *triangulos = new NodoGrafoEscena();

    TrianguloNodo *t1 = new TrianguloNodo ({1.0, 0.0, 1.0}, {1.0, 0.0, -1.0}, {0.0, 2.0, 0.0});
    t1->ponerNombre("Triańgulo 1");
    t1->ponerIdentificador(identificador);
    identificador++;
    vec3 centro = vec3{1.0, 0.0, 1.0} + vec3{1.0, 0.0, -1.0} + vec3{0.0, 2.0, 0.0};
    t1->ponerCentroOC((centro / vec3{3, 3, 3}));
    triangulos->agregar(t1);

    TrianguloNodo *t2 = new TrianguloNodo ({-1.0, 0.0, -1.0}, {-1.0, 0.0, 1.0}, {0.0, 2.0, 0.0});
    t2->ponerNombre("Triańgulo 2");
    t2->ponerIdentificador(identificador);
    identificador++;
    centro = vec3{-1.0, 0.0, -1.0} + vec3{-1.0, 0.0, 1.0} +vec3 {0.0, 2.0, 0.0};
    t2->ponerCentroOC((centro / vec3{3, 3, 3}));
    triangulos->agregar(t2);

    TrianguloNodo *t3 = new TrianguloNodo ({-1.0, 0.0, 1.0}, {0.0, 2.0, 0.0}, {1.0, 0.0, 1.0});
    t3->ponerNombre("Triańgulo 3");
    t3->ponerIdentificador(identificador);
    identificador++;
    centro = vec3{-1.0, 0.0, 1.0} + vec3{0.0, 2.0, 0.0} + vec3{1.0, 0.0, 1.0};
    t3->ponerCentroOC((centro / vec3{3, 3, 3}));
    triangulos->agregar(t3);

    TrianguloNodo *t4 = new TrianguloNodo ({1.0, 0.0, -1.0}, {-1.0, 0.0, -1.0}, {0.0, 2.0, 0.0});
    t4->ponerNombre("Triańgulo 4");
    t4->ponerIdentificador(identificador);
    identificador++;
    centro = vec3{1.0, 0.0, -1.0} + vec3{-1.0, 0.0, -1.0} + vec3{0.0, 2.0, 0.0};
    t4->ponerCentroOC((centro / vec3{3, 3, 3}));
    triangulos->agregar(t4);

    TrianguloNodo *t5 = new TrianguloNodo ({1.0, 0.0, 1.0}, {1.0, 0.0, -1.0}, {-1.0, 0.0, -1.0});
    t5->ponerNombre("Triańgulo 5");
    t5->ponerIdentificador(identificador);
    identificador++;
    centro = vec3{1.0, 0.0, 1.0} + vec3{1.0, 0.0, -1.0} + vec3{-1.0, 0.0, -1.0};
    t5->ponerCentroOC((centro / vec3{3, 3, 3}));
    triangulos->agregar(t5);

    TrianguloNodo *t6 = new TrianguloNodo ({1.0, 0.0, 1.0}, {-1.0, 0.0, -1.0}, {-1.0, 0.0, 1.0});
    t6->ponerNombre("Triańgulo 6");
    t6->ponerIdentificador(identificador);
    identificador++;
    centro = vec3{1.0, 0.0, 1.0} + vec3{-1.0, 0.0, -1.0} + vec3{-1.0, 0.0, 1.0};
    t6->ponerCentroOC((centro / vec3{3, 3, 3}));
    triangulos->agregar(t6);

    objeto->agregar(triangulos);
    agregar(objeto);
}