#include "ArbolRN.h"
#include<iostream>
using namespace std;

int main(){
   int dato = 0;
   int key = 0;

   ArbolRN arbol;

   do{
      // cout << "Dato:";
      // cin >> dato;
      // cout << "Key:";
	    // cin >> key;
	    // cout << endl;


      /** ingresa los nodos del 4 al 7, para probar la rotación izquierda */
    //  for(int i=0; i<3; ++i){
      //  key = i+4;
      //  dato = key;
      //  cout << "Ingresa el dato-> Key: " << key << " Dato: " << dato << endl;
      //  if(key!=-1){
     	  //   arbol.insertar(key, dato);
  	     //}
      //}

      /** ingresa los nodos del 7 al 4, para probar la rotación izquierda */
      
        cin >> key ;
        cin >> dato;
        cout << "Ingresa el dato-> Key: " << key << " Dato: " << dato << endl;
        if(key!=-1){
     	     arbol.insertar(key, dato);
  	     }
      

      

  }while(key != -1);

  cout << "Imprime el arbol: \n" << arbol << endl;

  return 0;
}
