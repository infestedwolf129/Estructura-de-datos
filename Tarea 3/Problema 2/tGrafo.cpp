#include <iostream>
#include <cstring>
#define NOVISITADO 0
#define VISITADO 1
#define INFINITO 100000

using namespace std;

typedef int tVertice;

struct DatosVertice{
    int Marca;
    int Grado;
};


class tGrafo{

        private:
        DatosVertice* vertices;
        int V;
        int E;
        tVertice** MatrizADJ;

    public:
        tGrafo(int n){
            
            vertices = new DatosVertice[n];
            MatrizADJ = new tVertice*[n];
            V= n;

            for(int i = 0; i < n; i++){
                MatrizADJ[i] = new tVertice[n];
            }
            

            for(int i = 0; i < n ; i++){
                vertices[i].Marca = NOVISITADO;
                vertices[i].Grado = 0;
            }
            
            for(int i = 0; i < n ; i++){
                for(int j = 0; j < n; j++){
                    MatrizADJ[i][j] = INFINITO;
                }
                MatrizADJ[i][i] = 0;
            }
        }

        int nVertex();
        int nEdges();
        tVertice first(tVertice v);
        tVertice next(tVertice v, tVertice w);
        void setEdge (tVertice v1, tVertice v2, int peso);
        void deleteEdge (tVertice v1, tVertice v2);
        int isEdge (tVertice v1, tVertice v2);
        int weight (tVertice v1, tVertice v2);
        int getMark (tVertice v);
        void setMark (tVertice v, int marca);
        int minVertex(tVertice v, int *D);
        int maxGrade();
        void Dijkstra(tGrafo& G, int *D, tVertice s);
        void clearD(tGrafo& G, int *D);
        long double averageDistance(tGrafo& G, int *D);
        long double shortestPath(int *D);
        long double factorial(long double n);
        long double sumatoriaPesos();
        long double weightedshortestPath(int *D);
        long double averageWeightedDistance(tGrafo& G, int *D);
};

/*****
* int nVertex
******
* Funcion encargada de entregar cantidad total de vértices del grafo
******
* Input:
* No recibe parametros
******
* Returns:
* int, Retorna cantidad total de vértices del grafo
*****/
int tGrafo::nVertex(){
    return V;
}

/*****
* int nEdges
******
* Funcion encargada de entregar cantidad total de arcos del grafo
******
* Input:
* No recibe parametros
******
* Returns:
* int, Retorna cantidad total de arcos del grafo
*****/
int tGrafo::nEdges(){
    return E;
}

/*****
* tVertice first
******
* Devuelve el primer vecino de un vértice v dado (asume que los
* vecinos de un vértice están ordenados por número de vértice)
******
* Input:
* tVertice v : Vertice desde el cual se busca su vecino más cercano
******
* Returns:
* tVertice i, Retorna el primer vecino del vértcice v
* tVertice v, Retorna el mismo vértice dado en caso de no tener vecino
*****/
tVertice tGrafo::first(tVertice v){
    for (int i = 0; i < V ; i++){
        if (MatrizADJ[v][i]!= 0){
            return i;
        };
    };
    return v;
}

/*****
* tVertice next
******
* Devuelve el menor vecino de v, cuya numeración es mayor a w.
* Si no existe dicho vecino, retorna el número de vértices del grafo
******
* Input:
* tVertice v : Vértice del grafo a consultar
* tVertice w : Vértice del grafo utilizado como condiciónal
******
* Returns:
* tVertice i, Retorna menor vecino de v, cuya numeración es mayor a w.
* int V, Retorna V en caso de no existir vecino.
*****/
tVertice tGrafo::next(tVertice v, tVertice w){
    for(int i = w+1 ; i < V; i++){
        if(MatrizADJ[v][i] != 0 && w < i){
            return i;
        }
    }
    return V;
}

/*****
* void setMark
******
* Marca un vértice con un valor dado
******
* Input:
* tVertice v : Vértice del grafo a consultar
* int marca : Valor con el que se marca
******
* Returns:
* void No existe return 
*****/
void tGrafo::setMark(tVertice v, int marca){
    vertices[v].Marca = marca;
}

/*****
* int getMark
******
* Obtiene la marca de un vértice dado
******
* Input:
* tVertice v : Vértice del grafo a consultar
******
* Returns:
* int Retorna marca de vertice consultado
*****/
int tGrafo::getMark(tVertice v){
    return vertices[v].Marca;
};

