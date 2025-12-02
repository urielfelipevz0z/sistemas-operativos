#include "include/controlador.h"
PCB *proceso;

//Imprimir el cuadro de mensajes de errores
void imprimirError(char *mensaje){
    werase(ventana->ventana[1]);
    box(ventana->ventana[1], 0, 0);
    mvwprintw(ventana->ventana[1], 1, 1, "%s", mensaje);
    wrefresh(ventana->ventana[1]);
    wmove(ventana->ventana[0], 1, 4);
    wrefresh(ventana->ventana[0]);
}

void imprimirDebug(char *mensaje){
    werase(ventana->ventana[9]);
    box(ventana->ventana[9], 0, 0);
    mvwprintw(ventana->ventana[9], 1, 1, "[DEBUG] %s", mensaje);
    wrefresh(ventana->ventana[9]);
}

void imprimirRecursos(char *mensaje){
    werase(ventana->ventana[8]);
    box(ventana->ventana[8], 0, 0);
    mvwprintw(ventana->ventana[8], 1, 1, "%s", mensaje);
    wrefresh(ventana->ventana[8]);
    wmove(ventana->ventana[8], 1, 4);
    wrefresh(ventana->ventana[8]);
}

void imprimirQuantum(char *mensaje){
    werase(ventana->ventana[6]);
    box(ventana->ventana[6], 0, 0);
    mvwprintw(ventana->ventana[6], 1, 1, "[QUANTUM]: %s", mensaje);
    wrefresh(ventana->ventana[6]);
}

void imprimirEncabezadoEjecucion(void){
    werase(ventana->ventana[2]);
    box(ventana->ventana[2], 0, 0);
    mvwprintw(ventana->ventana[2], 1, 1, "-----  EJECUCION  -----");
    mvwprintw(ventana->ventana[2],2,1,"%-5s %-5s %-5s %-5s %-5s %-5s %-5s %-5s %-5s %-10s %-10s %s",
           "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Rx", "Ry", "Rz", "Proceso", "IR", "Status");
    mvwprintw(ventana->ventana[2],3,1,"----------------------------------------------------------------------------------");
    wrefresh(ventana->ventana[2]);
}

void  imprimirFila(void){
    mvwprintw(ventana->ventana[2],4,1,"%-5d %-5d %-5d %-5d %-5d %-5d %-5d %-5d %-5d %-10s %-10s %s",
           reg_id, reg_pc, reg_ax, reg_bx, reg_cx, reg_dx, arreglo_de_listas[1]->RAsig[0], arreglo_de_listas[1]->RAsig[1], arreglo_de_listas[1]->RAsig[2],
           reg_proceso, reg_ir, "Correcto");
    wrefresh(ventana->ventana[2]);
    usleep(tiempo);
}

void imprimirFilaConError(char *mensaje_error){
    mvwprintw(ventana->ventana[2],4,1,"%-5d %-5d %-5d %-5d %-5d %-5d %-5d %-5d %-5d %-10s %-10s %s",
           reg_id, reg_pc, reg_ax, reg_bx, reg_cx, reg_dx, arreglo_de_listas[1]->RAsig[0], arreglo_de_listas[1]->RAsig[1], arreglo_de_listas[1]->RAsig[2],
           reg_proceso, reg_ir, mensaje_error);
    wrefresh(ventana->ventana[2]);
    usleep(tiempo);
}

void imprimirTabla(void){
    imprimirEncabezadoEjecucion();
    imprimirFila();
}

void inicializarVentanas(Ventana *ventana){

    ventana->ventana[0] = newwin(3,110,0,5);      //Promt
    ventana->ventana[1] = newwin(3,92,3,68);      //Mensajes de error
    ventana->ventana[2] = newwin(7,92,14,68);     //Lista de Ejecucion (7 filas)
    ventana->ventana[3] = newwin(8,92,6,68);      //Lista de Listos (8 filas = 4 procesos)
    ventana->ventana[4] = newwin(16,92,21,68);    //Lista de Terminados (16 filas = 12 procesos)
    ventana->ventana[5] = newwin(15,68,6,0);      //Lista de Nuevos (15 filas = 11 procesos)
    ventana->ventana[6] = newwin(3,68,3,0);       //Mensajes quantum
    ventana->ventana[7] = newwin(16,68,21,0);     //Lista de Bloqueados (16 filas = 12 procesos)
    ventana->ventana[8] = newwin(3,30,0,120);     //Recursos globales
    ventana->ventana[9] = newwin(3,160,37,0);
    ventana->update[0] = 1;
    ventana->update[1] = 1;
    ventana->update[2] = 1;
    ventana->update[3] = 1;
    ventana->update[4] = 1;
    ventana->update[5] = 1;
    ventana->update[6] = 1;
    ventana->update[7] = 1;
    ventana->update[8] = 1;
    ventana->update[9] = 1;
}

void imprimirVentanas(Ventana *ventana){
    ventanaPromt(ventana);
    ventanaMensaje(ventana);
    ventanaEjecucion(ventana);
    ventanaListos(ventana);
    ventanaTerminados(ventana);
    ventanaNuevos(ventana);
    ventanaQuantum(ventana);
    ventanaBloqueados(ventana);
    ventanaRecursos(ventana);
    ventanaDebug(ventana);
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

void ventanaDebug(Ventana *ventana){
    werase(ventana->ventana[9]);
    mvwprintw(ventana->ventana[9], 1, 1, "Debug: ");
    box(ventana->ventana[9],0,0);    
    ventana->update[9] = 0;                         //ponemos el estado en ya actualizado
    wrefresh(ventana->ventana[9]);                  //Refresca la ventana para mostrar el borde
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

void ventanaNuevos(Ventana *ventana){
    werase(ventana->ventana[5]);                    //Borrar todo el contenido de la ventana
    mvwprintw(ventana->ventana[5], 1, 1, "-----  NUEVOS  -----");
    box(ventana->ventana[5], 0, 0);                 //Dibujar nuevamente el borde de la ventana
    ventana->update[5] = 0;                         
    wrefresh(ventana->ventana[5]);
}

void ventanaQuantum(Ventana *ventana){
    werase(ventana->ventana[6]);                    //Borrar todo el contenido de la ventana
    mvwprintw(ventana->ventana[6], 1, 1, "[QUANTUM]:");
    box(ventana->ventana[6], 0, 0);                 //Dibujar nuevamente el borde de la ventana
    ventana->update[6] = 0;                         
    wrefresh(ventana->ventana[6]);
}

void ventanaBloqueados(Ventana *ventana){
    werase(ventana->ventana[7]);
    mvwprintw(ventana->ventana[7], 1, 1, "----- BLOQUEADOS -----");
    box(ventana->ventana[7], 0, 0);
    ventana->update[7] = 0;
    wrefresh(ventana->ventana[7]);
}

void ventanaRecursos(Ventana *ventana){
    werase(ventana->ventana[8]);
    mvwprintw(ventana->ventana[8], 1, 1, "Recursos Globales:");
    box(ventana->ventana[8], 0, 0);
    wrefresh(ventana->ventana[8]);
}