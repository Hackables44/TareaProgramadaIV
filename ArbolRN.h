/** ArbolRojiNegro.h */

#ifndef _ArbolRojiNegro
#define _ArbolRojiNegro

#include <iostream>
using namespace std;

/** constantes definidas para indicar cual es el hijo izquierdo y el derecho */
#define IZQ 0
#define DER 1

class ArbolRN{ /** definición de la clase para hacer el árbol de */
	/** método friend que imprime los valores en los nodos del árbol de forma recursiva, recibe y devuelve la referencia de un objeto de salida de flujo, junto con la referencia del objeto Arbol	*/
	friend ostream& operator<<(ostream& salida, ArbolRN& arbol){ /** recibe como parámetro la referencia de un objeto stream y Arbol */
		if(arbol.raiz){ /** si la raiz tiene un puntero válido a un nodo */
			/** le indica a la raiz que imprima su valor, de forma recursiva invocará el imprimir del resto de nodos que existan */
			arbol.raiz->imprimir(salida);
		}
		return salida; /** devuelve el objeto ostream */
	}
	public: //se ocupaba hacer un public aqui porque como el iterador es publico su prototipo tambien
	class Iterador; //prototipo

	private: /** delimitador de alcance privado */
	class Nodo; /** prototipo de la clase nodo para que el compilador sepa que existirá */

	class Pila{ /** definición de la clase Pila */

		friend class Iterador; /** declaramos la clase Iterador como friend para que pueda acceder al vector de punteros a Nodos,
		este vector guarda el camino que está siguiendo el iterador cuando baja por el árbol desde la raíz hasta las hojas*/

		public: /** delimitador de acceso público */
		Nodo** buffer; /** puntero que almacenará la referencia a un vector de punteros a nodo para guardar el camino
		por el cual se baja, desde la raíz, por los nodos intermedios hasta las hojas */
		int contadorDeNodosAgregados; /** contador de Nodos que lleva el control de la cantidad de Nodos agregados durante el camino */
		int length; /** tamaño base del vector para no pedir muchos campos de más y hacerlo un poco más óptimo */
		//Iterador iterador;

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
			_init(); /** se inicializa el vector de punteros y el contador de nodos agregados */
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
			// cout << "Se limpio la pila de forma exitosa" << endl;
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
			cout << "contadorDeNodosAgregados:" << contadorDeNodosAgregados << endl;
		}

		/** función que devuelve el atributo utilizado como contador de Nodos agregados al buffer */
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

		/*void setIterador(Iterador& iterador){
		this->iterador = iterador;
	}*/

};

class Nodo{ /** definición de la clase Nodo */
	public: /** todos sus atributos y métodos son públicos */
	char color; /** almacena el color Rojo o Negro del Nodo (raíz, nodo intermedio u hoja) */
	int key; /** llave del nodo, número menor entre 2 nodos */
	int /** T */ dato; /** almacena el valor según el tipo de dato (T) */
	Nodo* hijo[2]; /** cada nodo tiene máximo 2 hijos */

	//Pila pila; /** Se crea una instancia de Pila en el stack, el cual utilizará la instancia de la clase Iterador */

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
	Nodo(int key, int dato){ /** recibe un dato como parámetro */
		this->dato = dato; /** asigna como atributo el dato que está entrando */
		this->key = key; /** asigna como atributo la llave que está entrando */
		color = 'N'; /** las hojas siempre son de color negro */
		/** las hojas no tienen hijos asi que a los punteros en el vector de hijos se les asigna punteros nulos */
		hijo[IZQ] = 0; /** inicializacion del puntero al hijo izquierdo en nulo */
		hijo[DER] = 0; /** inicializacion del puntero al hijo derecho en nulo */
	}

