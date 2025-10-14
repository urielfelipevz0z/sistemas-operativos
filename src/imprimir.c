#include "include/controlador.h"

//Imprimir el cuadro de mensajes de errores
void imprimirError(char *mensaje){
    werase(ventana->ventana[1]);
    box(ventana->ventana[1], 0, 0);
    mvwprintw(ventana->ventana[1], 1, 1, "Mensaje: %s", mensaje);
    wrefresh(ventana->ventana[1]);
    wmove(ventana->ventana[0], 1, 4);
    wrefresh(ventana->ventana[0]);
}

void imprimirEncabezadoEjecucion(void){
    werase(ventana->ventana[2]);
    box(ventana->ventana[2], 0, 0);
    mvwprintw(ventana->ventana[2], 1, 1, "-----  EJECUCION  -----");
    mvwprintw(ventana->ventana[2],2,1,"%-6s%-6s%-6s%-6s%-6s%-6s%-14s%-21s%s",
           "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Proceso", "IR", "Status");
    mvwprintw(ventana->ventana[2],3,1,"-------------------------------------------------------------------------------");
    wrefresh(ventana->ventana[2]);

}

void imprimirFila(void){
    mvwprintw(ventana->ventana[2],4,1,"%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s",
           reg_id, reg_pc, reg_ax, reg_bx, reg_cx, reg_dx, 
           reg_proceso, reg_ir, "Correcto");
    wrefresh(ventana->ventana[2]);
    usleep(tiempo);
}
void imprimirFilaConError(char *mensaje_error){
    mvwprintw(ventana->ventana[2],4,1,"%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s",
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
    mvwprintw(ventana->ventana[3],2,1,"%-6s%-6s%-6s%-6s%-6s%-6s%-14s%-21s%s",
           "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Proceso", "IR", "Status");
    mvwprintw(ventana->ventana[3],3,1,"---------------------------------------");
    mvwprintw(ventana->ventana[3], renglon+4, 1, "%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s",
           nodo->id, nodo->pc, nodo->ax, nodo->bx, nodo->cx, nodo->dx, 
           nodo->nombre, "-", "-");
    wrefresh(ventana->ventana[3]);
    usleep(tiempo);
}

void imprimirTerminados(PCB *nodo, int renglon){
    box(ventana->ventana[4], 0, 0);
    mvwprintw(ventana->ventana[4],2,1,"%-6s%-6s%-6s%-6s%-6s%-6s%-14s%-21s%s",
           "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Proceso", "IR", "Status");
    mvwprintw(ventana->ventana[4],3,1,"---------------------------------------");
    mvwprintw(ventana->ventana[4], renglon+4, 1, "%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s",
           nodo->id, nodo->pc, nodo->ax, nodo->bx, nodo->cx, nodo->dx, 
           nodo->nombre, nodo->ir, nodo->estado);
    wrefresh(ventana->ventana[4]);
    usleep(tiempo);
}