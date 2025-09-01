/**
 * @file alu.c
 * @brief  Implementacion del modulo alu, realizacion de operaciones
 * @author Equipo: Los sistématicos
 * @date 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/alu.h"
#include "include/interprete.h"
#include "include/imprimir.h"

int reg_ax;
int reg_bx;
int reg_cx;
int reg_dx;

int reg_pc;
char reg_ir[16];

int reg_id;
char reg_proceso[16];

int aluGpo1(char *tipo_operacion, char *registro, int *dato){
        /* Operación Move */
    if (strcmp(OP_MOV, tipo_operacion) == 0){
        /* En registro Ax*/        
        if (strcmp(REG_AX, registro) == 0){
            reg_ax = *dato;
        }
        /* En registro Bx*/
        else if (strcmp(REG_BX, registro) == 0){
            reg_bx = *dato;
        }
        /* En registro Cx*/
        else if (strcmp(REG_CX, registro) == 0){
            reg_cx = *dato;
        }
        /* En registro Dx*/
        else if (strcmp(REG_DX, registro) == 0){
            reg_dx = *dato;
        }
        else{
            imprimirError(ERROR_REGISTRO_INVALIDO);
        }
    }

    
    /* Operación Suma */
    else if (strcmp(OP_ADD, tipo_operacion) == 0){
        /* En registro Ax*/
        if (strcmp(REG_AX, registro) == 0){
            reg_ax = reg_ax + *dato;
        }
        /* En registro Bx*/
        else if (strcmp(REG_BX, registro) == 0){
            reg_bx = reg_bx + *dato;
        }
        /* En registro Cx*/
        else if (strcmp(REG_CX, registro) == 0){
            reg_cx = reg_cx + *dato;
        }
        /* En registro Dx*/
        else if (strcmp(REG_DX, registro) == 0){
            reg_dx = reg_dx + *dato;
        }
        else{
            imprimirError(ERROR_REGISTRO_INVALIDO);
        }
    }


    /* Operación Resta */
    else if (strcmp(OP_SUB, tipo_operacion) == 0){
        /* En registro Ax*/
        if (strcmp(REG_AX, registro) == 0){
            reg_ax = reg_ax - *dato;
        }
        /* En registro Bx*/
        else if (strcmp(REG_BX, registro) == 0){
            reg_bx = reg_bx - *dato;
        }
        /* En registro Cx*/
        else if (strcmp(REG_CX, registro) == 0){
            reg_cx = reg_cx - *dato;
        }
        /* En registro Dx*/
        else if (strcmp(REG_DX, registro) == 0){
            reg_dx = reg_dx - *dato;
        }
        else{
            imprimirError(ERROR_REGISTRO_INVALIDO);
        }
    }


    /* Operación División */
    else if (strcmp(OP_DIV, tipo_operacion) == 0){
        /* En registro Ax*/
        if (strcmp(REG_AX, registro) == 0){
            reg_ax = reg_ax / *dato;
        }
        /* En registro Bx*/
        else if (strcmp(REG_BX, registro) == 0){
            reg_bx = reg_bx / *dato;
        }
        /* En registro Cx*/
        else if (strcmp(REG_CX, registro) == 0){
            reg_cx = reg_cx / *dato;
        }
        /* En registro Dx*/
        else if (strcmp(REG_DX, registro) == 0){
            reg_dx = reg_dx / *dato;
        }
        else{
            imprimirError(ERROR_REGISTRO_INVALIDO);
        }
    }


    /* Operación Multiplicación */
    else if (strcmp(OP_MUL, tipo_operacion) == 0){
        /* En registro Ax*/
        if (strcmp(REG_AX, registro) == 0){
            reg_ax = reg_ax * *dato;
        }
        /* En registro Bx*/
        else if (strcmp(REG_BX, registro) == 0){
            reg_bx = reg_bx * *dato;
        }
        /* En registro Cx*/
        else if (strcmp(REG_CX, registro) == 0){
            reg_cx = reg_cx * *dato;
        }
        /* En registro Dx*/
        else if (strcmp(REG_DX, registro) == 0){
            reg_dx = reg_dx * *dato;
        }
        else{
            imprimirError(ERROR_REGISTRO_INVALIDO);
        }
    }
}
    
int aluGpo2(char *tipo_operacion, char *registro){
    /* Operación Incremento */
    if (strcmp(OP_INC, tipo_operacion) == 0){
        /* En registro Ax*/
        if (strcmp(REG_AX, registro) == 0){
            reg_ax = reg_ax + 1;
        }
        /* En registro Bx*/
        else if (strcmp(REG_BX, registro) == 0){
            reg_bx = reg_bx + 1;
        }
        /* En registro Cx*/
        else if (strcmp(REG_CX, registro) == 0){
            reg_cx = reg_cx + 1;
        }
        /* En registro Dx*/
        else if (strcmp(REG_DX, registro) == 0){
            reg_dx = reg_dx + 1;
        }
        else{
            imprimirError(ERROR_REGISTRO_INVALIDO);
        }
    }


     /* Operación Decremento */
    else if (strcmp(OP_DEC, tipo_operacion) == 0){
        /* En registro Ax*/
        if (strcmp(REG_AX, registro) == 0){
            reg_ax = reg_ax - 1;
        }
        /* En registro Bx*/
        else if (strcmp(REG_BX, registro) == 0){
            reg_bx = reg_bx - 1;
        }
        /* En registro Cx*/
        else if (strcmp(REG_CX, registro) == 0){
            reg_cx = reg_cx - 1;
        }
        /* En registro Dx*/
        else if (strcmp(REG_DX, registro) == 0){
            reg_dx = reg_dx - 1;
        }
        else{
            imprimirError(ERROR_REGISTRO_INVALIDO);
        }
    }
}