	/** Constructor con parámetros que se utiliza para la creación de los nodos intermedios del árbol que solo poseen una llave */
	Nodo(int key){ /** Constructor con parámetros de la clase nodo */  //PUEDE SER QUE NO USEMOS EL PARAMETRO DATO EN ESTE CONSTRUCTOR
		/** inicializa el valor del atributo key con el parámetro key recibido */
		this->key = key;/** asignamos la llave que entra como parámetro */
		dato = 0; /** como es un nodo intermedio, solo almacena llave, entonces no asignamos dato */
		color = 'R'; /** las llaves cuando se crean son de color rojo */
		/** inicializa los punteros a hijo en nulo, los cuales serán asignados posteriormente mediante el método "crearLlave" según corresponda */
		hijo[IZQ] = 0; /** inicializa el puntero al hijo izquierdo en nulo */
		hijo[DER] = 0; /** inicializa el puntero al hijo derrecho en nulo */
	}

	/** Destructor de la clase Nodo que se encarga de si existen sus hijos */
	~Nodo(){
		for(int i=IZQ; i<=DER ; ++i){ /** recorre el hijo izquierdo y el hijo derecho */
			if(hijo[i]){ /** comprueba si el lado respectivo existe */
				delete hijo[i]; /** devuelve la memoria del hijo respectivo */
			}
		}
	}

	/** función para crear el nodo intermedio que según la llave ordenará las hojas con datos */
	Nodo* crearLlave(Nodo* nodo1, Nodo* nodo2){ /** recibe 2 nodos como parámetro */
		/** para inicializar los punteros, se toma "nodo1" como menor y "nodo2" como mayor */
		Nodo* menor = nodo1;/** guarda el puntero del primer nodo */
		Nodo* mayor = nodo2;/** guarda el puntero del segundo nodo */
		if(menor->getKey() > nodo2->getKey()){ /** si la llave del nodo indicado como menor en realidad es mayor que el del otro nodo */ /** por medio de esta condicion nos damos cuenta si nuestra suposicion de mayor estaba en lo correcto */
			/** reasigna de forma contraria el menor y el mayor, asigna los punteros de la forma correcta en este caso */
			menor = nodo2; /** nodo2 es el menor */
			mayor = nodo1; /** nodo1 es el mayor */
		}
		Nodo* llave = new Nodo(menor->getKey()); /** se llama al constructor del nodo que funciona como llave con el int que no se usa */
		llave->hijo[IZQ] = menor; /** asigna el menor al hijo izquierdo del nodo llave */
		llave->hijo[DER] = mayor; /** asigna el mayor al hijo derecho del nodo llave */
		return llave; /** devuelve el nodo llave */
	}

	/** método que asigna al nodo un color desde dentro o afuera, práctico para el método color-flip */
	void setColor(char color){ /** recibe el caracter que indica el color rojo o negro */
		if( (color=='R' || color=='N') || (color=='r' || color=='n') ){ /** si el caracter ingresado hace referencia a el color rojo o negro */
			this->color = color; /** realiza la asignación */
		}
		else{ /** indica al usuario que el caracter ingresado no hace referencia al color rojo, ni negro */
			cerr << "WARNING: El caracter ingresado \""<<color<<"\" no hace referencia al color rojo (R) o negro (N)" << endl;
			cerr << "No se ha establecido el color \""<<color<<"\""<< endl;
		}
	}

	/** método que realiza una asignacion del dato de la instancia de Nodo */
	void setDato(int dato){ /** recibe un dato de tipo T como parámetro */
		this->dato = dato; /** asignación del dato */
	}

	/** método que realiza una asignacion de la llave de la instancia de Nodo */
	void setKey(int key){
		this->key = key; /** asignación de la llave */
	}

	/** función que retorna el color del nodo respectivo */
	char getColor(){
		return color; /** retorno de la variable de instancia color */
	}

	/** función que devuelve el dato que está guardado en el nodo */
	int /** T */ getDato(){ /** no necesita parámetro */
		return dato; /** retorna el atributo dato */
	}

	/** función que devuelve el valor de la llave */
	int getKey(){
		return key; /** retorno del valor del atributo llave */
	}