/*****
* void setEdge
******
* Agrega un nuevo arco al grafo entre vértices v1 y v2 asignando un peso.
* Además aumenta el grado de ambos vértices.
******
* Input:
* tVertice v1 : Vértice inicial del arco
* tVertice v2 : Vértice final del arco
* int peso : Peso del arco establecido
******
* Returns:
* void No existe return 
*****/
void tGrafo::setEdge(tVertice v1, tVertice v2, int peso){
    MatrizADJ[v1][v2] = peso;
    MatrizADJ[v2][v1] = peso;
    E++;
    vertices[v1].Grado++;
    vertices[v2].Grado++;
};

/*****
* void deleteEdge
******
* Elimina un  arco del grafo entre vértices v1 y v2.
* Además disminuye el grado de ambos vértices.
******
* Input:
* tVertice v1 : Vértice inicial del arco
* tVertice v2 : Vértice final del arco
******
* Returns:
* void No existe return 
*****/
void tGrafo::deleteEdge(tVertice v1, tVertice v2){
    MatrizADJ[v1][v2] = INFINITO;
    MatrizADJ[v2][v1] = INFINITO;
    E--;
    vertices[v1].Grado--;
    vertices[v2].Grado--;
};

/*****
* int isEdge
******
* Dado dos vértices, indica si existe un arco entre ellos.
******
* Input:
* tVertice v1 : Vértice inicial del arco
* tVertice v2 : Vértice final del arco
******
* Returns:
* int Retorna true si existe arco entre v1 y v2.
* int Retorna false si no existe arco entre v1 y v2.  
*****/
int tGrafo::isEdge(tVertice v1, tVertice v2){
    if(MatrizADJ[v1][v2] != INFINITO) return true;
    else return false;
}

/*****
* int weight
******
* Devuelve el peso de un arco del grafo (0 si no existe).
******
* Input:
* tVertice v1 : Vértice inicial del arco
* tVertice v2 : Vértice final del arco
******
* Returns:
* int Retorna peso del arco entre v1 y v2 si existe.
* int Retorna 0 si no existe arco entre v1 y v2.  
*****/
int tGrafo::weight(tVertice v1, tVertice v2){
    if (MatrizADJ[v1][v2] == INFINITO) return 0;
    else return MatrizADJ[v1][v2];
}

/*****
* int maxGrade
******
* Devuelve el vertice con mayor grado del grafo luego de ser revisado
* los datos de cada uno.
******
* Input:
* No requiere inputs
******
* Returns:
* int Retorna el vertice de mayor grado del grafo. 
*****/
int tGrafo::maxGrade(){
    int max = vertices[0].Grado;
    int vert = 0;

    for(int i = 0; i < V ; i++){
        if(max < vertices[i].Grado){
            max = vertices[i].Grado;
            vert = i;
        }
    }
    return vert;
}

/*****
* int minVertex
******
* Devuelve el vértice de menor distancia desde un vértice dado.
******
* Input:
* tVertice s : Vértice desde el que se toma la distancia.
* int *D : Puntero a arreglo de distancias a todos los vértices desde s.
******
* Returns:
* int Retorna el vertice de menor distancia desde s.
*****/
int tGrafo::minVertex(tVertice s, int *D){
    int j = 0;
    int o = INFINITO;
    
    for(int i = 0; i < V; i++){
        if(vertices[i].Marca == NOVISITADO && D[i] < o){
            o = D[i];
            j = i;
        }
    }
    return j;
}

/*****
* void Dijkstra
******
* Ejecuta el algoritmo Dijkstra que se encarga de ver los caminos mas cortos de un vértice dado..
******
* Input:
* tGrafo& G : Grafo por referencia en el cual se itera el algoritmo
* int *D : Puntero a arreglo de distancias del vértice.
* tVertice s : Vértice a analizar en Dijkstra
******
* Returns:
* void No existe return
*****/
void tGrafo::Dijkstra(tGrafo& G, int *D, tVertice s){
    tVertice v, w;
    int i;
    for(i=0; i < G.nVertex();i++){
        v = minVertex(s, D);
        if (D[v] == INFINITO)
            return;
        G.setMark(v, VISITADO);
        for (w = G.first(v); w < G.nVertex() ; w = G.next(v, w))
            if(D[w] > (D[v] + G.weight(v, w)))
                D[w] = D[v] + G.weight(v, w);
    }
};

