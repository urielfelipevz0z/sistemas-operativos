#include "include/imprimir.h"
#include "include/globales.h"

void imprimirEncabezado(void){
    printf("%-6s%-6s%-6s%-6s%-6s%-6s%-6s%-14s%-21s%s\n",
           "ID", "PC", "ZF", "Ax", "Bx", "Cx", "Dx", "Proceso", "IR", "Status");
    printf("--------------------------------------------------------------------------------\n");
}

void imprimirFila(void){
    printf("%-6d%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s\n",
           reg_id, reg_pc, reg_Zf, reg_ax, reg_bx, reg_cx, reg_dx, 
           reg_proceso, reg_ir, "Correcto");
}

void imprimirFilaConError(char *mensaje_error){
    printf("%-6d%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s\n",
           reg_id, reg_pc, reg_Zf, reg_ax, reg_bx, reg_cx, reg_dx, 
           reg_proceso, reg_ir, mensaje_error);
	//reg_pc++;
}

void imprimirTabla(void){
    imprimirEncabezado();
}

void imprimirError(char *mensaje){
    printf("[ERROR] %s\n", mensaje);
}