	/** método que asigna, a la instancia de la clase Nodo, el buffer con el que está trabajando el árbol */
	//void setPila(Pila& pila){ /** recibe como parámetro la referencia de la instancia de Pila */
	//this->pila = pila; /** asignación, por referencia para que se trabaje con la misma pila*/ // esta línea está rara
	//}

	/** método que inserta de forma recursiva en la posicion necesitada */
	Nodo* insertar(int key, Nodo* nodo1, Nodo* nodo2, ArbolRN& arbol){ /** recibe un key de tipo entero, y los punteros de 2 nodos */
		Nodo* llave = nodo1; /** inicializa el puntero con la referencia del nodo que sostiene a los inferiores, así no se perderán las conexiones del árbol */
		if(this->key != key){ /** se agrega si el key recibido como parámetro no se ha agregado previamente */
			/** se decide si ir al lado izquierdo (si el nodo nuevo tiene una llave menor) o derecho (si tiene una llave mayor) */
			int lado = IZQ; /** se inicializa como para agregar al lado izquierdo del nodo intermedio */
			if(key > nodo1->key){ /** si el key que se esta agregando es mayor que el del primer nodo; esta condición lleva al lado derecho si es necesario */
				lado = DER; /** asignación para trabajar sobre el lado derecho */
			}
			// cout << "Antes de ColorFlip llamado en Nodo" << endl;
			if(nodo1->hijo[IZQ] && nodo1->hijo[DER]){
				//cout << "Existen los hijos" << endl;
				//cout << "Color de Nodo IZQ: " << nodo1->hijo[IZQ]->getColor() << " Key: " << nodo1->hijo[IZQ]->getKey() << " Dato: " << nodo1->hijo[IZQ]->getDato() << endl;
				//cout << "Color de Nodo DER: " << nodo1->hijo[DER]->getColor() << " Key: " << nodo1->hijo[DER]->getKey() << " Dato: " << nodo1->hijo[DER]->getDato() << endl;
				if(nodo1->hijo[IZQ]->color == 'R' && nodo1->hijo[DER]->color == 'R'){
					arbol.colorFlip();
					cout << "ColorFlip llamado en Nodo" << endl;
				}
			}
			if(nodo1->hijo[lado]){ /** si existe un nodo de dicho lado */

				arbol.pila.agregarALaPila(nodo1); /** se agrega a la pila el primer nodo de los 2 ingresados (ya que está más arriba en la jerarquía) */
				// busco que el actual sea nodo intermedio (llave) hijo y no padre
				arbol.iterador.setPila(arbol.pila);
				++(arbol.iterador); /** el iterador toma la referencia del último nodo agregado al vector de punteros que funciona como buffer */

				// para metodos de visualizacion
				// cout << "El actual de iterador esta apuntando a " << (*iterador)->key << endl;

				/** invoca al método insertar del nodo hijo pasándole sus respectivos parámetros, almacena el nodo llave devuelto por la función recursiva */
				nodo1->hijo[lado] = nodo1->hijo[lado]->insertar(key, nodo1->hijo[lado], nodo2, arbol);
			}
			else{ /**  */
				llave = crearLlave(nodo1,nodo2); /** se crea el nodo intermedio con su respectiva llave y de una vez le asigna los nodos como hijos */
				// quise arreglar lo de que el actual fuera el hijo y no el padre, pero no
				//arbol.pila.agregarALaPila(llave); /** se agrega a la pila el nodo llave (ya que está más arriba en la jerarquía) */
					//arbol.iterador.setPila(arbol.pila);
					//++(arbol.iterador); /** el iterador toma la referencia del último nodo agregado al vector de punteros que funciona como buffer */
				//arbol.imprimirPila();

				cout << "Llave->Key: " << llave->getKey() <<" Color de Llave: " << llave->getColor() <<" Dato: " << llave->getDato() << endl;
				llave->imprimir(cout) << endl;
				arbol.imprimirPila();
				// cout << "Creo llave, antes de rotar" << endl;
			}
		}
		// cout << "Devuelve la llave" << endl;
		return llave; /** devuelve la llave que sostiene a los nodos inferiores */
	}

