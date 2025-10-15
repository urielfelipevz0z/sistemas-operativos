/**
 * @file principal.c
 * @brief Programa principal del simulador de sistema operativo
 * @author Equipo: Los sistématicos
 * @date 2025
 * gcc -I. principal.c src/alu.c src/imprimir.c src/interprete.c src/comando.c src/globales.c src/controlador_procesos.c src/instrucciones.c src/leer_archivo.c src/validar.c src/kbhit.c -lncurses -o sistematicos
 * ./sistematicos
 *  ejecuta a.asm b.asm a.asm b.asm si.asm b.asm a.asm b.asm a.asm si.asm a.asm b.asm a.asm b.asm si.asm
 */

#include "include/controlador.h"
void simon();

int main(){

    initscr();//inicializa pantalla de ncurses
    curs_set(0);//oculta el cursor de la terminal

    ventana = malloc(sizeof(Ventana));
    inicializarVentanas(ventana);
    imprimirVentanas(ventana);

    while (1){
        if (kbhito()) {
            leerComando(comando);   // solo llamas si hay entrada
        }
        simon();   
    }
    if(ventana != NULL){
        free(ventana);
        ventana = NULL;
    }
    endwin(); 
}

void simon(){
    if(arreglo_de_listas[0] != NULL){
        recorrerListas(&(arreglo_de_listas[0]));
        //imprimir lista de listos
        // while (arreglo_de_listas[0] != NULL){ 
        
        if(arreglo_de_listas[1] == NULL){
            aux = arreglo_de_listas[0]; 
            arreglo_de_listas[0] = aux->siguiente;
            aux->siguiente = NULL;
            insertar(&(arreglo_de_listas[1]), aux); //Se mueve el 1er nodo de listos a ejecución 
            recorrerListas(&(arreglo_de_listas[0]));
            strcpy(reg_proceso, aux[0].nombre); 
            if (leerArchivo(&aux[0]) == -1){ //a.asm 
                reg_id--; 
                strcpy(reg_proceso, ""); 
            } 
        }
        else{
            if(ejecutarInstruccion(arreglo_de_listas[1]->archivo)){
                igualarRegistros(&aux[0]); 
                arreglo_de_listas[1] = NULL;
                insertar(&(arreglo_de_listas[2]), aux);   //Se mueve el nodo de ejecución a terminados 
                recorrerListas(&(arreglo_de_listas[0]));
            }
        }      
    }
    if(arreglo_de_listas[1] != NULL){
        if(ejecutarInstruccion(arreglo_de_listas[1]->archivo)){
                igualarRegistros(&aux[0]); 
                arreglo_de_listas[1] = NULL;
                insertar(&(arreglo_de_listas[2]), aux);   //Se mueve el nodo de ejecución a terminados 
                recorrerListas(&(arreglo_de_listas[0]));
        }
    }
}





