#include "ArbolRN.h"
#include<iostream>
#include <string>
using namespace std;


template< class T >
void seleccionDeTipo(T tipo){
   ArbolRN<int,T> arbol;
   int key;
   do{

      /** ingresa los nodos del 7 al 4, para probar la rotación izquierda */
        cout << "key: ";
        cin >> key ;
        cout << endl;
        cout << "dato: ";
        cin >> tipo;
        cout << endl;
        cout << "Ingresa el dato-> Key: " << key << " Dato: " << tipo << endl;
        if(key!=-1){
            arbol.insertar(key, tipo);
        }



  }while(key != -1);

  cout << "Imprime el arbol: \n" << arbol << endl;
}

int main(){
  int entero;
  double real;
  char letra;
  string hilera;
  cout << "ingrese de que tipo quiere que sea el arbol" << endl;
  cout << "C = char, S = string , I = int , D = double" << endl;
  char respuesta;
  cin >> respuesta;
  cout << "ingrese la llave, tiene que ser Int" << endl;
  cout << "Ingrese el dato que desea agregar al arbol, que sea del tipo respectivo" << endl;
  switch(respuesta){
    case 'C':
      seleccionDeTipo(letra);
       break;
    case 'S':
      seleccionDeTipo(hilera);
      break;
    case 'I':
      seleccionDeTipo(entero);
      break;
    case 'D':
      seleccionDeTipo(real);
      break;
    default:
      cerr << "WARNING: se digito un char invalido " << endl;
      break;
  }



  return 0;
}
