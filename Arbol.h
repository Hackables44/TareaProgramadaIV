class Arbol{
private:
  class Nodo{
    public:
      char color;
      int key;
      int dato;

      Nodo* hijo[2];
      Nodo();
      Nodo(int dato);
      Nodo(int key, int NoSeUsa);
      Nodo(Nodo* nodo1, Nodo* nodo2);
      ~Nodo();
      void setColor(char color);
      void setDato(int dato);
      void setKey(int key);
      char getColor();
      int  getDato();
      int getKey();
      void insertar(int dato, Nodo* nodo1);
      int existe(int dato);

  };
  class Pila{
    friend class Iterador;

			public:
				Nodo** buffer;
				int contadorDeNodosAgregados;
				int length;

        void _init();
        Pila(int length);
        Pila();
        ~Pila();
        void limpiarPila();
        void agregarALaPila(Nodo* nodo);
        int getContadorDeNodos();
        Nodo * getPtrNodo(int indice);
        int posValida(int indice);
  };

  Nodo* raiz;
  Pila pila;

public:
  class Iterador{
    Pila pila;
    Nodo * bisAbuelo;
    Nodo * abuelo;
    Nodo * padre;
    Nodo * actual; 

    void _initPtr();
    Iterador();
    ~Iterador();
    void operator++();
    void operator--();
    Nodo* operator*();
    void setPila(Pila& pila);
    };
    Iterador iterador;

    //Metodos de arbol

    ArbolRN();
    ~ArbolRN();
    void cambioColorRaiz();
    void colorFlip(Nodo * padre);
    void rotacionSimpleIzquierda();
    void rotacionSimpleDerecha();
    void rotacionDobleIzquierda();
    void rotacionDobleDerecha();
    void insertar(int dato);
    int existe(int dato);
};