/*****
* void clearD
******
* Limpia arreglo de distancias de un vértice.
******
* Input:
* tGrafo& G : Grafo por referencia en el cual esta almacenado las marcas de los vértices.
* int *D : Puntero a arreglo de distancias del vértice
******
* Returns:
* void No existe Return
*****/
void tGrafo::clearD(tGrafo& G, int *D){
    for(int i = 0; i < V; i++){
        D[i] = INFINITO;
        G.setMark(i,NOVISITADO);
    };
}

/*****
* long double factorial
******
* Calcula el valor factorial de un n
******
* Input:
* long double n : Valor dado al que se le calcula su factorial
******
* Returns:
* long double n*factorial(n-1) si el n es un numero mayor a 1
* long double 0 si el valor n es menor a 0 
*****/
long double tGrafo::factorial (long double n){
    if (n < 0){
        return 0;
    } else if (n > 1){
        return n*factorial(n-1);
    }
    return 1;
}

/*****
* long double shortestPath
******
* Devuelve el largo del camino más corto que NO 
* toma en cuenta el peso del arco
******
* Input:
* int *D : Puntero a arreglo de distancias del vertice
******
* Returns:
* long double Retorna el valor total del camino más corto
*****/
long double tGrafo::shortestPath(int *D){
    long double total = 0;
    for(int i = 0; i<V ; i++){
        if(D[i] != 0){
            total++;
        }        
    }
    return total;
}

/*****
* long double averageDistance
******
* Devuelve la longitud de camino promedio del grafo 
* dada por la distancia promedio
******
* Input:
* tGrafo& G : Grafo creado sobre el que se itera
* int *D : Puntero a arreglo de distancias del vértice
******
* Returns:
* long double Retorna el resultado de la operacion de una sumatoria divido combinatoria para calcular distancia promedio 
*****/
long double tGrafo::averageDistance(tGrafo& G, int *D){
    long double sumatoria = 0;

    for(tVertice i = 0; i < V; i++){
        G.Dijkstra(G, D, i);
        sumatoria += G.shortestPath(D);
        G.clearD(G, D);
    }

    long double factorialSup = factorial(V);
    long double factorialInf = factorial(V-2);
    long double Combinatoria= factorialSup/(factorialInf*2);

    return (sumatoria/Combinatoria);
}

/*****
* long double weightedshortestPath
******
* Devuelve el largo del camino más corto que SI 
* toma en cuenta el peso del arco
******
* Input:
* int *D : Puntero a arreglo de distancias de un vertice
******
* Returns:
* long double Retornar el valor total de camino más corto con pesos considerados
*****/
long double tGrafo::weightedshortestPath(int *D){
    double total = 0;
    
    for(int i = 0; i < V ; i++){

        if(D[i] != 0){
            total+= D[i];
        }        
    }

    return total;
}

/*****
* long double sumatoriaPesos
******
* Retorna la suma de todos los pesos de la matriz
******
* Input:
* No requiere input
******
* Returns:
* long double Retorna el valor total de la suma de los pesos del grafo
*****/
long double tGrafo::sumatoriaPesos(){
    long double total = 0;
    for(int i = 0; i < V ; i++){
        for(int j = 0; j < V; j++){
            total+= MatrizADJ[i][j];
        }
    }

    return total/2;
}


/*****
* long double averageWightedDistance
******
* Devuelve la longitud de camino promedio del grafo 
* dada por la distancia promedio considerando pesos
******
* Input:
* tGrafo& G : Grafo el cual se itera en la funcion
* int *D : Puntero a arreglo de distancias de un vértice
******
* Returns:
* long double Retorna el resultado de la operacion de una sumatoria divido sumatoria de Pesos para calcular distancia promedio
*****/
long double tGrafo::averageWeightedDistance(tGrafo& G, int *D){
    long double sumatoria = 0;
    

    for(tVertice i = 0; i < V; i++){
        D[i] = 0;
        G.Dijkstra(G, D, i);
        sumatoria += G.weightedshortestPath(D);
        G.clearD(G, D);
    }

    long double sumatoriaPesosMatriz = sumatoriaPesos();
    
    return(sumatoria/sumatoriaPesosMatriz);
}