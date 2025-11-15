#include "include/controlador.h"

//Imprimir el cuadro de mensajes de errores
void imprimirError(char *mensaje){
    werase(ventana->ventana[1]);
    box(ventana->ventana[1], 0, 0);
    mvwprintw(ventana->ventana[1], 1, 1, "%s", mensaje);
    wrefresh(ventana->ventana[1]);
    wmove(ventana->ventana[0], 1, 4);
    wrefresh(ventana->ventana[0]);
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
    mvwprintw(ventana->ventana[2],2,1,"%-5s %-5s %-5s %-5s %-5s %-5s %-10s %-10s %s",
           "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Proceso", "IR", "Status");
    mvwprintw(ventana->ventana[2],3,1,"----------------------------------------------------------------------------------");
    wrefresh(ventana->ventana[2]);
}

void  imprimirFila(void){
    mvwprintw(ventana->ventana[2],4,1,"%-5d %-5d %-5d %-5d %-5d %-5d %-10s %-10s %s",
           reg_id, reg_pc, reg_ax, reg_bx, reg_cx, reg_dx, 
           reg_proceso, reg_ir, "Correcto");
    wrefresh(ventana->ventana[2]);
    usleep(tiempo);
}

void imprimirFilaConError(char *mensaje_error){
    mvwprintw(ventana->ventana[2],4,1,"%-5d %-5d %-5d %-5d %-5d %-5d %-10s %-10s %s",
           reg_id, reg_pc, reg_ax, reg_bx, reg_cx, reg_dx, 
           reg_proceso, reg_ir, mensaje_error);
    wrefresh(ventana->ventana[2]);
    usleep(tiempo);
}

void imprimirTabla(void){
    imprimirEncabezadoEjecucion();
    imprimirFila();
}

void imprimirListos(PCB *nodo, int renglon){
    werase(ventana->ventana[3]);
    box(ventana->ventana[3], 0, 0);
    mvwprintw(ventana->ventana[3], 1, 1, "-----  LISTOS  -----");
    mvwprintw(ventana->ventana[3],2,1,"%-6s %-6s %-6s %-6s %-6s %-6s %-6s %-14s %-21s %s",
           "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Prior", "Proceso", "IR", "Status");
    mvwprintw(ventana->ventana[3],3,1,"---------------------------------------");
    mvwprintw(ventana->ventana[3], renglon+4, 1, "%-6d%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s",
           nodo->id, nodo->pc, nodo->ax, nodo->bx, nodo->cx, nodo->dx, nodo->prioridad,
           nodo->nombre, nodo->ir, nodo->estado);
    wrefresh(ventana->ventana[3]);
    usleep(tiempo);
}

void imprimirTerminados(PCB *nodo, int renglon){
    box(ventana->ventana[4], 0, 0);
    mvwprintw(ventana->ventana[4],2,1,"%-6s%-6s%-6s%-6s%-6s%-6s%-6s%-14s%-21s%s",
           "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Prior", "Proceso", "IR", "Status");
    mvwprintw(ventana->ventana[4],3,1,"---------------------------------------");
    mvwprintw(ventana->ventana[4], renglon+4, 1, "%-6d%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s",
           nodo->id, nodo->pc, nodo->ax, nodo->bx, nodo->cx, nodo->dx, nodo->prioridad,
           nodo->nombre, nodo->ir, nodo->estado);
    wrefresh(ventana->ventana[4]);
    usleep(tiempo);
}

void inicializarVentanas(Ventana *ventana){

    ventana->ventana[0] = newwin(3,139,0,7);    //Promt
    ventana->ventana[1] = newwin(3,87,3,65);    //Mensajes de error
    ventana->ventana[2] = newwin(7,87,14,65);    //Lista de Ejecucion
    ventana->ventana[3] = newwin(8,87,6,65);   //Lista de Listos
    ventana->ventana[4] = newwin(16,87,21,65);   //Lista de Terminados
    ventana->ventana[5] = newwin(31,65,6,0);   //Lista de Nuevos
    ventana->ventana[6] = newwin(3,65,3,0);    //Mensajes quantum
    ventana->update[0] = 1;
    ventana->update[1] = 1;
    ventana->update[2] = 1;
    ventana->update[3] = 1;
    ventana->update[4] = 1;
    ventana->update[5] = 1;
    ventana->update[5] = 1;
}

void imprimirVentanas(Ventana *ventana){
    ventanaPromt(ventana);
    ventanaMensaje(ventana);
    ventanaEjecucion(ventana);
    ventanaListos(ventana);
    ventanaTerminados(ventana);
    ventanaNuevos(ventana);
    ventanaQuantum(ventana);
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

void actualizaVentanas(Ventana *ventana, buffer *bufferC){
    if(ventana->update[0]){
        //printbuffer(ventana, bufferC);
    }
}



