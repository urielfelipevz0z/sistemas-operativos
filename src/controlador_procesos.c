#include "include/controlador.h"

gestorProcesos(char *argumento, PCB *listos){
    char *proceso;
    
}
//    bufferC = (buffer *)malloc(sizeof(buffer));
crear(char *proceso){
    PCB *nuevo = (PCB *)malloc(sizeof(PCB));
    if(nuevo == NULL){
        imprimirError("No se ha poodido crear el proceso\n");
    }
    else{

    int id;
    int pc;
    int ax;
    int bx;
    int cx;
    int dx;
    char ir[16];
    char estado[10];    // Nuevo, Listo, Terminado(Bien o Mal), Bloqueado, Suspendido
    char nombre[30]; //nombre del archivo
    FILE *archivo; //puntero al archivo
    struct PCB *siguiente; //puntero al siguiente PCB

    }
}

insertar(char *proceso, PCB *lista){

}

manejador(PCB *listos){

}

eliminar(PCB *lista){
    
}

