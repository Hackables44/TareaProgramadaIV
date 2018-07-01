/** ArbolRojiNegro.h */

#ifndef _ArbolRojiNegro
#define _ArbolRojiNegro

#include <iostream>
using namespace std;

/** constantes definidas para indicar cual es el hijo izquierdo y el derecho */
#define IZQ 0
#define DER 1

class ArbolRN{ /** definición de la clase para hacer el árbol de
	/** método friend que imprime los valores en los nodos del árbol de forma recursiva, recibe y devuelve la referencia
	 de un objeto de salida de flujo, junto con la referencia del objeto Arbol	*/
	friend ostream& operator<<(ostream& salida, ArbolRN& arbol){ /** recibe como parámetro la referencia de un objeto stream y Arbol */
		if(arbol.raiz){ /** si la raiz tiene un puntero válido a un nodo */
			/** le indica a la raiz que imprima su valor, de forma recursiva invocará el imprimir del resto de nodos que existan */
			arbol.raiz->imprimir(salida);
		}
		return salida; /** devuelve el objeto ostream */
	}

	private: /** delimitador de alcance privado */
		class Nodo; /**prototipo de la clase nodo para que el compilador sepa que existirá */
		class Pila{ /** definición de la clase Pila */

			friend class Iterador; /** declaramos la clase Iterador como friend para que pueda acceder al vector de punteros a Nodos,
			 este vector guarda el camino que está siguiendo el iterador cuando baja por el árbol desde la raíz hasta las hojas*/

			public: /** delimitador de acceso público */
				Nodo** buffer; /** puntero que almacenará la referencia a un vector de punteros a nodo para guardar el camino
				por el cual se baja, desde la raíz, por los nodos intermedios hasta las hojas */
				int contadorDeNodosAgregados; /** contador de Nodos que lleva el control de la cantidad de Nodos agregados durante el camino */
				int length; /** tamaño base del vector para no pedir muchos campos de más y hacerlo un poco más óptimo */

				/** método que se encarga de inicializar el vector al que apunta buffer en punteros nulos y por lo tanto se establece
				en 0 la cantidad de nodos que se han agregado, será llamado por los constructores de su clase Pila y por el método limpiarPila */
				void _init(){ /** no recibe parámetros */
					if(buffer){ /** si el puntero al vector que sirve como buffer es válido */
						for(int i = 0; i < length; ++i){ /** recorre la totalidad del vector, desde la primera hasta su última celda */
							buffer[i] = 0; /** establece el puntero en nulo */
						}
					}
					contadorDeNodosAgregados = 0; /** indica que no se han agregado nodos */
				}

				/* Constructor con parámetro de la clase Pila, el cual recibe el length del vector (su cantidad de celdas) */
				Pila(int length){ /** recibe la cantidad de celdas por las que debe estar compuesto el vector */
					buffer = new Nodo* [length]; /** al puntero buffer le asigno el puntero de la primera celda del vector de punteros a objetos de Nodo */
					this->length = length; /** almaceno el legth como atributo */
					_init(); /** invoca al método para inicializar el vector en punteros nulos y el contador de nodos agregados en 0 */
				}

				/** Constructor por omisión que establece de forma predeterminada un buffer de 100 celdas */
				Pila(){ /** Constructor sin parámetros */
					length = 100; /** se asigna un length de 100 por defecto */
					buffer = new Nodo * [length]; /** el buffer almacena el puntero al vector de punteros a Nodo */
					contadorDeNodosAgregados = 0; /** el contador de nodos agregados es 0 */
				}

				/** el destructor de la clase Pila, limpia el vector de punteros y elimina ese vector, luego le asigna a buffer un puntero nulo */
				~Pila(){ /** el destructor de la clase Pila */
					if(buffer){ /** si el puntero hace referencia a un vector que funciona como buffer */
						for(int i = 0; i < contadorDeNodosAgregados; ++i){ /** recorre el vector hasta la última celda que hace refe */
							buffer[i] = 0; /** establece el puntero en nulo, quien se encarga de eliminar los nodos es la clase ArbolRN */
						}
						delete buffer; /** elimina el vector de punteros */
						buffer = 0; /** asigna un puntero nulo */
					}
				}

				/** el método limpiarPila invoca al método que inicializa en null los punteros del vector y reinicia el contador de elementos agregados, no recibe parámetros */
				void limpiarPila(){/** no recibe parámetros */
					_init(); /** invoca al método que inicializa el vector de punteros  */
				}

				/** el método setLength indica la dimensión  */
				// void setLength(int length){
					// this->length = length;
				// }

				/** función que devuelve el atributo que indica la cantidad de celdas del vector que funciona como buffer */
				int getLength(){ /** no recibe parámetros */
					return length; /**  devuelve el atributo length */
				}

