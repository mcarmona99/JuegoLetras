/*
Estructuras de Datos
ETSIIT, UGR
Jose Saldaña Mercado 76424266G && Manuel Carmona Perez 17482989E
Grupo D-2

Práctica final: TDA Diccionario
Modulo Bolsa de Letras
Un objeto del T.D.A. Diccionario almacena palabras de un lenguaje. El T.D.A Diccionario será
representado como un set instanciado a string .
*/

/**
  * @file Diccionario.h
  * @brief Fichero cabecera del TDA diccionario
  *
  */

#ifndef __Diccionario_h__
#define __Diccionario_h__


#include <set>
#include <vector>
//#include <string>
using namespace std;

class Diccionario{
  private:
    set<string> datos;
  public:
    /**
      @brief Construye un diccionario vacío.
    **/
    Diccionario(){}

    /**
      @brief Devuelve el numero de palabras en el diccionario
    **/
    int size() const {
      return datos.size();
    }
    
    /**
      @brief Obtiene todas las palabras en el diccionario de un longitud dada
      @param longitud: la longitud de las palabras de salida
      @return un vector con las palabras de
      longitud especifica en el parametro de entrada
    **/
    vector<string> PalabrasLongitud(int longitud){
      vector<string> palabras;
      typename set<string>::iterator it;
      for (it=datos.begin();it!=datos.end();++it){
        if ((*it).size()==longitud)
          palabras.push_back(*it);
      }
      return palabras;
    }
    /**
      @brief Indica si una palabra está en el diccionario o no
      @param palabra: la palabra que se quiere buscar
      @return true si la palabra esta en el diccionario. False en caso contrario
    **/
    bool Esta(string palabra){
      if (datos.empty())
        return false;

      bool encontrada=false;
      typename set<string>::iterator it;
      it=datos.find(palabra);
      if (it!=datos.end())
        encontrada=true;
      else
        encontrada=false;

      return encontrada;
    }
    /**
      @brief Lee de un flujo de entrada un diccionario
      @param is:flujo de entrada
      @param D: el objeto donde se realiza la lectura.
      @return el flujo de entrada
    **/
    friend istream & operator>>(istream & is,Diccionario &D){
      string palabra;
      while (!(is.eof())){
        getline(is,palabra);
        D.datos.insert(palabra);
      }
    }
    /**
      @brief Escribe en un flujo de salida un diccionario
      @param os:flujo de salida
      @param D: el objeto diccionario que se escribe
      @return el flujo de salida
    **/
    friend ostream & operator<<(ostream & os, Diccionario &D){
      typename Diccionario::iterator it;
      os << "\nDICCIONARIO: " << endl;
      for (it=D.begin();it!=D.end();++it){
        os<< (*it)<< endl;

      }
    }

    /**
     * @brief clase para iterar sobre el diccionario
     * */

    class iterator{
      private:
        set<string>::iterator it;
      public:
        iterator (){}
        string operator *(){
          return *(it);
        }
        iterator & operator ++(){
          ++it;
          return *this;
        }
        bool operator ==(const iterator &i){
          return i.it==it;
        }
        bool operator !=(const iterator &i){
          return i.it!=it;
        }
        friend class Diccionario;
    };

    /**
     * @brief Inicializa un iterator al comienzo del diccionario
     * */
    iterator begin(){
      iterator i;
      i.it=datos.begin();
      return i;
    }
    /**
     * @brief Inicializa un iterator al final del diccionario
     * */
    iterator end(){
      iterator i;
      i.it=datos.end();
      return i;
    }
};

#endif
