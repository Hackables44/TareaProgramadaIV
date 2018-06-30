/** ArbolRojiNegro.h */

#ifndef _ArbolRojiNegro
#define _ArbolRojiNegro

#include <iostream>
using namespace std;

#define IZQ 0
#define DER 1

class ArbolRN{

	friend ostream& operator<<(ostream& salida, ArbolRN& arbol){
		if(arbol.raiz){
			arbol.raiz->imprimir(salida);
		}
		return salida;
	}

	private:
		class Nodo;
		class Pila{
			friend class Iterador;

			public:
				Nodo** buffer;
				int contadorDeNodosAgregados;
				int length;

				void _init(){
					for(int i = 0; i < length; ++i){
						buffer[i] = 0;
					}
					contadorDeNodosAgregados = 0;
				}

				Pila(int length){
					buffer = new Nodo* [length];
					this->length = length;
					_init();
				}

				Pila(){
					buffer = 0;
					contadorDeNodosAgregados = 0;
				}

				~Pila(){
					if(buffer){
						for(int i = 0; i < contadorDeNodosAgregados; ++i){
							delete buffer[i];
						}
						delete buffer;
						buffer = 0;
					}

				}

				void limpiarPila(){
					_init();
				}

				void agregarALaPila(Nodo* nodo){
					buffer[contadorDeNodosAgregados] = nodo;
					++contadorDeNodosAgregados;
				}

				int getContadorDeNodos(){
					return contadorDeNodosAgregados;
				}

				Nodo * getPtrNodo(int indice){
					Nodo * ptr = 0;
					if( posValida(indice) ){
						ptr = buffer[indice];
					}
					return ptr;
				}

				int posValida(int indice){
					int validez = 0;
					if(indice>=0 && indice<length){
						validez = 1;
					}
					return validez;
				}

		};

		class Nodo{
			public:
				char color; /** almacena el color Rojo o Negro del Nodo (raíz, nodo intermedio u hoja) */
				int key; /** llave del nodo */
				int /** T */ dato; /** almacena el valor según el tipo de dato (T) */
				Nodo* hijo[2]; /** cada nodo tiene máximo 2 hijos */
				Pila pila;

				Nodo(){ /** constructor por omisión */
					/** inicializa los valores en */
					dato = 0;
					key = 0;
					color = '\0';
					hijo[IZQ] = 0;
					hijo[DER] = 0;
				}

				Nodo(int dato){
					this->dato = dato;
					key = dato; //tentativo
					color = 'N';
					hijo[IZQ] = 0;
					hijo[DER] = 0;
				}

				Nodo(int key, int NoSeUsa){ /** constructor con parámetros de la clase nodo */  //PUEDE SER QUE NO USEMOS EL PARAMETRO DATO EN ESTE CONSTRUCTOR
					/** inicializa los valores con los atributos recibidos*/
					this->key=key;
					dato = 0;
					color = 'R';
					hijo[IZQ] = 0;
					hijo[DER] = 0;
				}

				Nodo* crearLlave(Nodo* nodo1, Nodo* nodo2){
					// en parte tienes razon hay que tomar en cuenta el caso en que pase eso para no meterse aqui y solo agregar una hoja, pero serie en insertar aislando bien las condiciones

					Nodo* menor = nodo1;
					Nodo* mayor = nodo2;

					if(menor->getKey() > nodo2->getKey()){
						menor = nodo2;
						mayor = nodo1;
					}
					Nodo* llave = new Nodo(menor->getKey(), 0);
					llave->hijo[IZQ] = menor;
					llave->hijo[DER] = mayor;
					return llave;
				}


				~Nodo(){
					for(int i=IZQ; i<=DER ; ++i){
						if(hijo[i]){
							delete hijo[i];
						}
					}
				}

				void setColor(char color){
					this->color = color;
				}

				void setDato(int dato){
					this->dato = dato;
				}

				void setKey(int key){
					this->key = key;
				}

				char getColor(){
					return color;
				}

				int /** T */ getDato(){
					return dato;
				}

				int getKey(){
					return key;
				}

				void setPila(Pila& pila){
					this->pila = pila;
				}

				void insertar(int dato, Nodo* nodo1, Nodo* nodo2){  //falta agregar el recursivo para que se siga extendiendo en todo el arbol
			  if(this->dato!=dato){
					int lado = IZQ;
					if(dato > nodo1->dato){
						lado = DER;
					}
					if(nodo1->hijo[lado]){
						pila.agregarALaPila(nodo1->hijo[lado]);
						/*nodo2 =*/ nodo1->hijo[lado]->insertar(dato,nodo1->hijo[lado], nodo2);
					}
					else{
						hijo[lado] = new Nodo(dato);
					}
					Nodo* llave = crearLlave(nodo1,nodo2); // esto crearia la llave y de una vez le asignaria los nodos como hijos
					}
				}

