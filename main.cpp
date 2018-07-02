#include "ArbolRojiNegro.h"
#include<iostream>
using namespace std;

int main(){
   int dato = 0;
   int key = 0;

   ArbolRN arbol;
   do{
      cout << "Dato:";
      cin >> dato;
      cout << "Key:";
	    cin >> key;
	    cout << endl;
	    if(key!=-1){
   	     arbol.insertar(key, dato);
	     }
  }while(key != -1);

  cout << "Imprime el arbol: " << arbol << endl;
}
