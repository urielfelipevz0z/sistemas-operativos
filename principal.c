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
        
    }
    free(ventana);
    endwin(); 
}