				int existe(int dato){
					int esta = 0;
					if(this->dato!=dato){
	   				int lado = IZQ;
						if(dato > this->dato){
		   				lado = DER;
	   				}
	   				if(hijo[lado]){
		   				esta = hijo[lado]->existe(dato);
	   				}
					}
					else {
						esta = 1;
					}
					return esta;
				}

				ostream& imprimir(ostream& salida){
					if(hijo[0]){
						hijo[0]->imprimir(salida);
					}
    			salida << dato << " ";
					if(hijo[1]){
						hijo[1]->imprimir(salida);
					}
					return salida;
				}
		};


		Nodo* raiz; // atributo del ArbolRN
		Pila pila;  //atributo de la clase ArbolRN

	public:

		//friend class Pila;



		class Iterador{ /** con cuatro punteros */
			public:
			Pila pila;
			Nodo * bisAbuelo;
			Nodo * abuelo;
			Nodo * padre;
			Nodo * actual; /** se toma como nodo hijo, y en base a este, se asignan los nodos padre, abuelo y bisAbuelo */

			void _initPtr(){
				bisAbuelo = 0;
				abuelo = 0;
				padre = 0;
				actual = 0;
			}

			Iterador(){
				_initPtr();
			}

			~Iterador(){
				_initPtr();
			}

			void operator++(){ /** Cada vez que baje, que mueva cada puntero hacia arriba */
				bisAbuelo = abuelo;
				abuelo = padre;
				padre = actual; // actual es el hijo
				actual = pila.getPtrNodo(pila.getContadorDeNodos() - 1) ; // baje en el árbolo por tanto el hijo cambio
			}

			void operator--(){
				actual = padre; // actual se devuelve una poscision que corresponde al padre
				padre = abuelo; // padre se devuelve una poscision que corresponde al abuelo
				abuelo = bisAbuelo; // abuelo se devuelve una poscision que corresponde al bisAbuelo
				bisAbuelo = pila.getPtrNodo(pila.getContadorDeNodos() - 5); //el bisAbuelo se devuelve una posicion que seria el total de Nodos agregados -5 porque la actual era -4
			}

			Nodo* operator*(){
				return actual;
			}

			void setPila(Pila& pila){
				//implementarlo de mejor manera para que no haga una copia a nivel de miembro(al rato si este bien ya que planeamos usar la misma pila)
				this->pila = pila;
			}

		};
		Iterador iterador; // atributo de la clase ArbolRN

		ArbolRN(){
			raiz = 0;
		}

		~ArbolRN(){  //hacer destructor de nodo que se llame a sus hijos
			if (raiz) {
				delete raiz;
			}
		}

		void cambioColorRaiz(){ /** cambia el color de la raíz de Rojo a Negro */
			if( 'R' == raiz->color ){ /** si la raiz es de color Rojo */
				raiz->color = 'N'; /** cambiar la raíz a color Negro */
			}
		}

		void colorFlip(Nodo * padre){ /** recibe el puntero del nodo padre */
			int ambos = 0; /** */
			/** si el hijo izquierdo y el hijo derecho son rojos lo almacena en la variable local */
			if( ('R' == iterador.padre->hijo[IZQ]->getColor()) && ('R' == iterador.padre->hijo[DER]->getColor()) ){
				ambos = 1;
			}

			if(ambos){ /** si ambos son rojos */
				/** pinta de Negro los nodos */
				iterador.padre->hijo[IZQ]->setColor('N');
				iterador.padre->hijo[DER]->setColor('N');
				iterador.padre->setColor('R'); /** y el padre se vuelve rojo */
			}
		}

		void rotacionSimpleIzquierda(){ /** se puede pasar a las siglas RSI */
		/** rotación de punteros */ /** si debe asignar el hijo derecho del bisAbuelo */
			iterador.abuelo->hijo[DER] = iterador.padre->hijo[IZQ]; /** le damos el hijo izquierdo al abuelo */
			iterador.padre->hijo[IZQ] = iterador.abuelo; /** el abuelo se vuelve hijo izquierdo del padre */
			iterador.bisAbuelo->hijo[DER] = iterador.padre; /** el bisAbuelo toma al nodo de mayor jerarquía */

		/** rotación de punteros */ /** si debe asignar el hijo derecho del bisAbuelo */
			iterador.abuelo->hijo[DER] = iterador.padre->hijo[IZQ]; /** le damos el hijo izquierdo al abuelo */
			iterador.padre->hijo[IZQ] = iterador.abuelo; /** el abuelo se vuelve hijo izquierdo del padre */
			iterador.bisAbuelo->hijo[IZQ] = iterador.padre; /** el bisAbuelo toma al nodo de mayor jerarquía */

		}

