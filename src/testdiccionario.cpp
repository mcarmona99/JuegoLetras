/*
Estructuras de Datos
ETSIIT, UGR
Jose Saldaña Mercado 76424266G && Manuel Carmona Perez 17482989E
Grupo D-2

Práctica final: test diccionario
Test para el TDA Diccionario
Este programa permitirá comprobar el buen funcionamiento del T.D.A Diccionario,
representado como un set. 
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Diccionario.h"


int main(int argc, char* argv[]){
  if (argc!=2){
    cout << "Los parametros son:"<<endl;
    cout << "1.- El fichero con las palabras\n";
    return 0;
  }

  ifstream f(argv[1]);
  if (!f){
    cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
    return 0;
  }

  Diccionario D;

  cout<< "Cargando diccionario..." << endl;

  f>>D;

  cout<<"Leido el diccionario..."<<endl;

  cout << D;

  int longitud;

  cout << "Dime la longitud de las palabras que quieres ver: ";
  cin >> longitud;

  vector<string> v= D.PalabrasLongitud(longitud);

  cout <<"\nPalabras de longitud "<<longitud<<endl;

  for(unsigned int i=0;i<v.size();++i)
    cout << v[i] << endl;

  string p;

  cout << "Dime una palabra: ";
  cin >> p;

  if(D.Esta(p)) cout << "\nSí, esa palabra existe"<< endl;
  else cout << "\nEsa palabra no existe"<< endl;

}
