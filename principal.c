/**
 * @file principal.c
 * @brief Programa principal del simulador de sistema operativo
 * @author Equipo: Los sistématicos
 * @date 2025
 * gcc -I. principal.c src/alu.c src/imprimir.c src/interprete.c src/comando.c src/globales.c src/manejador_archivos.c src/instrucciones.c src/validar.c -lncurses -o sistematicos
 */

#include "include/controlador.h"

int main(){
    ventana = initscr();
    if(ventana == NULL){
        return 1;
    }

    keypad(ventana, TRUE);
        
    while (1){
        clear();
        mvprintw(0, 0, ">> ");
        leerComando(comando);
        refresh();
        getch();
    }
    endwin();
}
