#include "include/controlador.h"

void inicializarVentanas(Ventana *ventana){

    ventana->ventana[0] = newwin(3,100,0,0);    //Promt
    ventana->ventana[1] = newwin(3,100,3,0);    //Mensajes de error
    ventana->ventana[2] = newwin(7,100,6,0);    //Lista de Ejecucion
    ventana->ventana[3] = newwin(12,100,13,0);   //Lista de Listos
    ventana->ventana[4] = newwin(12,100,25,0);   //Lista de Terminados
    ventana->update[0] = 1;
    ventana->update[1] = 1;
    ventana->update[2] = 1;
    ventana->update[3] = 1;
    ventana->update[4] = 1;
}

void imprimirVentanas(Ventana *ventana){

    ventanaPromt(ventana);
    ventanaMensaje(ventana);
    ventanaEjecucion(ventana);
    ventanaListos(ventana);
    ventanaTerminados(ventana);
}

void ventanaPromt(Ventana *ventana){
    werase(ventana->ventana[0]);                    //Borrar todo el contenido de la ventana
    box(ventana->ventana[0], 0, 0);                 //Dibujar nuevamente el borde de la ventana
    mvwprintw(ventana->ventana[0], 1, 1, ">> ");    //Imprimir prompt 
    wmove(ventana->ventana[0], 1, 4);
    wrefresh(ventana->ventana[0]);
}

void ventanaMensaje(Ventana *ventana){
    werase(ventana->ventana[1]);
    mvwprintw(ventana->ventana[1], 1, 1, "Mensaje: ");
    box(ventana->ventana[1],0,0);    
    ventana->update[1] = 0;                         //ponemos el estado en ya actualizado
    wrefresh(ventana->ventana[1]);                  //Refresca la ventana para mostrar el borde
}

void ventanaEjecucion(Ventana *ventana){
    werase(ventana->ventana[2]);
    mvwprintw(ventana->ventana[2], 1, 1, "-----  EJECUCION  -----");
    box(ventana->ventana[2],0,0);
    ventana->update[2] = 0;                         //ponemos el estado en ya actualizado
    wrefresh(ventana->ventana[2]);
}

void ventanaListos(Ventana *ventana){
    werase(ventana->ventana[3]);                    //Borrar todo el contenido de la ventana
    mvwprintw(ventana->ventana[3], 1, 1, "-----  LISTOS  -----");
    box(ventana->ventana[3], 0, 0);                 //Dibujar nuevamente el borde de la ventana
    ventana->update[3] = 0;                         
    wrefresh(ventana->ventana[3]);
}

void ventanaTerminados(Ventana *ventana){
    werase(ventana->ventana[4]);                    //Borrar todo el contenido de la ventana
    mvwprintw(ventana->ventana[4], 1, 1, "-----  TERMINADOS  -----");
    box(ventana->ventana[4], 0, 0);                 //Dibujar nuevamente el borde de la ventana
    ventana->update[4] = 0;                         
    wrefresh(ventana->ventana[4]);
}


void actualizaVentanas(Ventana *ventana, buffer *bufferC){
    if(ventana->update[0]){
        //printbuffer(ventana, bufferC);
    }
}