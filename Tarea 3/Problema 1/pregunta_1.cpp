#include <iostream>
#include <string>

#define M 128
#define VACIA ""

using namespace std;

typedef int tElemLista;
typedef string tipoClave;
typedef string tipoInfo;

//------------------------------------------------------------------------------------------------------------------------------------

struct tNodo{
    tElemLista terPos;
    tElemLista consultas;
    tNodo* sig;
};

struct ranura {
    tipoClave termino;
    tipoInfo significado;
    int consultas;
};

struct tQE {
    int total;
    int conocidos;
    int desconocidos;
};

struct tPS {
    int accesses;
    int hits;
    int misses;
    int cleanups;
};

//------------------------------------------------------------------------------------------------------------------------------------

class Lista{
    private:
        tNodo *head;
        tNodo *curr;
        tNodo *tail;
        int largo;
        int pos;
    public:
        Lista(){
            head = NULL;
            curr = NULL;
            tail = NULL;
            largo = 0;
            pos = 0;
        };
        int length();
        void moveToStart();
        void next();
        void prev();
        void insert(tElemLista terPos, tElemLista cons);
        void addNext(tElemLista terPos, tElemLista cons);
        int getValueCons();
        int getValuePos();
};

class CacheDiccionario {
private:
    ranura ran[M];
    tQE QE;
    tPS PS;
public:
    CacheDiccionario(){
        int i;
        for(i=0;i<M;i++){
            ran[i].termino = VACIA;
            ran[i].significado = VACIA;
            ran[i].consultas = 0;
            QE.total = 0;
            QE.conocidos = 0;
            QE.desconocidos = 0;
            PS.accesses = 0;
            PS.cleanups = 0;
            PS.hits = 0;
            PS.misses = 0;
        }
    }
    void cleanup();
    bool query(string termino, string& significado);
    void insert(string termino, string significado);
    void querystats(int& total, int& conocidos, int& desconocidos);
    void perfstats(int& accesses, int& hits, int& misses, int& cleanups);
};

//------------------------------------------------------------------------------------------------------------------------------------

/**
 * @brief Función auxiliar a la función hashing, que permite el reposicionamiento de un término, en caso de que la ranura que le correspondía originalmente esté ocupada. Corresponde a un Hashing Cerrado Cuadrático
 * 
 * @param k término a reposicionar
 * @param i iteraciones
 * @return int Valor que, en conjunto con el valor original de hashing, entrega una nueva posición para el término.
 */
int p(tipoClave k, int i){
    if (i == 0) return 0;
    return 3*i*i + 7*i + 29;
}

/**
 * @brief Función que permite entregar un espacio a un término dentro de la tabla de hash. Por cada término, consigue su valor ASCII y lo multiplica por su posición en el término. A este valor se le aplica el módulo del la cantidad de ranura de la tabla de hash.
 * 
 * @param termino término aposicionar
 * @return int Valor que entrega la posición para el término dentro de la tabla de hash.
 */
int h(tipoClave termino) {
    int cont;
    int value = 0;
    int largo = termino.length();
    for(cont = 0; cont < largo; cont++){
        if(termino==""){
            return value;  
        }
        value = (((int(termino[cont]))*(cont+1))%M);
    }
    return value;
}

//------------------------------------------------------------------------------------------------------------------------------------

/**
 * @brief Entrega el largo de la lista
 * 
 * @return int Largo de la lista.
 */
int Lista::length(){
    return largo;
};

/**
 * @brief Se "mueve" al inicio de la lista.
 * 
 */
void Lista::moveToStart(){
    curr = head;
    pos = 0;
};

/**
 * @brief Se "mueve" al nodo siguiente al que estamos ubicados
 * 
 */
void Lista::next(){
    if(curr->sig != NULL){
        curr = curr->sig;
        pos++;
    }
};

/**
 * @brief Se "mueve" al nodo anterior al que estamos ubicados
 * 
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

/**
 * @brief Inserta un nodo dentro de una lista.
 * 
 * @param terPos Posición de un término
 * @param cons Cantidad de consultas de un término
 */
void Lista::insert(tElemLista terPos, tElemLista cons){
    if(largo == 0){
        tNodo * nuevo = new tNodo;
        nuevo->terPos = terPos;
        nuevo->consultas = cons;
        head = nuevo;
        curr = nuevo;
        tail = nuevo;
        nuevo->sig = NULL;
        largo++;
        pos = 0;
    }else{
        if(pos == 0){
            tNodo* nuevo = new tNodo;
            nuevo->terPos = terPos;
            nuevo->consultas = cons;
            nuevo->sig = head;
            curr = head;
            head = nuevo;
            largo++;
            pos++;
        }else{
            tNodo * nuevo = new tNodo;
            nuevo->terPos = terPos;
            nuevo->consultas = cons;
            nuevo->sig = curr;
            prev();
            curr->sig = nuevo;
            next();
            largo++;
        }
    }
};

/**
 * @brief Añade un nodo contiguamente al nodo que se está analizando.
 * 
 * @param terPos Posición de un término
 * @param cons Cantidad de consultas de un término
 */
void Lista::addNext(tElemLista terPos, tElemLista cons){
    tNodo* nuevo = new tNodo;
    nuevo->terPos = terPos;
    nuevo->consultas = cons;
    curr->sig = nuevo;
    curr = nuevo;
    largo++;
    pos++;
}

/**
 * @brief Entrega el la cantidad de consultas de un término.
 * 
 * @return int 
 */
int Lista::getValueCons(){
    return curr->consultas;
};

/**
 * @brief Entrega el valor de la posición de un término en la tabla de hash.
 * 
 * @return int posición de un término
 */
