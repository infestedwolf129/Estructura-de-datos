#include <iostream>
#include <fstream>
#include <cstring>
#include "ListaEnlazada.cpp"
using namespace std;


/*****
* void  comprobarCaracter()
******
* Toma el caracter actual y comprueba que no sea alguno especial que realice movimiento en el elemento actual.
******
* Input:
* Lista &newList : Entrega lista generada para su iteración.
* char caracter : Entrega caracter actual para realizar comparacion con las restricciones del problema ('<';'>';'[';']').
* .......
******
* Returns:
* Al ser tipo void no existe un return en esta función.
*****/

void comprobarCaracter(Lista &newList, char caracter){
    if(caracter == '<'){
        newList.prev();
    }
    else if(caracter == '>'){
        newList.next();
    }
    else if(caracter == '['){
        newList.moveToStart();
    }
    else if(caracter == ']'){
        newList.moveToEnd();
    }else{
        newList.insert(caracter);
        newList.next();
    } 
};

/*****
* Lista generarLista()
******
* Recibe como parámetros las características de la lista a generar junto con esta misma vacía, por lo que itera dentro del string entregado así obteniendo cada caracter, comprobrandolo y generar la lista con las condiciones deseadas.
******
* Input:
* string aux : Corresponde a una linea obtenida del archivo a leer.
* int largo : Corresponde al largo del string para poder iterar sobre este.
* Lista &newList: Corresponde a la lista vacia generada para poder ingresar datos dentro de ella, dando así una lista generada con elementos.
* .......
******
* Returns:
* Lista, Retorna la lista generada con los elementos ya incluídos en ella.
*****/

Lista generarLista(string aux, int largo, Lista &newList){
    char a = '+';
    newList.insert(a);
    for (int i =0; i < largo; i++){
        char caracter = aux[i];
        if(newList.length() == 0){
            newList.moveToStart();
            comprobarCaracter(newList,caracter);
        }
        else{
            comprobarCaracter(newList,caracter);
        }
    };
    newList.moveToEnd();
    newList.remove();
    newList.moveToStart();
    return newList;
};


int main(){
    ifstream archivo;   //archivo de entrada.
    archivo.open("teclado-entrada.txt", ios::in);
    ofstream Final;     //archivo de salida.
    Final.open("teclado-salida.txt", ios::app);
    string aux;
    int largo;
    Lista newList;
    while(!archivo.eof()){   
        archivo >> aux;     //obtencion de linea en archivo de entrada.
        largo = aux.length();
        newList = generarLista(aux,largo,newList);
        newList.moveToStart();
        for (int i=0 ; i < newList.length();i++){   //escritura dentro del archivo de salida.
            Final << newList.getValue();
            newList.next();
        }
        Final << endl;
        newList.clear();    //reinicio de lista para poder iterar siguiente linea del archivo.
        newList.moveToStart();
    }
    archivo.close();
    return 0;
}