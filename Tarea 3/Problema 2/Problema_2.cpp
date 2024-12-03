//PROBLEMA 2

#include <iostream>
#include <sstream>
#include <fstream>
#include "tGrafo.cpp"

using namespace std;


struct informacion{
    int ID;
    string NOMBRE;
};

/*****
* informacion* RecogerDatosPersonajes
******
* Abre el archivo csv de los nombres y se encarga de
* recolectarlos dentro de un arreglo de struct
******
* Input:
* int n : Número entero que representa la cantidad de datos a recolectar
******
* Returns:
* informacion*, Retorna un arreglo de struct con la informacion recopilada de todos los personajes
*****/
informacion* RecogerDatosPersonajes(int n){
    ifstream personajes("miserables_id_to_names.csv");

    char delimitador = ',';
    string linea;
    getline(personajes, linea);

    informacion* DATOS = new informacion[n];

    int i=0;
    while(getline(personajes, linea)){
        stringstream stream(linea);
        string ID, nombre;
        getline(stream,ID,delimitador);
        getline(stream,nombre,delimitador);
        DATOS[i].ID = stoi(ID);
        DATOS[i].NOMBRE = nombre;
        i++;
    };
    
    personajes.close();
    return DATOS;
};

/*****
* tGrafo RecogerDatosMatriz
******
* Abre el archivo csv con la matris de adyacencia que
* registra las veces que salen 2 personajes juntos y las recolecta
* en un grafo para su uso.
******
* Input:
* int n : Entero encargado de dictar el tamaño del grafo.
******
* Returns:
* tGrafo, Retorna un grafo fabricado con los datos del archivo csv
*****/
tGrafo RecogerDatosMatriz(int n){
    ifstream matriz;
    matriz.open("miserables.csv", ios::in);

    char delimitador = ';';
    string linea;
    getline(matriz,linea);

    tGrafo grafo(n);
    
    int i = 0;
    while(getline(matriz,linea)){

        stringstream stream(linea);
        string ID,PESO;
        getline(stream,ID,delimitador);

        int j=0;
        while(getline(stream,PESO,delimitador)){
            grafo.setEdge(i,j,stoi(PESO));
            j++;
        };
        i++;
    }

    matriz.close();
    return grafo;
};

/*****
* int EncontrarProtagonista
******
* Analiza el grafo para encontrar el vértice de mayor grado 
* y asignarlo como protagonista para mostrarlo por pantalla.
******
* Input:
* tGrafo Grafo : Grafo que contiene la informacion del archivo con la Matriz de adyacencia
* informacion* DATOS : Arreglo de struct que contiene la informacion correspondiente al valor del vértice
******
* Returns:
* int, Retorna el número del vertice que es considerado como protagonista.
*****/

int EncontrarProtagonista (tGrafo Grafo, informacion* DATOS){
    int Protagonista = Grafo.maxGrade();
    cout << "Personaje Principal: " << DATOS[Protagonista].NOMBRE << endl;
    return Protagonista;
};

int main(){
    
    int cantDatos = 77; 
    int *D = new int[cantDatos];

    for(int i = 0; i < cantDatos; i++){
        D[i] = INFINITO;
    }

    informacion* DATOS = RecogerDatosPersonajes(cantDatos);
    tGrafo grafo = RecogerDatosMatriz(cantDatos);
    int Protagonista = EncontrarProtagonista(grafo, DATOS);
    D[Protagonista] = 0;
    grafo.Dijkstra(grafo, D, Protagonista);
    
    int Secundario = 0;
    int mayorDistancia = D[0];

    for(int i = 0; i < cantDatos; i++){
        if(D[i] > mayorDistancia){
            mayorDistancia = D[i];
            Secundario = i;
        }
    };
    cout << "Personaje Secundario más Relevante: " << DATOS[Secundario].NOMBRE << endl;
    grafo.clearD(grafo, D);


    long double LongitudCaminoPromedio = grafo.averageDistance(grafo, D);
    cout << "Diametro: " << LongitudCaminoPromedio << endl;


    long double LongitudCaminoPromedioConPesos = grafo.averageWeightedDistance(grafo, D);
    cout << "Diametro (con pesos): " << LongitudCaminoPromedioConPesos << endl;
    

    delete[] DATOS;
};