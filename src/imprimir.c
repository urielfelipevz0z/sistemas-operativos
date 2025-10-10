#include "include/controlador.h"
//mvprintw(0, 0, ">> ");
void imprimirEncabezado(void){
    mvprintw(3,0,"%-6s%-6s%-6s%-6s%-6s%-6s%-14s%-21s%s\n",
           "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Proceso", "IR", "Status");
    mvprintw(4,0,"--------------------------------------------------------------------------------\n");
    refresh();
}

void imprimirFila(void){
    mvprintw(5,0,"%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s\n",
           reg_id, reg_pc, reg_ax, reg_bx, reg_cx, reg_dx, 
           reg_proceso, reg_ir, "Correcto");
           refresh();   
           usleep(tiempo);
}
void imprimirFilaConError(char *mensaje_error){
    mvprintw(5,0,"%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s\n",
           reg_id, reg_pc, reg_ax, reg_bx, reg_cx, reg_dx, 
           reg_proceso, reg_ir, mensaje_error);
           refresh();
           usleep(tiempo);
}

void imprimirTabla(void){
    imprimirEncabezado();
    imprimirFila();
}

void imprimirError(char *mensaje){
    mvprintw(6,0,"[ERROR] %s\n", mensaje);
}

void imprimirFilaPr(PCB *nodo){
    mvprintw(5,0,"%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s\n",
           nodo->id, nodo->pc, nodo->ax, nodo->bx, nodo->cx, nodo->dx, 
           nodo->nombre, nodo->ir, "Correcto");
           refresh();   
           usleep(tiempo);
}