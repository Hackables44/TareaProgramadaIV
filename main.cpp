#include "ArbolRojiNegro.h"
#include<iostream>
using namespace std;

int main(){
   int valor = 0;

   ArbolRN arbol;
   do{
      cout << "Valor:";
	    cin >> valor;
	    cout << endl;
	    if(valor!=-1){
   	     arbol.insertar(valor);
	     }
  }while(valor != -1);

  cout << arbol << endl;
}
