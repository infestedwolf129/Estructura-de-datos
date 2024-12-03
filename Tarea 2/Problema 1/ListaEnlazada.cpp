#include <iostream>
#include <fstream>
#include <cstring>

typedef int tElemLista;

class Lista{
    private:
        typedef struct nodo{
            struct nodo *sig;
            tElemLista info;
        }tNodo;
        tNodo *head;
        tNodo *curr;
        tNodo *tail;
        int largo;
        double pos;
    public:
        Lista(){
            head = NULL;
            curr = NULL;
            tail = NULL;
            largo = 0;
            pos = 0;
        }
        void clear();
        int length();
        void insert(tElemLista a);
        void next();
        void prev();
        char remove();
        void moveToStart();
        void moveToEnd();
        char getValue();
};

/*
* void Lista::clear()
**
* La función clear se encarga de limpiar una lista ya usada anteriormente reestableciendo cada variable, como pueden ser head y tail, a su estado original.  
**
* Input:
* Esta función no tiene input.
**
* Returns:
* Al ser tipo void no existe un return en esta función.
*/

void Lista::clear(){
    tNodo *AUX;
    while(head != NULL){
        AUX = head;
        if (head == NULL) break;
        head = head->sig;
        delete AUX;
        AUX = NULL;
    }
    largo = 0;
    pos = 0;
    head = NULL;
    curr = NULL;
};

/*
* int Lista::length()
**
* La función length se encarga de entregar el largo total de la lista.  
**
* Input:
* Esta función no tiene input.
**
* Returns:
* Retorna el largo de la lista en formato int.
*/

int Lista::length(){
    return largo;
};

/*
* void Lista::insert(tElemLista a)
**
* La función insert está encargada de insertar un elemento en la posición actual de la lista, existen condiciones dependiendo de donde
* se este insertando el elemento, en la posicion head, tail o entre dos elementos.
**
* Input:
* EL insert es el elemento que se quiere insertar almacenado en una variable.
**
* Returns:
* Al ser tipo void no existe un return en esta función.
*/

void Lista::insert(tElemLista a){
    if(largo == 0){
        moveToStart();
        tNodo * nuevo = new tNodo;
        nuevo->info = a;
        head = nuevo;
        curr = nuevo;
        tail = nuevo;
        nuevo->sig = NULL;
        largo++;
    }else{
        if(pos == 0){
            tNodo* nuevo = new tNodo;
            nuevo->info = a;
            nuevo->sig = head;
            head = nuevo;
            curr = head;
            largo++;
        }else{
            tNodo * nuevo = new tNodo;
            nuevo->info = a;
            nuevo->sig = curr;
            prev();
            curr->sig = nuevo;
            next();
            largo++;
        }
    }
};

/*
* void Lista::next()
**
* La función next es encargada de avanzar la posición actual del nodo al siguiente.
**
* Input:
* Esta función no tiene input.
**
* Returns:
* Al ser tipo void no existe un return en esta función.
*/

void Lista::next(){
    if(curr->sig != NULL){
        curr = curr->sig;
        pos++;
    }
};

/*
* void Lista::prev()
**
* La función prev es encargada de retroceder la posición actual del nodo al anterior.
**
* Input:
* Esta función no tiene input.
**
* Returns:
* Al ser tipo void no existe un return en esta función.
*/

void Lista::prev(){
    if(curr != head){
        tNodo * aux = head;
        while (aux->sig != curr){
            aux = aux->sig;
        }
        curr = aux;
        pos--;
    }
};

/*
* char Lista::remove()
**
* Toma el nodo actual y lo elimina dejando como actual el siguiente a este.
**
* Input:
* No requiere de un input al ser función de la clase Lista.
* .......
**
* Returns:
* char, Retorna el nodo siguiente como actual.
*/

char Lista::remove(){
    if(largo != 0){
        if(pos == 0){
            tNodo *aux = head;
            head = head->sig;
            int b = aux->info;
            delete aux;
            largo--;
            return b;
        }else{
            tNodo *aux = curr->sig;
            prev();
            int b = curr->sig->info;
            delete curr->sig;
            curr->sig = aux;
            largo--;
            next();
            return b;
        };
    };
    return -1;
};


/*
* void Lista::moveToStart()
**
* La función moveToStart es encargada de avanzar la posición actual del nodo al head, es decir, al principio de la lista.
**
* Input:
* Esta función no tiene input.
**
* Returns:
* Al ser tipo void no existe un return en esta función.
*/

void Lista::moveToStart(){
    curr = head;
    pos = 0;
};


/*
* void Lista::moveToEnd()
**
* La función moveToEnd es encargada de retroceder la posición actual del nodo al tail, es decir, al final de la lista.
**
* Input:
* Esta función no tiene input.
**
* Returns:
* Al ser tipo void no existe un return en esta función.
*/

void Lista::moveToEnd(){
    curr = tail;
    pos = largo - 1;
};

/*
* char Lista::getValue();
**
* Toma información del nodo actual y se lo retorna al usuario.
**
* Input:
* Esta función no necesita parámetros, ya que proviene de la clase Lista.
* .......
**
* Returns:
* char, Retorna información de nodo actual.
*/

char Lista::getValue(){
    return curr->info;
};


