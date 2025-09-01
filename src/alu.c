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

int aluGpo1(char *tipo_operacion, char *registro, int *dato){
        /* Operación Move */
    if (strcmp(OP_MOV, tipo_operacion) == 0){
        /* En registro Ax*/        
        if (strcmp(REG_AX, registro) == 0){
            reg_ax = *dato;
            return 0;
        }
        /* En registro Bx*/
        else if (strcmp(REG_BX, registro) == 0){
            reg_bx = *dato;
            return 0;
        }
        /* En registro Cx*/
        else if (strcmp(REG_CX, registro) == 0){
            reg_cx = *dato;
            return 0;
        }
        /* En registro Dx*/
        else if (strcmp(REG_DX, registro) == 0){
            reg_dx = *dato;
            return 0;
        }
        else{
            imprimirError(ERROR_REGISTRO_INVALIDO);
            return -1;
        }
    }

    
    /* Operación Suma */
    else if (strcmp(OP_ADD, tipo_operacion) == 0){
        /* En registro Ax*/
        if (strcmp(REG_AX, registro) == 0){
            reg_ax = reg_ax + *dato;
            return 0;
        }
        /* En registro Bx*/
        else if (strcmp(REG_BX, registro) == 0){
            reg_bx = reg_bx + *dato;
            return 0;
        }
        /* En registro Cx*/
        else if (strcmp(REG_CX, registro) == 0){
            reg_cx = reg_cx + *dato;
            return 0;
        }
        /* En registro Dx*/
        else if (strcmp(REG_DX, registro) == 0){
            reg_dx = reg_dx + *dato;
            return 0;
        }
        else{
            imprimirError(ERROR_REGISTRO_INVALIDO);
            return -1;
        }
    }


    /* Operación Resta */
    else if (strcmp(OP_SUB, tipo_operacion) == 0){
        /* En registro Ax*/
        if (strcmp(REG_AX, registro) == 0){
            reg_ax = reg_ax - *dato;
            return 0;
        }
        /* En registro Bx*/
        else if (strcmp(REG_BX, registro) == 0){
            reg_bx = reg_bx - *dato;
            return 0;
        }
        /* En registro Cx*/
        else if (strcmp(REG_CX, registro) == 0){
            reg_cx = reg_cx - *dato;
            return 0;
        }
        /* En registro Dx*/
        else if (strcmp(REG_DX, registro) == 0){
            reg_dx = reg_dx - *dato;
            return 0;
        }
        else{
            imprimirError(ERROR_REGISTRO_INVALIDO);
            return -1;
        }
    }


    /* Operación División */
    else if (strcmp(OP_DIV, tipo_operacion) == 0){
        /* En registro Ax*/
        if (strcmp(REG_AX, registro) == 0){
            reg_ax = reg_ax / *dato;
            return 0;
        }
        /* En registro Bx*/
        else if (strcmp(REG_BX, registro) == 0){
            reg_bx = reg_bx / *dato;
            return 0;
        }
        /* En registro Cx*/
        else if (strcmp(REG_CX, registro) == 0){
            reg_cx = reg_cx / *dato;
            return 0;
        }
        /* En registro Dx*/
        else if (strcmp(REG_DX, registro) == 0){
            reg_dx = reg_dx / *dato;
            return 0;
        }
        else{
            imprimirError(ERROR_REGISTRO_INVALIDO);
            return -1;
        }
    }


    /* Operación Multiplicación */
    else if (strcmp(OP_MUL, tipo_operacion) == 0){
        /* En registro Ax*/
        if (strcmp(REG_AX, registro) == 0){
            reg_ax = reg_ax * *dato;
            return 0;
        }
        /* En registro Bx*/
        else if (strcmp(REG_BX, registro) == 0){
            reg_bx = reg_bx * *dato;
            return 0;
        }
        /* En registro Cx*/
        else if (strcmp(REG_CX, registro) == 0){
            reg_cx = reg_cx * *dato;
            return 0;
        }
        /* En registro Dx*/
        else if (strcmp(REG_DX, registro) == 0){
            reg_dx = reg_dx * *dato;
            return 0;
        }
        else{
            imprimirError(ERROR_REGISTRO_INVALIDO);
            return -1;
        }
    }
}
    
int aluGpo2(char *tipo_operacion, char *registro){
    /* Operación Incremento */
    if (strcmp(OP_INC, tipo_operacion) == 0){
        /* En registro Ax*/
        if (strcmp(REG_AX, registro) == 0){
            reg_ax = reg_ax + 1;
            return 0;
        }
        /* En registro Bx*/
        else if (strcmp(REG_BX, registro) == 0){
            reg_bx = reg_bx + 1;
            return 0;
        }
        /* En registro Cx*/
        else if (strcmp(REG_CX, registro) == 0){
            reg_cx = reg_cx + 1;
            return 0;
        }
        /* En registro Dx*/
        else if (strcmp(REG_DX, registro) == 0){
            reg_dx = reg_dx + 1;
            return 0;
        }
        else{
            imprimirError(ERROR_REGISTRO_INVALIDO);
            return -1;
        }
    }


     /* Operación Decremento */
    else if (strcmp(OP_DEC, tipo_operacion) == 0){
        /* En registro Ax*/
        if (strcmp(REG_AX, registro) == 0){
            reg_ax = reg_ax - 1;
            return 0;
        }
        /* En registro Bx*/
        else if (strcmp(REG_BX, registro) == 0){
            reg_bx = reg_bx - 1;
            return 0;
        }
        /* En registro Cx*/
        else if (strcmp(REG_CX, registro) == 0){
            reg_cx = reg_cx - 1;
            return 0;
        }
        /* En registro Dx*/
        else if (strcmp(REG_DX, registro) == 0){
            reg_dx = reg_dx - 1;
            return 0;
        }
        else{
            imprimirError(ERROR_REGISTRO_INVALIDO);
            return -1;
        }
    }
}