				/** el método agregarALaPila recibe el puntero de un Nodo como parámetro y lo agrega al vector de punteros utilizado como buffer */
				void agregarALaPila(Nodo* nodo){ /** recibe como parámetro un puntero a Nodo */
					buffer[contadorDeNodosAgregados++] = nodo; /** agrega el puntero recibido de acuerdo con el contador de nodos */
				}

				/** fnción que devuelve el atributo utilizado como contador de Nodos agregados al buffer */
				int getContadorDeNodos(){ /** no recibe parámetro alguno */
					return contadorDeNodosAgregados; /** devuelve el valor del atributo "contadorDeNodosAgregados" */
				}

				/** devuelve el puntero a instancia de Nodo almacenado en la celda cuyo indice es ingresado como parámetro */
				Nodo * getPtrNodo(int indice){ /** recibe el indice de la celda del vector */
					Nodo * ptr = 0; /** inicializa el puntero en nulo */
					/** por medio de la función que verifica que el índice ingresado es una posición válida dentro del vector */
					if( posValida(indice) ){ /** si la posición es válida */
						ptr = buffer[indice]; /** devuelva el puntero en dicha celda */
					}
					return ptr; /** devuelve el puntero almacenado en la variable local */
				}

				/** función que devuelve 0 (false) si el indice no está dentro del vector o 1 (true) si es cierto que el indice ingresado corresponde a alguna celda del vector de punteros*/
				int posValida(int indice){ /** recibe un entero que funciona como índice */
					int validez = 0; /** inicializamos la variable local que indica la validez del puntero */
					if(indice>=0 && indice<length){ /** si el indice está entre la primera y última celda (incluyéndolas) es válido */
						validez = 1; /** indica que la vaidez es verdadera */
					}
					else{ /** si el indice no está dentro del rango del vector, lo indica al usuario */
						cerr << "WARNING: El indice ingresado no es valido\nRango del vector 0 - " << length << endl;
						cerr << "El indice ingresado es " << indice << endl;
						cout << "se devuelve un puntero nulo por omision" << endl;
					}
					return validez; /** devuelve el valor almacenado en validez */
				}

		};

		class Nodo{ /** definición de la clase Nodo */
			public: /** todos sus atributos y métodos son públicos */
				char color; /** almacena el color Rojo o Negro del Nodo (raíz, nodo intermedio u hoja) */
				int key; /** llave del nodo, número menor entre 2 nodos */
				int /** T */ dato; /** almacena el valor según el tipo de dato (T) */
				Nodo* hijo[2]; /** cada nodo tiene máximo 2 hijos */

				Pila pila; /** Se crea una instancia de Pila en el stack, el cual utilizará la instancia de la clase Iterador */

				/** Constructor por omisión que inicializa los atributos numéricos en 0, el caracter en nulo y punteros en nulo también */
				Nodo(){ /** constructor sin parámetros */
					/** inicializa los atributos de la clase dato, key, color y los punteros a los hijos izquierdo y derecho en cero o nulo según corresponda. */
					dato = 0; /** inicializa dato en 0 */
					key = 0; /** inicializa la llave en 0 */
					color = '\0'; /** inicializa el caracter del color en nulo */
					hijo[IZQ] = 0; /** inicializa el puntero al hijo izquierdo en nulo */
					hijo[DER] = 0; /** inicializa el puntero al hijo derecho en nulo */
				}

				/** Constructor con párametro que se utiliza para crear una hoja */
				Nodo(int dato){ /** recibe un dato como parámetro */
					this->dato = dato; /** asigna como atributo el dato que está entrando */
					key = dato; // tentativo
					color = 'N'; /** las hojas siempre son de color negro */
					 /** las hojas no tienen hijos asi que a los punteros en el vector de hijos se les asigna punteros nulos */
					hijo[IZQ] = 0; /** inicializacion del puntero al hijo izquierdo en nulo*/
					hijo[DER] = 0; /** inicializacion del puntero al hijo derecho en nulo*/
				}

				/** Constructor con parámetros que se utiliza para la creación de los nodos intermedios del árbol que solo poseen una llave */
				Nodo(int key, int NoSeUsa){ /** constructor con parámetros de la clase nodo */  //PUEDE SER QUE NO USEMOS EL PARAMETRO DATO EN ESTE CONSTRUCTOR
					/** inicializa los valores de los atributos con los atributos recibidos */
					this->key=key;/**asignamos la llave que le esta entrando como parametro*/
					dato = 0; /**como es una llave le asignaremos el parametro en nulo*/
					color = 'R'; /**las llaves siempre son de color rojo cuando recien se estan creando*/
					hijo[IZQ] = 0; /**le asignamos esto en nulo pero por medio del metodo crearLlave le asignaremos los hijos que corresponden*/
					hijo[DER] = 0; /**le asignamos esto en nulo pero por medio del metodo crearLlave le asignaremos los hijos que corresponden*/
				}

