#include <iostream>
#include <fstream>
#include <cstring>


typedef int tElem;

struct tNodoArbolBin{
    tElem info;
    tNodoArbolBin* izq;
    tNodoArbolBin* der;
};

class RankedABB {
    private:
        tNodoArbolBin *Raiz; // puntero al nodo raíz del ABB
        int nElems; // cantidad de elementos en el ABB
    public:
        RankedABB(){
            Raiz = NULL;
            nElems = 0;
        }
        ~RankedABB(){
            // destructor
        }
        // inserta el elemento x en el árbol.
        void insert(tElem x); 

        // dado un elemento x, no necesariamente almacenado previamente en el ABB, retorna la cantidad de elementos que son menores o iguales a x.
        int rank(tElem x); 

        // busca el elemento x en el árbol y retorna un valor verdadero de encontrarse en el árbol.
        bool find(tElem x);

        // recorrido in-orden de un ABB
        void inOrden();
};
