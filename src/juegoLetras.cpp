/*
Estructuras de Datos
ETSIIT, UGR
Jose Saldaña Mercado 76424266G & Manuel Carmona Perez 17482989E
Grupo D-2

Práctica final: Letras
Modulo Juego
*/

#include "letras.h"
#include "Diccionario.h"
#include <fstream>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <set>
#include <algorithm>

using namespace std;

// Funcion para calcular puntuaciones
// Recibe la palabra a la que calcular puntuacion,
// el modo de juego (P o L) y la bolsa de letras
int calcularPuntuacion(string solucion, string modo, Letras bolsa){
  int puntuacion = 0;
  if (modo == "L"){ // Modo Longitud
    puntuacion = solucion.size();
  } else { // Modo Puntuación
    multiset<char> conjuntoSolucion;
    multiset<char>::iterator mit;
    int i;
    i = 0;
    char aux = solucion[i];
    while (aux != '\0'){
      conjuntoSolucion.insert(aux);
      i++;
      aux = solucion[i];
    }
    map<char,info>::iterator p;
    for (mit=conjuntoSolucion.begin(); mit!=conjuntoSolucion.end(); ++mit){
      p = bolsa.getDatos().find(*mit);
      puntuacion = puntuacion + (*p).second.puntuacion;
    }
  }
  return puntuacion;
}


// Funcion para comprobar que la palabra que damos pertenece al conjunto de letras
// Recibe la palabra que queremos comprobar que sea correcta y
// el conjunto de letras que nos da el juego para formar palabras
bool perteneceConjuntoLetras(string palabra,multiset<char> conjunto){
  bool correcto = false;
  multiset<char> conjuntoSolucion;
  int i=0;
  char aux;
  multiset<char>::iterator mit;

  // Comprobamos si se han usado correctamente las letras
  // Metemos la solucion en otro multiset
  aux = palabra[i];
  while (aux != '\0'){
    conjuntoSolucion.insert(aux);
    ++i;
    aux = palabra[i];
  }

  // Comprobamos que el multiset solucion esta contenido en el multiset bolsaDeLetras
  correcto = true;
  for (mit=conjuntoSolucion.begin(); mit!=conjuntoSolucion.end(); ++mit){
    if (conjuntoSolucion.count(*mit) > conjunto.count(*mit)){
      correcto = false;
      break; //ahorra tiempo al parar el bucle cuando repetimos letra
    }
  }

  return correcto;
}

// Operador para imprimir un multiset
ostream & operator<<(ostream & os, multiset<char> conjunto){
  multiset<char>::iterator mit;
  for (mit=conjunto.begin();mit!=conjunto.end();++mit){
    cout << " " << *mit;
  }

}

// Funcion para transformar multiset a string
string multisetToString(multiset<char> conjunto){
  string resultado="";
  multiset<char>::iterator mit;
  for (mit=conjunto.begin(); mit!=conjunto.end(); ++mit){
    resultado = resultado + (*mit);
  }
  return resultado;
}



// ------------------
// PROGRAMA PRINCIPAL
// ------------------

