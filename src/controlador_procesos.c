#include "include/controlador.h"

void gestorProcesos(char *argumento, PCB *arreglo_de_listas[]){
    char arg_copia[256];
    strcpy(arg_copia,argumento);  //a.asm b.asm
    
    char *proceso = strtok(arg_copia, " ");

    while(proceso != NULL){
        //Falta comprobar el asm;
        insertar(proceso, arreglo_de_listas);       //Se guardan todos los nodos en lista_listos
        proceso = strtok(NULL, " ");
    }
    manejador(arreglo_de_listas);
}

PCB *crear(char *proceso){
    PCB *nuevo = (PCB *)malloc(sizeof(PCB));
    if(nuevo == NULL){
        imprimirError("No se ha poodido crear el proceso\n");
    }
    else{
        nuevo->id = 0;
        nuevo->pc = 1;
        nuevo->ax = 0;
        nuevo->bx = 0;
        nuevo->cx = 0;
        nuevo->dx = 0;

        strcpy(nuevo->ir, "");
        strcpy(nuevo->estado, "");
        strcpy(nuevo->nombre, proceso);
                
        nuevo->archivo = fopen(proceso, "r");;
        nuevo->siguiente = NULL;
    }
    return nuevo;
}

void insertar(char *proceso, PCB *arreglo_de_listas[]){
    PCB *nuevo;
    PCB *aux;
    nuevo = crear(proceso);
    if(arreglo_de_listas[0] == NULL){
       arreglo_de_listas[0] = nuevo;
    }
    else{
        aux = arreglo_de_listas[0];
        while(aux->siguiente != NULL){ //Recorre la lista hasta el final 
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
    }
}

void manejador(PCB *arreglo_de_listas[]){ 
    PCB *aux; 
    while (arreglo_de_listas[0] != NULL){ 
        aux = arreglo_de_listas[0]; 
        arreglo_de_listas[0] = aux->siguiente;
        aux->siguiente = NULL;
        //arreglo_de_listas[1] = NULL;
        insertar(aux[0].nombre, &(arreglo_de_listas[1])); //Se mueve el 1er nodo de listos a ejecución 
        strcpy(reg_proceso, aux[0].nombre); 
        if (leerArchivo(&aux[0]) == -1){ //a.asm 
            reg_id--; strcpy(reg_proceso, ""); 
        } 
        igualarRegistros(&aux[0]); 
        imprimirEncabezado(); 
        imprimirFilaPr(&aux[0]); 
        aux = arreglo_de_listas[1]; 
        insertar(aux[0].nombre, &(arreglo_de_listas[2]));   //Se mueve el nodo de ejecución a terminados 
    }     
}


void eliminar(PCB *arreglo_de_listas[]){
    PCB *aux;
    PCB *lista = arreglo_de_listas[0];
    
    if(lista == NULL){
        imprimirError("No hay procesos en la lista\n");
    }
    else{
        while(lista != NULL){
            aux = lista;
            lista = lista->siguiente;
            free(aux);
        }
        arreglo_de_listas[0] = NULL;
    }
}

// void recorrer(PCB *lista){
//     while(lista != NULL){

//     }
// }