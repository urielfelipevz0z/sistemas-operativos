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
    ventana = initscr();        //inicializa la ventana
    if(ventana == NULL){
        return 1;
    }

    keypad(ventana, TRUE);
    while (1){
        clear();
        mvprintw(0, 0, ">> ");      //imprime en un lugar en especifico
        
        if (kbhito()) {
            leerComando(comando);   // solo llamas si hay entrada
        }
        refresh();                  //actualiza la pantalla
        usleep(tiempo * 5);                 //utilizada para hacer pausas
    } 
}