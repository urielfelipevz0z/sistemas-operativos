/**
 * @file principal.c
 * @brief Programa principal del simulador de sistema operativo
 * @author Equipo: Los sistématicos
 * @date 2025
 * gcc -I. principal.c src/alu.c src/imprimir.c src/interprete.c src/comando.c src/globales.c src/controlador_procesos.c src/instrucciones.c src/leer_archivo.c src/validar.c src/kbhit.c -lncurses -o sistematicos
 * ./sistematicos
 * gcc -I. principal.c src/*.c -lncurses -o sistematicos
 *  ejecuta a.asm b.asm a.asm b.asm si.asm b.asm a.asm b.asm a.asm si.asm a.asm b.asm a.asm b.asm si.asm
 *  ejecuta a.asm c.asm b.asm si.asm a.asm si.asm b.asm b.asm a.asm si.asm 
 *  ejecuta a.asm c.asm b.asm no.asm a.asm no.asm b.asm b.asm a.asm no.asm 
 *  ejecuta a.asm c.asm b.asm a.asm a.asm c.asm b.asm a.asm
 *  ejecuta si.asm b.asm b.asm a.asm si.asm
 *  ejecuta no.asm c.asm si.asm no.asm no.asm no.asm si.asm si.asm no.asm no.asm
 * 
 * 
 * 
 */

#include "include/controlador.h"

int main(){

    initscr();//inicializa pantalla de ncurses
    curs_set(0);//oculta el cursor de la terminal

    ventana = malloc(sizeof(Ventana));
    inicializarVentanas(ventana);
    imprimirVentanas(ventana);
    while (1){
        // if (kbhito()) {
        //     leerComando(comando);   // solo llamas si hay entrada
        // }
        quantum();       
    }
    if(ventana != NULL){
        free(ventana);
        ventana = NULL;
    }
    endwin(); 
}