int Lista::getValuePos(){
    return curr->terPos;
};

//------------------------------------------------------------------------------------------------------------------------------------

/**
 * @brief Función auxiliar que vacía la mitad de la tabla de hash, al ésta alcanzar su máxima capacidad. Ocupala ayuda del método de lista enlazada.
 * 
 */
void CacheDiccionario::cleanup(){
    int i;
    Lista list = Lista();
    for(i = 0; i < M ; i++){
        tElemLista terPos = i;
        tElemLista NroCons = ran[i].consultas;
        list.moveToStart();
        if (i==0){
            list.insert(terPos,NroCons);
        }
        if (i==1){
            if (list.getValueCons() <= NroCons){
                list.addNext(terPos,NroCons);
            }
            else{
                list.insert(terPos,NroCons);
            }
        }
        else{
            if (list.getValueCons() <= NroCons){
                int cont;
                for(cont = 1;list.getValueCons() <= NroCons && cont <= list.length(); cont++){
                    list.next();
                }
                if(cont == list.length()){
                    list.addNext(terPos,NroCons);
                }
                else{
                    list.insert(terPos,NroCons);
                }
            }
            else{
                list.insert(terPos,NroCons);
            }
        }
        PS.accesses++;
    }
    list.moveToStart();
    for(i=0;i<(M/2);i++){
        ran[list.getValuePos()].termino = VACIA;
        ran[list.getValuePos()].significado = VACIA;
        ran[list.getValuePos()].consultas = 0;
        PS.accesses++;
        list.next();
    }
    PS.cleanups++;
    }

/**
 * @brief Permite consultar por una definición, buscando su termino. De encontrarse, la operación retorna verdadero y entrega el significado asociado al término en el parámetro por referencia significado. En cualquier otro caso, retorna falso y un string vacío en el parámetro por referencia significado.
 * 
 * @param termino término que se busca en la tabla de hash.
 * @param significado referencia a la definición del término.
 * @return true Si es que el término fue encontrado
 * @return false Si es que el término no fue encontrado
 */
bool CacheDiccionario::query(string termino, string& significado){
    QE.total++;
    int pos = h(termino);
    if (ran[pos].termino == termino){
        if (ran[pos].significado == ""){
            QE.desconocidos++;
        }
        else{
            QE.conocidos++;
        }
        significado = ran[pos].significado;
        PS.hits++;
        PS.accesses++;
        return true; // registro encontrado, búsqueda exitosa
    }
    int i;
    for (i = 1; (ran[pos].termino != VACIA || ran[pos].termino != termino) && i <= M; i++){
        PS.accesses++;
        if (ran[pos].termino == termino){
            if (ran[pos].significado == ""){
                QE.desconocidos++;
            }
            else{
                QE.conocidos++;
            }
            significado = ran[pos].significado;
            PS.hits++;
            return true; // registro encontrado, búsqueda exitosa
        }
        pos = (h(termino) + p(termino, i)) % M; // próxima ranura en la secuencia
    }
    QE.desconocidos++;
    PS.misses++;
    return false; //No encontré nah
}

/**
 * @brief Permite insertar una nueva definición, recibiendo como parámetros su termino y significado. Al alcanzarse la máxima capacidad del almacenamiento interno se realizará una limpieza, llamando a la función cleanup(). Esta función elimina la mitad de los elementos con menor cantidad de consultas. Posterior a la limpieza, queda almacenada la definición que se pretendía insertar. En caso de insertarse un término repetido, se reemplaza el significado anterior, manteniendo la cantidad de consultas realizadas previamente.
 * 
 * @param termino término a insertar en el hash.
 * @param significado definición del término a insertar.
 */
void CacheDiccionario::insert(string termino, string significado){
    int inicio, i;
    int pos = inicio = h(termino);
    PS.accesses++;
    for (i = 1; ran[pos].termino != VACIA && ran[pos].termino != termino && i <= M; i++){
        PS.accesses++;
        pos = (inicio + p(termino, i)) % M;
    }
    if (i == M+1){
            cleanup();
            i = 0;
            insert(termino,significado);
    }
    if (ran[pos].termino == VACIA){
        PS.accesses++;
        ran[pos].termino = termino;
        ran[pos].significado = significado;
    }
    else if (ran[pos].termino == termino){
        PS.accesses++;
        ran[pos].significado = significado;
    }
}

/**
 * @brief Entrega estadísticas de las consultas realizadas sobre el TDA desde su creación, entregando los siguien-
tes valores en los parámetros por referencia
 * 
 * @param total cantidad total de consultas realizadas.
 * @param conocidos cantidad total de consultas realizadas a términos con significado no vacío.
 * @param desconocidos cantidad total de consultas realizadas a términos con significado vacío.
 */
void CacheDiccionario::querystats(int& total, int& conocidos, int& desconocidos){
    total = QE.total;
    conocidos = QE.conocidos;
    desconocidos = QE.desconocidos;
}

/**
 * @brief Entrega estadísticas de rendimiento del TDA CacheDiccionario desde su creación, entregando los siguientes valores en
los parámetros por referencia.
 * 
 * @param accesses la cantidad de accesos realizadas a todas las ranuras de la tabla de hashing base del
TDA.
 * @param hits la cantidad de veces que se encontró un término consultado.
 * @param misses la cantidad de veces que no se encontró un término consultado.
 * @param cleanups la cantidad de veces que se realizó una limpieza.
 */
void CacheDiccionario::perfstats(int& accesses, int& hits, int& misses, int& cleanups){
    accesses = PS.accesses;
    hits = PS.hits;
    misses = PS.misses;
    cleanups = PS.cleanups;
}