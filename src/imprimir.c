#include "include/controlador.h"
//mvprintw(0, 0, ">> ");
void imprimirEncabezado(void){
    mvprintw(2,0,"%-6s%-6s%-6s%-6s%-6s%-6s%-14s%-21s%s\n",
           "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Proceso", "IR", "Status");
    mvprintw(3,0,"--------------------------------------------------------------------------------\n");
    refresh();
}

void imprimirFila(void){
    mvprintw(4,0,"%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s\n",
           reg_id, reg_pc, reg_ax, reg_bx, reg_cx, reg_dx, 
           reg_proceso, reg_ir, "Correcto");
           refresh();   
           getch();
}
void imprimirFilaConError(char *mensaje_error){
    mvprintw(8,0,"%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s\n",
           reg_id, reg_pc, reg_ax, reg_bx, reg_cx, reg_dx, 
           reg_proceso, reg_ir, mensaje_error);
           refresh();
           getch();
}

void imprimirTabla(void){
    imprimirEncabezado();
    imprimirFila();
}

void imprimirError(char *mensaje){
    mvprintw(2,0,"[ERROR] %s\n", mensaje);
}

void imprimirFilaPr(PCB *nodo){
    mvprintw(4,0,"%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s\n",
           nodo->id, nodo->pc, nodo->ax, nodo->bx, nodo->cx, nodo->dx, 
           nodo->nombre, nodo->ir, "Correcto");
           refresh();   
           getch();
}