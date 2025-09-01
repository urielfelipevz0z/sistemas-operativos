#include "imprimir.h"
#include "globales.h"

void imprimirEncabezado(void){
    printf("ID    PC    Ax    Bx    Cx    Dx    Proceso       IR                   Status\n");
    printf("------------------------------------------------------------------------\n");
}

void imprimirFila(void){
    printf("%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s\n",
           reg_id, reg_pc, reg_ax, reg_bx, reg_cx, reg_dx, 
           reg_proceso, reg_ir, "Correcto");
}

void imprimirTabla(void){
    imprimirEncabezado();
    imprimirFila();
}

void imprimirError(char *mensaje){
    printf("[ERROR] %s\n", mensaje);
}