int main(int argc, char *argv[]){

  // check args
  if (argc != 4){
    cout << "Introducir:\n" << "1. El nombre del fichero con el diccionario\n" << "2. El número de letras que se deben generar de forma aleatoria\n";
    cout << "3. Modalidad de juego:\n L Longitud: se buscará la palabra más larga.\n P Puntuación: se obtendrá la palabra de mayor puntuación.\n";
    return 0;
  }
  char *modojuego=argv[3]; //variable para cambiar el modo de juego
  if ((strcmp(modojuego, "P")!=0) && (strcmp(modojuego, "L")!=0)){
    cout << "Error al elegir modo de juego\n";
    cout << "3. Modalidad de juego:\n L Longitud: se buscará la palabra más larga.\n P Puntuación: se obtendrá la palabra de mayor puntuación.\n";
    return 0;
  }

  // Se elige un diccionario para jugar
  string direccion = argv[1];
  // ./datos/diccionario*.txt
  ifstream f(direccion);
  if (!f){
      cout << "No puedo abrir el fichero " << direccion << endl;
      return 0;
  }

  // Se genera la bolsa de letras
  Letras bolsa;
  f >> bolsa;
  vector<char> bolsaDeLetras;
  Letras::iterator it;
  for (it=bolsa.begin(); it!=bolsa.end();++it){
    for (int i = 0; i < (*it).second.apariciones; ++i){
      bolsaDeLetras.push_back((*it).first);
    }
  }

  string juegonuevo; //variable para repetir juego
  string cambioOpciones; //variable para cambiar opciones
  int numLetras = stoi(argv[2]);
  multiset<char>::iterator mit;

  do{

    // Se muestran por pantalla la bolsa de letras asociada al diccionario en caso de modo PUNTUACION
    if (strcmp(modojuego, "P")==0){
      cout << "La bolsa de letras asociada al diccionario " << direccion << " tiene en total : " << bolsa.letrasTotales() << endl;
      cout << bolsa << endl;
    }

    // Inicializamos juego
    multiset<char> conjuntoLetras;
    int posicionAleatoria;
    srand(time(NULL));
    for (int i = 0; i < numLetras; ++i){
      posicionAleatoria = rand() % bolsaDeLetras.size();
      char aux = bolsaDeLetras[posicionAleatoria];
      conjuntoLetras.insert(aux);
    }


    cout << endl << endl << "---COMIENZO DE JUEGO---" << endl;
    cout << endl << "Las letras son: " << conjuntoLetras;

    cout << endl << "Dime tu solucion: ";
    string solucion;
    cin >> solucion;

    // Se comprueba si hemos usado las letras que nos da el juego
    while (!perteneceConjuntoLetras(solucion,conjuntoLetras)){
      cout << endl << "Palabra no valida, dime tu solucion: ";

      cin >> solucion;
    }


    // Cargamos Diccionario
    Diccionario diccionario;
    ifstream g(direccion);
    g>>diccionario;

    int puntuacion;
    // Comprobamos si solucion esta en el Diccionario
    if(diccionario.Esta(solucion)){
      // calculamos puntuacion
      puntuacion = calcularPuntuacion(solucion,modojuego, bolsa);

      cout << endl << solucion << " PUNTUACION = " << puntuacion << endl;
    } else {
      cout << endl << "Palabra introducida no esta en el diccionario. PUNTUACION = 0" << endl << endl;
    }

    // Se muestran soluciones de la maquina
    vector<string> solucionesMaquina;
    int punt_max = 0;
    string letrasParaJugar;
    letrasParaJugar=multisetToString(conjuntoLetras);


    if (strcmp(modojuego, "L")==0) { // Modo Longitud
      int longSolucion = numLetras;
      bool encontrada = false;
      while (!(encontrada) && (longSolucion > 0)){
        vector<string> vectorAuxiliar = diccionario.PalabrasLongitud(longSolucion);
        for (int i = 0; i < vectorAuxiliar.size(); i++){
          if (perteneceConjuntoLetras(vectorAuxiliar[i],conjuntoLetras)){
            solucionesMaquina.push_back(vectorAuxiliar[i]);
          }
        }
        if (solucionesMaquina.size() > 0) {
          encontrada = true;
        } else {
          longSolucion--;
        }
      }
        if (encontrada){
          puntuacion = calcularPuntuacion(solucionesMaquina[0], modojuego, bolsa);
          cout << endl << "Mis soluciones son:" << endl;
          for (int i = 0; i < solucionesMaquina.size(); ++i){
            cout << solucionesMaquina[i] << " Puntuacion: " << puntuacion << endl;
          }
        } else {
          cout << endl << "No encuentro solucion" << endl;
        }
    } else { // Modo Puntuacion
      int puntuacionMaxima = 0;
      int puntuacionSolucion = 0;
      Diccionario::iterator dic;
      for (dic = diccionario.begin(); dic !=diccionario.end(); ++dic){
        if (perteneceConjuntoLetras(*dic,conjuntoLetras)){
          puntuacionSolucion = calcularPuntuacion(*dic, modojuego, bolsa);
          if (puntuacionSolucion > puntuacionMaxima){
            solucionesMaquina.clear();
            solucionesMaquina.push_back(*dic);
            puntuacionMaxima = puntuacionSolucion;
          } else if (puntuacionSolucion == puntuacionMaxima){
            solucionesMaquina.push_back(*dic);
          }
        }
      }
        if (solucionesMaquina.size() > 0){
          puntuacion = calcularPuntuacion(solucionesMaquina[0], modojuego, bolsa);
          cout << endl << "Mis soluciones son:" << endl;
          for (int i = 0; i < solucionesMaquina.size(); ++i){
            cout << solucionesMaquina[i] << " Puntuacion: " << puntuacion << endl;
          }
        } else {
          cout << endl << "No encuentro solucion" << endl;
        }
    }

    cout << endl << "¿Quieres volver a jugar (s/n)? " ;

    cin >> juegonuevo;

    if ((juegonuevo == "s") || (juegonuevo == "S")){

      cout << endl << "¿Quieres cambiar las opciones (s/n)? ";

      cin >> cambioOpciones;

      if ((cambioOpciones == "s") || (cambioOpciones == "S")){

        do{
          cout << endl << "Cambio de modo de juego: " ;
          cin >> modojuego;
        }while ((strcmp(modojuego, "P")!=0) && (strcmp(modojuego, "L")!=0));

        cout  << "Cambio de numero de letras: " ;
        cin >> numLetras;

      }
    }
  }while((juegonuevo == "s") || (juegonuevo == "S"));
 return (0);
}