				Nodo* crearLlave(Nodo* nodo1, Nodo* nodo2){
					// en parte tienes razon hay que tomar en cuenta el caso en que pase eso para no meterse aqui y solo agregar una hoja, pero serie en insertar aislando bien las condiciones

					Nodo* menor = nodo1;/**asumimos que el nodo1 sera el menor*/
					Nodo* mayor = nodo2;/**asumimos que el nodo2 sera el mayor*/

					if(menor->getKey() > nodo2->getKey()){/**por medio de esta condicion nos damos cuenta si nuestra suposicion de mayor estaba en lo correcto*/
						menor = nodo2;/**asignamos como deberia serlo*/
						mayor = nodo1;/**asignamos como deberia serlo*/
					}
					Nodo* llave = new Nodo(menor->getKey(), 0);//llamamos al constructor de nodo con el int que no se usa que realia la construccion de llaves
					llave->hijo[IZQ] = menor; //le decimos al nuevo nodo que que hijo izquierdo es el menor
					llave->hijo[DER] = mayor; //le decimos al nuevo nodo que su hijo derecho es el mayor
					return llave; //retornamos este nodo
				}


				~Nodo(){
					for(int i=IZQ; i<=DER ; ++i){ /**este for recorre de el lado izquierdo al lado derecho*/
						if(hijo[i]){ /**comprueba si el lado respectivo existe */
							delete hijo[i]; /**mata al hijo respectivo*/
						}
					}
				}

				/**metodo que asigna al nodo un color desde afuera, practico para futuro color flip*/
				void setColor(char color){
					this->color = color; /**realizacion de la asignacion*/
				}
				/**metodo que realiza una asignacion de dato desde afuera*/
				void setDato(int dato){
					this->dato = dato;/**realizacion de la asignacion*/
				}
				/**metodo que asigna una llave desde afuera*/
				void setKey(int key){
					this->key = key;/**realizacion de la asignacion*/
				}
				/**metodo que nos retorna el color del nodo respectivo*/
				char getColor(){
					return color; /**realizacion del retorno */
				}
				/**nos devuelve el dato que esta guardado en nodo*/
				int /** T */ getDato(){
					return dato;/**realizacion del retorno*/
				}
				/**metodo que nos devuelve el valor de la llave*/
				int getKey(){
					return key;/**retorno del valor de la llave*/
				}
				/**metodo que le asigna a la clase nodo la pila con la que esta trabajando el arbol actualmente*/
				void setPila(Pila& pila){
					this->pila = pila; /**asignacion, por referencia para que se trabaje con la misma pila*/
				}
				/**metodo que inserta de forma recursiva en la posicion indicada */
				void insertar(int dato, Nodo* nodo1, Nodo* nodo2){
			  if(this->dato!=dato){ /**condicion que solo agrega si no existe el dato que se va a agregar previamente*/
					int lado = IZQ; /**asumimos que se va a agregar del lado izquierdo*/
					if(dato > nodo1->dato){/**si el dato que se esta agregando es mayor que el actual esta condicion nos lleva al lado derecho*/
						lado = DER; /**asignacion del lado respectivo*/
					}
					if(nodo1->hijo[lado]){ /**comprobamos si el nodo existe de ese lado*/
						pila.agregarALaPila(nodo1->hijo[lado]); /**se realiza el agregado a la pila */
						nodo1->hijo[lado]->insertar(dato,nodo1->hijo[lado], nodo2); /**metodo recursivo que vuelve a llamar al metodo insertar con diferente valor*/
					}
					else{
						hijo[lado] = new Nodo(dato); /**si no existe el hijo lo creamos*/
					}
					Nodo* llave = crearLlave(nodo1,nodo2); /**esto crearia la llave y de una vez le asignaria los nodos como hijos*/
					}
				}
				/**metodo que nos dice si un elemento existe o no dentro del arbol*/
				int existe(int dato){
					int esta = 0; /**inicializacion de la variable que se va a devolver*/
					if(this->dato!=dato){ /**condicion que comprueba si ese elemento existe*/
	   				int lado = IZQ; /**asumimos que vamos a ir hacia el lado izquierdo*/
						if(dato > this->dato){ /**si el dato es mayor al de este nodo vamos al lado derecho*/
		   				lado = DER; /**asignacion del lado derecho*/
	   				}
	   				if(hijo[lado]){ /**comprobamos si existe ese lado*/
		   				esta = hijo[lado]->existe(dato); /**si existe el nodo llamamos denuevo al metodo de forma recursiva */
	   				}
					}
					else {/**nos demuestra que el dato si existia*/
						esta = 1; /**asignacion true de la variable que se retornara*/
					}
					return esta; /**retorno de la variable*/
				}
				/**metodo que imprime cada nodo y imprime a sus hijos respectivos*/
				ostream& imprimir(ostream& salida){
					if(hijo[0]){ /**preguntamos si el hijo izquierdo existe */
						hijo[0]->imprimir(salida); /**llama de forma recursiva el metodo imprimir de el hijo izquierdo*/
					}
    			salida << dato << " "; /**manda a salida el dato y deja un espacio*/
					if(hijo[1]){ /**pregunta si el hijo derecho existe*/
						hijo[1]->imprimir(salida); /**llama de forma recursiva el metodo imprimir del hijo derecho*/
					}
					return salida; /**retorna el ostream*/
				}
		};