	/**metodo que nos dice si un dato existe o no dentro del arbol*/
	int existe(int dato){
		int esta = 0; /**inicializacion de la variable que se va a devolver, en este caso toma el valor de 0(no esta) por defecto*/
		if(this->dato!=dato){ /**condicion que realiza la comparacion entre el dato actual y el que se esta ingresando, si son iguales no entra*/
			int lado = IZQ; /**asumimos que vamos a ir hacia el lado izquierdo*/
			if(dato > this->dato){ /**comparamos si el dato ingresado es mayor que el actual*/
				lado = DER; /**en caso positivo de la condicion nos vamos al lado derecho*/
			}
			if(hijo[lado]){ /**comprobamos si existe ese lado, para no entrar en lugares de memoria sin determinar*/
				esta = hijo[lado]->existe(dato); /**si existe el nodo llamamos denuevo al metodo de forma recursiva al metodo con su hijo */
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
		salida << "Dato: "<< dato << " Key: " << key << " Color: " << color <<"\n"; /**manda a salida el dato y deja un espacio*/
		if(hijo[1]){ /**pregunta si el hijo derecho existe*/
			hijo[1]->imprimir(salida); /**llama de forma recursiva el metodo imprimir del hijo derecho*/
		}
		return salida; /**retorna el ostream*/
	}

	/** método para debuggear */
	ostream& imprimirA(ostream& salida){
		salida << "Dato: "<< dato << " Key:" << key << " Color: " << color <<"\n"; /**manda a salida el dato y deja un espacio*/
		return salida;
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
		/** método que le asigna al iterador la misma pila con la que trabaja el árbol */
		void setPila(Pila& pila){ /** recibe por referencia el objeto que contiene el vector de punteros que sirve como buffer */
			this->pila = pila; /** asignación de la pila con la que trabajará */
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

	void colorFlip(){ /** recibe el puntero del nodo padre */
		cout << "Entra al colorFlip" << endl;
		cout << "El actual seria " << iterador.actual->dato << endl;
		int ambos = 0; /** */
		/** si el hijo izquierdo y el hijo derecho son rojos lo almacena en la variable local */
		if( ('R' == iterador.actual->hijo[IZQ]->getColor()) && ('R' == iterador.actual->hijo[DER]->getColor()) ){
			ambos = 1;
		}

		if(ambos){ /** si ambos son rojos */
			/** pinta de Negro los nodos */
			iterador.actual->hijo[IZQ]->setColor('N');
			iterador.actual->hijo[DER]->setColor('N');
			iterador.actual->setColor('R'); /** y el padre se vuelve rojo */
		}
		/*cout << "Imprime el actual y sus hijos:" <<*/ iterador.actual->imprimir(cout) << endl;
	}

	/** método que se encarga de rotar nodos cuando la rama derecha se está haciendo muy grande, trabaja con los nodos intermedios llave */
	void rotacionSimpleIzquierda(){ /** no recibe parámetros, trabaja directamente con los atributos del árbol roji-negro */
		/** rotación de punteros */ /** si debe asignar el hijo derecho del bisAbuelo */
		// cout << "La raiz sostiene: " << endl;
		// raiz->imprimir(cout) << endl;
		// cout << "Actual (padre) sostiene: " << endl;
		// iterador.actual->imprimir(cout) << endl;

		// if(iterador.actual){
		// cout << "Color de Nodo actual: " << iterador.actual->getColor() << " Key: " << iterador.actual->getKey() << " Dato: " << iterador.actual->getDato() << endl;
		// if(iterador.actual->hijo[IZQ]){
		// cout << "Color de Nodo IZQ: " <<iterador.actual->hijo[IZQ]->getColor() << " Key: " << iterador.actual->hijo[IZQ]->getKey() << " Dato: " <<iterador.actual->hijo[IZQ]->getDato() << endl;
		// }
		// if(iterador.actual->hijo[DER]){
		// cout << "Color de Nodo DER: " << iterador.actual->hijo[DER]->getColor() << " Key: " << iterador.actual->hijo[DER]->getKey() << " Dato: " << iterador.actual->hijo[DER]->getDato() << endl;
		//}
		// }

		/// if(iterador.actual){
			/// cout << "iterador.actual: " << endl;
			/// iterador.actual->imprimirA(cout) << endl;
		// if(iterador.actual->hijo[DER]){
		// cout << "iterador.actual->hijo[DER]: " << endl;
		// iterador.actual->hijo[DER]->imprimirA(cout) << endl;
		// }
		/// }
		// else{
		// cerr << "iterador.actual es nulo " << endl;
		// }

		/// if(iterador.padre){
			/// cout << "iterador.padre: " << endl;
			/// iterador.padre->imprimirA(cout) << endl;
		/// }
		// else{
		// cerr << "iterador.padre es nulo " << endl;
		// }

		/// if(iterador.abuelo){
			 /// cout << "iterador.abuelo: " << endl;
			 /// iterador.abuelo->imprimirA(cout) << endl;
		/// }
		// else{
		// cerr << "iterador.abuelo es nulo " << endl;
		// }

		// if(iterador.bisAbuelo){
		// cout << "iterador.bisAbuelo: " << endl;
		// iterador.bisAbuelo->imprimirA(cout) << endl;
		// }
		// else{
		// cerr << "iterador.bisAbuelo es nulo " << endl;
		// }


		/** Aquí el iterador actual es el padre y el padre es el abuelo*/
		iterador.padre->hijo[DER] = iterador.actual->hijo[IZQ]; /** le damos el hijo izquierdo del padre al abuelo */
		iterador.actual->hijo[IZQ] = iterador.padre; /** el abuelo se vuelve hijo izquierdo del nodo padre */
		//cout << endl;
		/** después de reordenar las relaciones de padres e hijos */
		if(iterador.abuelo != raiz){ /** si no se va a cambiar de posición (bajár en la jerarquía) al nodo apuntado por la raíz,  */
			//cout << "existe el abuelo " << endl;
			iterador.abuelo->hijo[DER] = iterador.actual; /** el abuelo toma al nodo de mayor jerarquía */
		}
		else{ /** si el nodo apuntado por la raíz, bajará en el árbol */
			///	cout << "primera raiz: " << endl;
			//raiz->imprimirA(cout) << endl;
			//cout << "hijo[IZQ]: "; raiz->hijo[IZQ]->imprimirA(cout) << endl;
			//cout << "hijo[DER]: "; raiz->hijo[DER]->imprimirA(cout) << endl;
			///	cout << endl;

			///	cout << "Se sustituye la raiz" << endl;
			raiz = iterador.actual; /** el padre se asigna como nueva raíz */
			/// cout << "segunda raiz: " << endl;
			/// raiz->imprimirA(cout) << endl;
			//cout << "hijo[IZQ]: "; raiz->hijo[IZQ]->imprimirA(cout) << endl;
			//cout << "hijo[DER]: "; raiz->hijo[DER]->imprimirA(cout) << endl;
			/// cout << endl;
		}
		/// cout << "Imprime el arbol(rotacionIzquierda): " << endl;
		/// raiz->imprimir(cout) << endl;

		//------------------------------------------------------------------------------------------------------------------------------
		/** rotación de punteros */ /** si debe asignar el hijo derecho del bisAbuelo */
		//iterador.padre->hijo[DER] = iterador.actual->hijo[IZQ]; /** le damos el hijo izquierdo al abuelo */
		//iterador.actual->hijo[IZQ] = iterador.padre; /** el abuelo se vuelve hijo izquierdo del padre */
		//if(iterador.abuelo){
		//iterador.abuelo->hijo[IZQ] = iterador.actual; /** el bisAbuelo toma al nodo de mayor jerarquía */
		//}

		//}
	}

	void rotacionSimpleDerecha(){ /** se puede pasar a las siglas RSD */
		/** rotación de punteros */ /** si debe asignar el hijo derecho del bisAbuelo */
		iterador.padre->hijo[IZQ] = iterador.actual->hijo[DER]; /** le damos el hijo izquierdo al abuelo */
		iterador.actual->hijo[DER] = iterador.padre; /** el abuelo se vuelve hijo izquierdo del padre */
		if(iterador.abuelo != raiz){ /** si no se va a cambiar de posición (bajár en la jerarquía) al nodo apuntado por la raíz,  */
			//cout << "existe el abuelo " << endl;
			iterador.abuelo->hijo[IZQ] = iterador.actual; /** el abuelo toma al nodo de mayor jerarquía */
		}
		else{ /** si el nodo apuntado por la raíz, bajará en el árbol */
			///	cout << "primera raiz: " << endl;
			//raiz->imprimirA(cout) << endl;
			//cout << "hijo[IZQ]: "; raiz->hijo[IZQ]->imprimirA(cout) << endl;
			//cout << "hijo[DER]: "; raiz->hijo[DER]->imprimirA(cout) << endl;
			///	cout << endl;

			///	cout << "Se sustituye la raiz" << endl;
			raiz = iterador.actual; /** el padre se asigna como nueva raíz */
			/// cout << "segunda raiz: " << endl;
			/// raiz->imprimirA(cout) << endl;
			//cout << "hijo[IZQ]: "; raiz->hijo[IZQ]->imprimirA(cout) << endl;
			//cout << "hijo[DER]: "; raiz->hijo[DER]->imprimirA(cout) << endl;
			/// cout << endl;
		}
		//-------------------------------------------------------------------------------------------------------------------------------
		/** rotación de punteros */ /** si debe asignar el hijo derecho del bisAbuelo */
		//iterador.padre->hijo[IZQ] = iterador.actual->hijo[DER]; /** le damos el hijo izquierdo al abuelo */
		//iterador.actual->hijo[DER] = iterador.padre; /** el abuelo se vuelve hijo izquierdo del padre */
		//if(iterador.abuelo){
		//iterador.abuelo->hijo[IZQ] = iterador.actual; /** el bisAbuelo toma al nodo de mayor jerarquía */
		//}
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
		iterador.bisAbuelo = iterador.abuelo;
		/** el abuelo es el mismo */
		iterador.padre = iterador.actual; /** el hijo pasa a ser padre */
		iterador.actual = iterador.abuelo->hijo[IZQ]; /** el primer padre pasa a ser hijo */
		rotacionSimpleDerecha();
	}

	/** el método público insertar de la clase ArbolRN recibe como parámetro la llave y el dato de tipo T que corresponderán al nodo hoja */
	void insertar(int key, int dato){
		Nodo* hoja = new Nodo(key,dato); /** crea en el heap un nodo hoja con los parámetros recibidos y guarda su referencia */
		//cout << "Color de Hoja: " << hoja->getColor()<< endl;
		if(raiz){ /** si el árbol tiene una raíz válida */
			if(raiz->color == 'R'){
				cambioColorRaiz();
			}

			raiz = raiz->insertar(key, raiz, hoja, *this); /** se le indica a la raíz del árbol el dato, y los 2 nodos con los cuales generará el nodo intermedio llave (método recursivo) */ //creo que ocupamos psarle tambien la referencio de raiz a este metodo y el nodo tambien se lo estamos pasando por parametro

			if(*(iterador)){
				if((*(iterador))->color == 'R'){
					cout << "primera raiz: " << endl;
					raiz->imprimirA(cout) << endl;
					cout << "hijo[IZQ]: "; raiz->hijo[IZQ]->imprimirA(cout) << endl;
					cout << "hijo[DER]: "; raiz->hijo[DER]->imprimirA(cout) << endl;
					cout << endl;

					cout << "Se sustituye la raiz" << endl;
					rotacionSimpleIzquierda();
					cout << "segunda raiz: " << endl;
					raiz->imprimirA(cout) << endl;
					cout << "hijo[IZQ]: "; raiz->hijo[IZQ]->imprimirA(cout) << endl;
					cout << "hijo[DER]: "; raiz->hijo[DER]->imprimirA(cout) << endl;
					cout << endl;

					//if(lado){
					// cout << "Aqui rotaria a la izquierda" << endl;
					//	cout << "Antes de rotar izquierda" << endl;

					//	cout << "Despues de rotar izquierda" << endl;
					//}
					//else{
					//arbol.rotacionSimpleDerecha();
					//cout << "Despues de rotar derecha" << endl;
					//}

				}
			}

		}
		else{ /** si el árbol no tiene raíz */
			raiz = hoja; /** la primera raíz es el primer nodo ingresado, cuando se ingrese el siguiente nodo la raíz será un nodo llave */
			//pila.agregarALaPila(raiz);  aqui creo que no se agrega porque apenas es la primera hoja agregada no se baja
		}

		// las siguientes 2 líneas son para pruebas
		//cout << "contador de nodos agregados de pila" << pila.contadorDeNodosAgregados << endl;
		//imprimirPila();

		pila.limpiarPila(); /** establece las celdas del vector, que funciona como buffer, en punteros nulos */
		cout << endl;
	}

	/** método que verifica si el dato ingresado como parámetro existe en el árbol, llama recursivamente al método existe de los nodos */
	int existe(int dato){ /** recibe un dato de tipo T como parámetro */
		int esta = 0; /** inicializamos la variable en 0, como si no estuviera el dato en el árbol */
		if(raiz){ /** si existe la raíz, entra */
			esta = raiz->existe(dato); /** esta almacena si existe el dato, llamado al metodo existe del nodo */
		}
		return esta; /** retorna el resultado de si el dato está o no está en el árbol */
	}

	void imprimirPila(){
		cout << "La Pila se va a imprimir" << endl;
		cout << "{ | ";
		for(int i = 0; i < pila.contadorDeNodosAgregados; ++i){
			cout << "Dato: " << pila.buffer[i]->dato << " Key: "<< pila.buffer[i]->key << " | ";
		}
		cout << " }" << endl;
	}


	//metodo que no se utiliza en este momento pero puede ser que a futuro nos llegue a servir
	/*void setLengthPila(int length){
	this->pila.setLength(length);
}*/

};
#endif


// Hacer la siguiente prueba, insertar 1 y 2, lo que debe salir en consola debe ser 1 1 2

//RECORDATORIO

// revisar iterador, ojo con los índices negativos
// línea 261
// falta indicar qué tipo de rotación efectuar y probar rotación derecha

// Pasar el nombre del archivo .h a ArbolRN
// Cuidado con setLength()
// ver si Pila tiene un nombre apropiado, por su forma del manejo de datos, podría cambiarse a Buffer

// se crea como atributo una instancia de la clase Pila en Nodo para facilitar el manejo de la misma, preguntar a Casasola
// si eso es correcto o si debe incluirse solamente donde se interactue con la pila, Nodo no tiene que ver con la Pila, sino alguna clase como iterador

//el metodo agregar necesita ir llenando la pila conforme va bajando y verificar si hay que hacer color flip o las rotaciones
//ahorita estamos realizando pruebas con int en general pasar a tipo T despues
//probar los metodos colorFlip y rotaciones...
//ocupamos implementar el ++ de iterador dentro de nodo ya que ahi se realiza el insertar en la pila, asi que ocupamos pasarle una referencia de iterador

// Pila debería de encargarse de la impresión de los valores a los que apunta su vector de punteros, no árbol.

// Correcciones
// en el constructor se le indica al iterador el buffer con el que trabajará, para no repetirlo varias veces en el código, y el diseño se debe implementar en el construtor
// Corrección del rotación simple izquierda, primer caso funciona, verificar para los casos siguientes.
// se sacó rotación