		void rotacionSimpleDerecha(){ /** se puede pasar a las siglas RSD */
		/** rotación de punteros */ /** si debe asignar el hijo derecho del bisAbuelo */
			iterador.abuelo->hijo[IZQ] = iterador.padre->hijo[DER]; /** le damos el hijo izquierdo al abuelo */
			iterador.padre->hijo[DER] = iterador.abuelo; /** el abuelo se vuelve hijo izquierdo del padre */
			iterador.bisAbuelo->hijo[DER] = iterador.padre; /** el bisAbuelo toma al nodo de mayor jerarquía */

		/** rotación de punteros */ /** si debe asignar el hijo derecho del bisAbuelo */
			iterador.abuelo->hijo[IZQ] = iterador.padre->hijo[DER]; /** le damos el hijo izquierdo al abuelo */
			iterador.padre->hijo[DER] = iterador.abuelo; /** el abuelo se vuelve hijo izquierdo del padre */
			iterador.bisAbuelo->hijo[IZQ] = iterador.padre; /** el bisAbuelo toma al nodo de mayor jerarquía */
		}

		void rotacionDobleIzquierda(){
			/** rotación de punteros */ /** si debe asignar el hijo derecho del bisAbuelo */
			iterador.padre->hijo[IZQ] = iterador.padre->hijo[IZQ]->hijo[DER]; /** la llave izquierda le da su hijo derecho al padre */
			iterador.actual->hijo[DER] = iterador.padre; /** El iterador tendrá referencia del bisAbueloPtr, abueloPtr, padrePtr, hijoLlavePtr */
			// -> actualizar los punteros del iterador
			// revisar si se puede quitar ArbolRN::
			iterador.bisAbuelo = iterador.abuelo;
			/** el abuelo es el mismo */
			iterador.padre = iterador.actual; /** el hijo pasa a ser padre */
			iterador.actual = iterador.abuelo->hijo[DER]; /** el primer padre pasa a ser hijo */
			rotacionSimpleIzquierda();
		}

		void rotacionDobleDerecha(){
			/** rotación de punteros */ /** si debe asignar el hijo izquierdo del bisAbuelo */
			iterador.padre->hijo[DER] = iterador.padre->hijo[DER]->hijo[IZQ]; /** la llave derecha le da su hijo izquierdo al padre */
			/** El iterador tendrá referencia del bisAbueloPtr, abueloPtr, padrePtr, hijoLlavePtr */
			iterador.actual->hijo[IZQ] = iterador.padre; /** el hijo se hace padre de su padre */
			// -> actualizar los punteros del iterador
			// revisar si se puede quitar ArbolRN::
			iterador.bisAbuelo = iterador.abuelo;
			/** el abuelo es el mismo */
			iterador.padre = iterador.actual; /** el hijo pasa a ser padre */
			iterador.actual = iterador.abuelo->hijo[IZQ]; /** el primer padre pasa a ser hijo */
			rotacionSimpleDerecha();
		}

		void insertar(int dato){
			Nodo* nodo2 = new Nodo(dato); //esto es lo que acabo de agregar
		 if(raiz){
			 raiz->insertar(dato, raiz, nodo2); //creo que ocupamos psarle tambien la referencio de raiz a este metodo y el nodo2 tambien se lo estamos pasando por parametro
		 }
		 else {
			 raiz = nodo2;
			 //pila.agregarALaPila(raiz);  aqui creo que no se agrega porque apenas es la primera hoja agregada no se baja
		 }
		 pila.limpiarPila();
	 }

	int existe(int dato){
		 int esta = 0;
		 if(raiz){
			 esta = raiz->existe(dato);
		 }
		 return esta;
	 }

	 /*ostream& imprimir(ostream& salida){
		 if(raiz){
		 	salida << raiz;
	 	}
		return salida;
	*/


};
#endif

//RECORDATORIO


//un metodo que limpia la pila
//el metodo agregar necesita ir llenando la pila conforme va bajando y verificar si hay que hacer color flip o las rotaciones
//ahorita estamos realizando pruebas con int en general pasar a tipo T despues
//solo falta agregar constructor de nodo llave a insertar y ir llenando la pila
//claro y probar los metodos colorFlip y rotaciones...