		Nodo* raiz; // atributo del ArbolRN
		Pila pila;  //atributo de la clase ArbolRN

	public:

		class Iterador{ /** con cuatro punteros */
			public:
			Pila pila; //**instancia de pila dentro de la clase iterador*/
			Nodo* bisAbuelo; /**puntero a nodo con el que vamos a saber quien es el bisAbuelo  mientras bajamos*/
			Nodo* abuelo;  /**puntero a nodo con el que vamos a saber quien es el Abuelo  mientras bajamos*/
			Nodo* padre;  /**puntero a nodo con el que vamos a saber quien es el padre  mientras bajamos*/
			Nodo* actual; /** se toma como nodo hijo, y en base a este, se asignan los nodos padre, abuelo y bisAbuelo */

			/**inicializacion de todo en nulo*/
			void _initPtr(){
				bisAbuelo = 0;
				abuelo = 0;
				padre = 0;
				actual = 0;
			}

			/**constructor por omisión de la clase iterador*/
			Iterador(){
				_initPtr();
			}

			/**destructor de iterador el cual no tiene que matar nada porque los nodos los mata el arbol pero es efectivo hacer que cuando se muera sus punteros queden en nulo */
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

			/**metodo sobrecaragado del asterisco que retorno al puntero que esta apuntando al actual*/
			Nodo* operator*(){
				return actual; /**retorno del puntero que apunta al actual*/
			}
			/**metodo que le asigna al iterador la misma pila con al que trabaja el arbol*/
			void setPila(Pila& pila){
				this->pila = pila; /**asignacion de la pila */
			}

		};
		Iterador iterador; /**instancio de iterador que actua como atributo de la clase arbol*/
		/**metodo constructor por omision de la clase ArbolRN*/
		ArbolRN(){
			raiz = 0; /**inicializacion de la raiz en nulo*/
		}
		/**metodo destructor de arbol que mata a la raiz y esta se encarga de matar a sus hijos*/
		~ArbolRN(){
			if (raiz) { /**entra solo si existe la raiz*/
				delete raiz; /**cada nodo mata recursivamente a sus hijos*/
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
			rotacionSimpleIzquierda(); /**llamado al metodo rotacion simple izquierda*/
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
	 /**metodo existe de arbol que llama recursivamente al de nodo*/
	int existe(int dato){
		 int esta = 0; /**se asume que no esta*/
		 if(raiz){/**si existe la raiz entra*/
			 esta = raiz->existe(dato); /**llamado a el metodo existe de nodo */
		 }
		 return esta; /**retorna el resultado de si esta o no esta*/
	 }

	//metodo que no se utiliza en este momento pero puede ser que a futuro nos llegue a servir
	/*void setLengthPila(int length){
		this->pila.setLength(length);
	}*/

};
#endif

//RECORDATORIO

// Pasar el nombre del archivo .h a ArbolRN
// Cuidado con setLength()
// ver si Pila tiene un nombre apropiado, por su forma del manejo de datos, podría cambiarse a Buffer

// se crea como atributo una instancia de la clase Pila en Nodo paa facilitar el manejo de la misma, preguntar a Casasola
// si eso es correcto o si debe incluirse solamente donde se interactue con la pila, Nodo no tiene que ver con la Pila, sino alguna clase como iterador

// Ajustar el constructor de Nodo para el árbol roji-negro real, agregar key ¿cierto?
// El constructor de la llave es la que debe tener un constructor con un sólo parámetro

//el metodo agregar necesita ir llenando la pila conforme va bajando y verificar si hay que hacer color flip o las rotaciones
//ahorita estamos realizando pruebas con int en general pasar a tipo T despues
//probar los metodos colorFlip y rotaciones...
//ocupamos implementar el ++ de iterador dentro de nodo ya que ahi se realiza el insertar en la pila, asi que ocupamos pasarle una referencia de iterador
