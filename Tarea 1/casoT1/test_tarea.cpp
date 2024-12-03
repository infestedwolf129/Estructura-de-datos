#include <iostream>
#include <fstream>
#include <cstring>

struct tipoServicio{
    std::string nameServicio;
    int limitDiario;
    int limitMensual;
    int hrInicio;
    int minInicio;
    int hrFin;
    int minFin;
};
struct Ticket{
    char rut_funcionario[10];
    int day_of_month;
    char time[6];
};

struct TicketComparar{
    std::string rut_funcionario;
    int horaticket;
    int minticket;
    int dia;
};

struct RutUnico{
    std::string rut_unico;
    int ticketEmitidos;
    int ticketValidos;
    bool condicionHoras;
    int CantUsosDia;
    int CantUsosMes;
    int CantUsosTotal;
};


/*****
 * bool ValidationTime
*****
 * Analiza si el ticket está dentro de tiempo (por ende, si es válido)
*****
 * Input:

 * int hhi    : Entero que representa la hora de inicio de un servicio.
 * int mmi    : Entero que representa el minuto de inicio de un servicio.
 * int hhf    : Entero que representa la hora de fin de un servicio.
 * int mmf    : Entero que representa el minuto de fin de un servicio.
 * int hhx    : Entero que representa la hora de inicio de un ticket.
 * int mmx    : Entero que representa el minuto de inicio de un ticket.
 
*****
 * REALIZADO POR FRANCISCA SALINAS
*****/
bool ValidationTime(int hhi,int mmi,int hhf,int mmf,int hhx,int mmx){
    if(hhf<hhi){
        hhf = (24+hhf);
        if(hhx<12){
            hhx = (24+hhx);
        }
    };
    if(hhi<=hhx && hhx<=hhf){
        if((hhi == hhx && mmi<= mmx)||(hhf == hhx && mmx<=mmf)||(hhi < hhx && hhx<hhi)){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
};
    
/*****
 * tipoServicio* recogerDatosServicios
*****
 * Procedimiento que lee un archivo de texto que se llama "servicios.txt" y recolecta informacion sobre los servicios a realizar en la empresa almacenandolos en un arreglo de struct.
*****
 * Input:
 * int &cantServicios    : Puntero a dirección de memoria de un entero creado en la funcion int main() que almacena la cantidad de servicios que se realizan.
*****
 * REALIZADO POR THOMAS RODRIGUEZ
*****/
tipoServicio* recogerDatosServicios(int &cantServicios){
    std::ifstream servicios;
    servicios.open("servicios.txt",std::ios::in);
    servicios >> cantServicios;

    tipoServicio* arregloServicios = new tipoServicio[cantServicios];
    int contador = 0;
    std::string horaInicio, horaFin;
    while(!servicios.eof()){
        servicios >> arregloServicios[contador].nameServicio;
        servicios >> arregloServicios[contador].limitDiario;
        servicios >> arregloServicios[contador].limitMensual;
        servicios >> horaInicio;
        servicios >> horaFin;
        std::string temp1 = horaInicio.substr(0,2);
        std::string temp2 = horaInicio.substr(3,6);
        std::string temp3 = horaFin.substr(0,2);
        std::string temp4 = horaFin.substr(3,6);
        int hrInicio = stoi(temp1);
        int minInicio = stoi(temp2);
        int hrFin = stoi(temp3);
        int minFin = stoi(temp4);
        arregloServicios[contador].hrInicio = hrInicio;
        arregloServicios[contador].minInicio = minInicio;
        arregloServicios[contador].hrFin = hrFin;
        arregloServicios[contador].minFin = minFin;
        contador++;
    }
    
    servicios.close();
    return arregloServicios;
};

/*****
 * Ticket* recogerDatosTicket
*****
 * Procedimiento que lee un archivo binario llamado "ticket.dat" y recolecta la informacion de todos los tickets emitidos durante el mes, agrupando ademas en un arreglo de struct el registro de tickets emitidos(rut,cantidad,hora de emision respectivamente).
*****
 * Input:
 * int &cantTicket    : Puntero a dirección de memoria de un entero creado en la funcion int main() que almacena la cantidad de tickets emitidos durante el mes.
*****
 * REALIZADO POR THOMAS RODRIGUEZ
*****/

Ticket* recogerDatosTicket(int &cantTicket){
    std::ifstream ticket;
    ticket.open("tickets.dat", std::ios::in|std::ios::binary);
    ticket.read((char*)&cantTicket,sizeof(int));
    Ticket* arregloTicket = new Ticket[cantTicket];
    int i = 0;
    while (!ticket.eof()){
        ticket.read((char*) arregloTicket[i].rut_funcionario,12*sizeof(char));
        ticket.read((char*) &arregloTicket[i].day_of_month,sizeof(int));
        ticket.read((char*) arregloTicket[i].time,8*sizeof(char));
        i++;
    };
    return arregloTicket;
};

int main(){
    int cantServicios, cantTicket;
    
    /*Extractor de informacion de servicios.txt THOMAS RODRIGUEZ*/
    tipoServicio* datosServicios = recogerDatosServicios(cantServicios);

    /*Extractor de informacion de tickets.dat THOMAS RODRIGUEZ*/
    Ticket* datosTicket= recogerDatosTicket(cantTicket);
    
    /*Transformamos los RUT a enteros THOMAS RODRIGUEZ*/
    std::string RUT;
    int rutN;
    int arregloRUT[cantTicket];
    TicketComparar* arregloTicket= new TicketComparar[cantTicket];
    for (int i = 0; i < cantTicket; i++){
        RUT = std::string (datosTicket[i].rut_funcionario);
        std::string temp= RUT.substr(0,8);
        rutN = std::stoi(temp);
        arregloRUT[i] = rutN; 
        arregloTicket[i].rut_funcionario = RUT;  
    };

    /*Transformamos la hora del ticket en entero para poder comparar y almacenamos en un Struct con su usuario correspondiente THOMAS RODRIGUEZ*/
    std::string horaTicket;
    int hrticket,minticket;
    for (int i=0;i< cantTicket;i++){
        horaTicket = std::string (datosTicket[i].time);
        std:: string temp1= horaTicket.substr(0,2);
        std:: string temp2 = horaTicket.substr(3,6);
        hrticket = std::stof(temp1);
        minticket = std::stof(temp2);
        arregloTicket[i].horaticket = hrticket;
        arregloTicket[i].minticket = minticket;
        arregloTicket[i].dia = datosTicket[i].day_of_month;
        
    };
        

    /*Ordenar datos del struct Ticket y arreglo de RUT THOMAS RODRIGUEZ*/
    for(int i=0;i<cantTicket;i++){
        int pos=i;
        int aux = arregloRUT[i];

        while((pos>0)&&(arregloRUT[pos-1]>aux)){
            arregloRUT[pos]=arregloRUT[pos-1];
            std::swap(datosTicket[pos],datosTicket[pos-1]);
            std::swap(arregloTicket[pos],arregloTicket[pos-1]);
            pos--;
        };
        arregloRUT[pos]=aux;
    };

    /*Obtener cantidad de ruts únicos sin repetición THOMAS RODRIGUEZ*/
    int unicos=0;
    for(int i=0; i<cantTicket;i++){
        if(arregloRUT[i] != arregloRUT[i-1]){
            unicos++;
        }
    };

    /*Creacion de arreglo que almacena cada RUT una unica vez VICENTE DIAZ*/
    RutUnico* arregloUnico = new RutUnico[unicos];
    int cont = 0;
    for(int j=0; j<cantTicket; j++){
        std::string rut1 = datosTicket[j].rut_funcionario;
        std::string rut2 = datosTicket[j-1].rut_funcionario;
        if(rut1 != rut2){
            
            arregloUnico[cont].rut_unico = rut1;
            cont++;
            
        }
            
    };

    /* Contamos cantidad de tickets emitidos por RUT THOMAS RODRIGUEZ*/
    for(int i=0;i<unicos;i++){
        int ticketTotalEmitidos = 0;
        for(int j=0;j<cantTicket;j++){
            if(datosTicket[j].rut_funcionario == arregloUnico[i].rut_unico)
                ticketTotalEmitidos++;
        }
        arregloUnico[i].ticketEmitidos = ticketTotalEmitidos;
    }
    


    /* Extrae las horas y minutos de cada ticket para luego ser analizadas por Validation() FRANCISCA SALINAS*/

    for (int i = 0;i < cantServicios; i++){
        int hhi = datosServicios[i].hrInicio; 
        int mmi = datosServicios[i].minInicio;
        int hhf = datosServicios[i].hrFin;
        int mmf = datosServicios[i].minFin;
        int DayLimServ = datosServicios[i].limitDiario;
        int MonLimServ = datosServicios[i].limitMensual;
        for (int j = 0; j < cantTicket; j++){
            std::string RUTx = arregloTicket[j].rut_funcionario;
            int hhx = arregloTicket[j].horaticket;
            int mmx = arregloTicket[j].minticket;

            if(ValidationTime(hhi,mmi,hhf,mmf,hhx,mmx)){
                for(int k=0;k<unicos;k++){
                    if(arregloUnico[k].rut_unico == RUTx){
                        if (arregloUnico[k].CantUsosDia<DayLimServ){
                            arregloUnico[k].CantUsosDia++;
                            if(arregloUnico[k].CantUsosMes<= MonLimServ){
                                arregloUnico[k].CantUsosMes++;
                                if(arregloUnico[k].CantUsosTotal<100){
                                    arregloUnico[k].ticketValidos++;
                                }
                            }
                        }
                    }
                arregloUnico[k].CantUsosTotal++;
                }
            }
        }
    }


    /* Realizamos escritura de archivo txt con los datos de salida correspondientes THOMAS RODRIGUEZ*/
    std::ofstream salida;
    salida.open("salida_test.txt");
    for (int i=0;i<unicos;i++){
        salida << arregloUnico[i].rut_unico << " " << arregloUnico[i].ticketEmitidos-arregloUnico[i].ticketValidos << "/" << arregloUnico[i].ticketEmitidos <<"\n";
    };
    

    delete[] arregloTicket;
    delete[] datosTicket;
    delete[] datosServicios;
    return 0;
};

