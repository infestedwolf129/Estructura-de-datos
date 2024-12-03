#include <iostream>
#include <fstream>
#include <cstring>
#include "ABB.cpp"

//-------------------------------------Función find----------------------------------------------
/*
*
* bool findHelp()

* Función recursiva que ayuda a encontrar un número específico dentro del árbol.

* Input:
* - tNodoArbolBin *nodo : Es el puntero que representa el nodo del árbol que se está analizando,
    su información será analizada para saber si es el elemento que está buscando la función.
* - tElem item : Item a buscar en el árbol.
* .......
**
* Returns:
* - findHelp(), vuelve a la misma función, pero ahora con nuevos parámetros que permiten "navegar"
    dentro del árbol.
* - bool, si el item no está en el árbol, será false; si el item está en el árbol, será true.
*/

bool findHelp(tNodoArbolBin *nodo, tElem item) {
    if (nodo == NULL) return false; // item no está en el ABB
    if (nodo->info == item) return true; // item encontrado
    if (item < nodo->info){ 
        return findHelp(nodo->izq, item);}
    else {
        return findHelp(nodo->der, item);}
}

/*
*
* bool RankedABB::find()

* Función de la clase Ranked ABB, que llamará a una función auxiliar para determinar si un 
  elemento determinado se encuentra dentro de árbol.

* Input:
* tElem item : Item a buscar en el árbol.
* .......
**
* Returns:
* bool, la función findHelp() determinará su valor.
*/

bool RankedABB::find(tElem item) {
    return findHelp(Raiz, item);
}
//-----------------------------------------------------------------------------------------------

//-------------------------------------Función Insert--------------------------------------------

/*
*
* void insertHelp()

* Función recursiva que permite la inserción de un nodo dentro de nuestro árbol. Esta compara la
  la información del Nodo creado previamente en la función RankedABB::insert(), con los nodos del 
  árbol, para determinar su ubicación dentro de este.

* Input:
* tNodoArbolBin *Nodo : Nodo que permite la "navegación" dentro del árbol. Debido a esto, su valor
  inicial es la raiz, pero luego puede tomar los valores de otros nodos debido a la función recursiva.
  tNodoArbolBin *NewNode : Nodo que contiene el elemento que queremos añadir a nuestro árbol
* .......
**
* Returns:
* Nada, es una función void que ejecuta una acción.
*/

void insertHelp(tNodoArbolBin *Nodo,tNodoArbolBin *NewNode){
    if (NewNode->info == Nodo->info) return;
    else if (NewNode->info < Nodo->info){
        if (Nodo->izq != NULL){
            insertHelp(Nodo->izq, NewNode);
            }
        else{
            Nodo->izq = NewNode;
        }
    }
    else if (NewNode->info > Nodo->info){
        if(Nodo->der != NULL){
            insertHelp(Nodo->der, NewNode);
        }
        else{
            Nodo->der = NewNode;
        }
    }
}

/*
*
* RankedABB::insert()

* Función que inicializa el proceso de inserción de un elemento deseado. En un inicio, creo un
  nodo que almacena el elemento deseado, para luego ser insertado con la ayuda de la función 
  insertHelp(). Además, si se está insertando en un árbol vacío, esta función hará que la raíz
  sea el nodo recién creado.

* Input:
* tElem x : Elemento a añadir al árbol.
* .......
**
* Returns:
* Nada, es una función void que ejecuta una acción.
*/

void RankedABB::insert(tElem x) {
    //Se crea el nodo a insertar
    tNodoArbolBin *NewNode = new tNodoArbolBin;
    NewNode->info = x;
    
    //Si el árbol no tiene una raíz, el nuevo nodo lo transformará en la raíz
    if (Raiz == NULL) {
        Raiz = NewNode;
        nElems++;
    }
    else{
        insertHelp(Raiz, NewNode);
    };
};
//-----------------------------------------------------------------------------------------------


//-------------------------------------Función Rank----------------------------------------------

/*
*
* int rankrec()

* Función recursiva que permite contar la cantidad de elementos presentes en el árbol que sean 
  menores o iguales a algún elemento previamente declarado en la función RankedABB::rank(). Ocupa 
  un método similar al de recorrido In-Orden de un árbol para contar.

* Input:
* - tNodoArbolBin *nodo : Nodo que permite la "navegación" dentro del árbol. Debido a esto, su valor
    inicial es la raiz, pero luego puede tomar los valores de otros nodos debido a la función recursiva.
  - int counter : Contador de elementos menores o iguales a x.
  - tElem x : Elemento a comparación.
* .......
**
* Returns:
* int, retorna el número de elemento menores o iguales al elemento declarado.
*/

int rankrec(tNodoArbolBin *nodo,int counter,tElem x){
    if (nodo == NULL) return counter;
    counter = rankrec (nodo->izq,counter,x);
    if(nodo->info <= x){
        counter++;
    }
    counter = rankrec (nodo->der,counter,x);
    return counter;
};

/*
*
* int RankedABB::rank()

* Función que inicializa el proceso para contar la cantidad de elementos presentes en el árbol que sean 
  menores o iguales a un elemento x. Incluye un contador que inicializa en 0, que será ocupado después 
  en rankrec()

* Input:
* tElem x : Elemento a comparación.
* .......
**
* Returns:
* int, retorna el número de elemento menores o iguales al elemento declarado.
*/

int RankedABB::rank(tElem x){
    int counter = 0;
    return rankrec(Raiz,counter,x);
};
//-----------------------------------------------------------------------------------------------