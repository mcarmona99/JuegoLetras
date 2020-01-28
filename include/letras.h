/*
Estructuras de Datos
ETSIIT, UGR
Jose Saldaña Mercado 76424266G && Manuel Carmona Perez 17482989E
Grupo D-2

Práctica final: Letras
Modulo Letra y Conjunto de Letras
El T.D.A Letra almacena una letra. Una letra se especifica con tres valores:
1. El carácter de la propia letra
2. La cantidad de veces que puede aparecer.
3. La puntuación de una letra.
El T.D.A Conjunto_Letras permitirá tener en memoria un fichero Letras. Este T.D.A se define
como una colección de letras, en las que no hay letras repetidas.
*/

#ifndef _LETRAS
#define _LETRAS
#include <cassert>
#include <iostream>
#include <map>
#include <string>

using namespace std;

struct info{
    int apariciones;
    int puntuacion;
    info (int apara, int punt){
      apariciones = apara;
      puntuacion = punt;
    }
 };

 istream & operator>>(istream &is,char &d){
   is.get(d);
   return is;
 }

 ostream & operator<<(ostream &os,const pair<const char,info> &d){
 	  os<<d.first<<'\t'<<d.second.apariciones<<"\t"<<d.second.puntuacion<<endl;
 	  return os;
 }

/**
  *  @brief T.D.A. Letra
  *
  * Una instancia @e c del tipo de datos abstracto @c Letra es un objeto
  * formado por El carácter de la propia letra, La cantidad de veces que puede aparecer en un diccionario
  * La puntuación de una letra.
  *
  *
  * @author Jose Saldaña && Manuel Carmona
  * @date Diciembre 2018
  */
class Letras {
private:
  map<char,info> datos;
public:
  // Constructor
  Letras(){
  }

  map<char,info> getDatos(){
    return datos;
  }

  // Numero de letras
  int size() const{
    return datos.size();
  }

  // Devuelve total de letras por sus apariciones
  double letrasTotales(){
    int total = 0;
    map<char,info>::iterator it;
    for (it=datos.begin();it!=datos.end();++it){
      total = total + it->second.apariciones;
    }
    return total;
  }

  /**
   @brief Insert letra
   @param letra: char letra
  */
  void insert(char letra){
    if (letra < 'a' || letra > 'z'){
      // Para filtrar posible basura en diccionarios
    } else {
    map<char,info>::iterator it;
    if (letra != '\n'){
      if (datos.count(letra) > 0){
        it = datos.find(letra);
        it->second.apariciones++;
        double total = letrasTotales();
        double proporcion = (double) it->second.apariciones/total;
        if (proporcion >= 0.100){
          it->second.puntuacion = 1;
        } else if(proporcion >= 0.05){
          it->second.puntuacion = 2;
        } else if (proporcion >= 0.025){
          it->second.puntuacion = 4;
        } else if (proporcion >= 0.02){
          it->second.puntuacion = 5;
        } else if (proporcion >= 0.01){
          it->second.puntuacion = 7;
        } else if (proporcion >= 0.005){
          it->second.puntuacion = 8;
        } else if (proporcion >= 0.001){
          it->second.puntuacion = 9;
        } else {
          it->second.puntuacion = 10;
        }
      } else {
        info nuevo(1, 10);
        pair<char,info> nuevaLetra (letra, nuevo);
        datos.insert(nuevaLetra);
      }
    }
  }
  }

  /**
    @brief Limpia las letras
   */
  void clear(){
      datos.clear();
  }

  /**
   * @brief clase para iterar sobre las letras
   * */
  class iterator{
   private:
    map<char,info>::iterator it;
   public:
     iterator & operator++(){
       ++it;
     }

     iterator & operator--(){
       --it;
     }

     pair<const char,info> &operator *(){
       return *it;
     }
     bool operator ==(const iterator &i){
       return i.it==it;
     }

     bool operator !=(const iterator &i){
       return i.it!=it;
     }

     friend class Letras;
  };

  /**
   * @brief Inicializa un iterator al comienzo de las letras
   * */
  iterator begin(){
    iterator i;
    i.it=datos.begin();
    return i;
  }

  /**
   * @brief Inicializa un iterator al final de las letras
   * */
  iterator end(){
    iterator i;
    i.it=datos.end();
    return i;
  }

  /**
    @brief Escritura de la letras
    @param os: flujo de salida. Es MODIFICADO
    @param g: letras que se escriben
    @return el flujo de salida
   */

  friend ostream & operator<<(ostream & os, Letras & g){
      map<char,info>::iterator it;
      for (it=g.datos.begin(); it!=g.datos.end();++it){
        os<<"letra: "<<it->first<<" cantidad: "<<it->second.apariciones<<" puntos: "<<it->second.puntuacion<<endl;
      }
      return os;
  }

  /**
    @brief Lectura de las Letras
    @param is: flujo de entrada. ES MODIFICADO
    @param g: Letras. ES MODIFICADO
    @return el flujo de entrada
  */

  friend istream & operator>>(istream & is, Letras & g){
      char p;
      Letras aux;

      while (is>>p){
        aux.insert(p);
      }
      g=aux;
      return is;
  }
};
#endif
