#include "include/alu.h"
#include "include/imprimir.h"

int reg_ax = 0;
int reg_bx = 0;
int reg_cx = 0;
int reg_dx = 0;

int *obtenerRegistro(const char *nombre){
    if (strcmp("Ax", nombre) == 0) return &reg_ax;
    if (strcmp("Bx", nombre) == 0) return &reg_bx;
    if (strcmp("Cx", nombre) == 0) return &reg_cx;
    if (strcmp("Dx", nombre) == 0) return &reg_dx;
    return NULL;
}

int aluGpo1(char *operacion, char *registro, int *valor){
    int *reg = obtenerRegistro(registro);
    if (reg == NULL){
        imprimirFilaConError("Registro inválido");
        return -1;
    }
    
    reg_pc++;
    
    if (strcmp("MOV", operacion) == 0){
        *reg = *valor;
    }else if (strcmp("ADD", operacion) == 0){
        *reg += *valor;
    }else if (strcmp("SUB", operacion) == 0){
        *reg -= *valor;
    }else if (strcmp("MUL", operacion) == 0){
        *reg *= *valor;
    }else if (strcmp("DIV", operacion) == 0){
        if (*valor == 0){
            reg_pc--;
            imprimirFilaConError("Division por cero");
            return -1;
        }
        *reg /= *valor;
    } else{
        reg_pc--;
        imprimirFilaConError("Operación no reconocida");
        return -1;
    }

    return 0;
}

int aluGpo2(char *operacion, char *registro){
    int *reg = obtenerRegistro(registro);
    if (reg == NULL){
        imprimirFilaConError("Registro inválido");
        return -1;
    }
    
    reg_pc++;
    
    if (strcmp("INC", operacion) == 0){
        (*reg)++;
    } else if (strcmp("DEC", operacion) == 0){
        (*reg)--;
    } else{
        reg_pc--;
        imprimirFilaConError("Operación no reconocida");
        return -1;
    }
        
    return 0;
}