/**
 * @file imprimir.c
 * @brief Implementación del módulo de impresión y formateo de salida
 * @author Equipo: Los sistématicos
 * @date 2025
 */

#include "include/imprimir.h"

void imprimirEncabezado(void){
    printf("%-*s %-*s %-*s %-*s %-*s %-*s %-*s %-*s %s\n",
           ANCHO_COLUMNA_ID, "ID",
           ANCHO_COLUMNA_PC, "PC",
           ANCHO_COLUMNA_REG, "Ax",
           ANCHO_COLUMNA_REG, "Bx",
           ANCHO_COLUMNA_REG, "Cx",
           ANCHO_COLUMNA_REG, "Dx",
           ANCHO_COLUMNA_PROCESO, "Proceso",
           ANCHO_COLUMNA_IR, "IR",
           "Status");
    
    for (int i = 0; i < 80; i++){
        printf("-");
    }
    printf("\n");
}

void imprimirEstadoSistema(int mostrar_solo_encabezado){
    if (mostrar_solo_encabezado){
        imprimirEncabezado();
        return;
    }

        printf("%-*d %-*d %-*d %-*d %-*d %-*d %-*s %-*s\n",
            ANCHO_COLUMNA_ID, reg_id,
            ANCHO_COLUMNA_PC, reg_pc,
            ANCHO_COLUMNA_REG, reg_ax,
            ANCHO_COLUMNA_REG, reg_bx,
            ANCHO_COLUMNA_REG, reg_cx,
            ANCHO_COLUMNA_REG, reg_dx,
            ANCHO_COLUMNA_PROCESO, reg_proceso,
            ANCHO_COLUMNA_IR, reg_ir);
}

void imprimirEstadoCompleto(void){
    imprimirEncabezado();
    imprimirEstadoSistema(0);
}

void imprimirError(const char *mensaje){
    printf("\n[ERROR] %s\n\n", mensaje);
}




