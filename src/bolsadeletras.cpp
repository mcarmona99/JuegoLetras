/*
Estructuras de Datos
ETSIIT, UGR
Jose Saldaña Mercado 76424266G && Manuel Carmona Perez 17482989E
Grupo D-2

Práctica final: Letras
Modulo Bolsa de Letras
Este módulo será útil para el programa letras. El T.D.A Bolsa_Letras almacena caracteres
correspondientes a una letra de un Conjunto de Letras. Este carácter aparece en la
Bolsa_Letras repetido tantas veces como diga el campo cantidad de la letra. Por lo tanto en la
Bolsa de Letras aparecen las letras de forma aleatoria. En el programa “letras” la secuencia
de letras con las que se juega se cogen de la Bolsa de Letras.
*/

#include "letras.h"
#include <fstream>

int main(){

  // Se recoge un diccionario para sacar bolsa de letras
  string direccion;
  cout << "Introduce ubicación del diccionario: " << endl;
  cin >> direccion;
  // /home/jose/Dropbox/2D/ED/practica_final/ej-dic/diccionario1000.txt
  ifstream f(direccion);
  if (!f){
      cout << "No puedo abrir el fichero " << direccion << endl;
      return 0;
  }

  Letras bolsa;
  f >> bolsa;

  // Se muestran por pantalla la bolsa de letras asociada al diccionario
  cout << "Total letras en diccionario: " << bolsa.letrasTotales() << endl;
  cout << "La bolsa de letras asociada al diccionario " << direccion << endl << bolsa << endl;

  cin.clear();

 return (0);
}
