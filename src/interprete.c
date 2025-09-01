/**
 * @file interprete.c
 * @brief 
 * @author Equipo: Los sistématicos
 * @date 2025
 */

#include "include/interprete.h"
#include "include/alu.h"
#include "include/imprimir.h"
#include "include/globales.h"

static const char CMD_EJECUTA[] = "ejecuta";
static const char CMD_SALIR[] = "salir";

int reg_id;
char reg_proceso[16];


int interprete(char *comando){  //ejecutar a.asm
    char copia[TAMANIO_COMANDO];
    char *token;
    strcpy(copia, comando);
    token = strtok(copia, DELIMITADOR_ESPACIO); //ejecutar
    if(strcmp(CMD_EJECUTA, token) == 0){
        token = strtok(NULL, DELIMITADOR_ESPACIO); //a.asm
        strcpy(reg_proceso, token);
        leerArchivo(token); //a.asm
        reg_id++;
        return 0;
    }
    else if(strcmp(CMD_SALIR, token) == 0){
        exit(0);
        return 1;
    }
    else{
        imprimirError(ERROR_INSTRUCCION_NO_RECONOCIDA);
        return -1;
    }
}


int leerArchivo(char *nombre_archivo){
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL){
        imprimirError(ERROR_ARCHIVO_NO_ENCONTRADO);
    }

    char linea[TAMANIO_LINEA];
    char copia[TAMANIO_LINEA];
    char *token;
    char reg_ir[16];
    int reg_pc = 0;   
    while (fgets(linea, sizeof(linea), archivo) != NULL){   //MOV Ax,7
        reg_pc++;
        strcpy(copia, linea);   //MOV Ax,7
        strcpy(reg_ir, linea);
        token = strtok(copia, DELIMITADOR_ESPACIO); //MOV

        if (strcmp(OP_MOV, token) == 0){ //MOV = MOV
            return analizadorGpo1(token, strok(NULL, DELIMITADOR_ESPACIO)); //Ax,7
        }
        else if (strcmp(OP_ADD, token) == 0){
            return analizadorGpo1(token, strok(NULL, DELIMITADOR_ESPACIO));
        }
        else if (strcmp(OP_SUB, token) == 0){
            return analizadorGpo1(token, strok(NULL, DELIMITADOR_ESPACIO));
        }
        else if (strcmp(OP_MUL, token) == 0){
            return analizadorGpo1(token, strok(NULL, DELIMITADOR_ESPACIO));
        }
        else if (strcmp(OP_DIV, token) == 0){
            return analizadorGpo1(token, strok(NULL, DELIMITADOR_ESPACIO));
        }
        else if (strcmp(OP_INC, token) == 0){
            return analizadorGpo2(token, strtok(NULL, DELIMITADOR_ESPACIO));
        }
        else if (strcmp(OP_DEC, token) == 0){
            return analizadorGpo2(token, strtok(NULL, DELIMITADOR_ESPACIO));
        }
        else{
            imprimirError(ERROR_INSTRUCCION_NO_RECONOCIDA);
            return -1;
        }
    }

    fclose(archivo);
}


int analizadorGpo1(char *tipo_operacion, char *operandos){  //Ax,7
    char *registro = strtok(operandos, DELIMITADOR_COMA);   //Ax
    int numero_entero = atoi(strtok(NULL, DELIMITADOR_ESPACIO)); //7
    
    if(strcmp(REG_AX, registro) == 0){
        return aluGpo1(tipo_operacion,registro, numero_entero);
    }
    else if(strcmp(REG_BX, registro) == 0){
        return aluGpo1(tipo_operacion,registro, numero_entero);
    }
    else if(strcmp(REG_CX, registro) == 0){
        return aluGpo1(tipo_operacion,registro, numero_entero);
    }
    else if(strcmp(REG_DX, registro) == 0){
        return aluGpo1(tipo_operacion,registro, numero_entero);
    }
    else{
        imprimirError(ERROR_REGISTRO_INVALIDO);
        return -1;
    }
}


int analizadorGpo2(char *tipo_operacion, char *registro){   //Ax
    if (strcmp(REG_AX, registro) == 0){
        return aluGpo2(tipo_operacion, registro);
    }
    else if (strcmp(REG_BX, registro) == 0){
        return aluGpo2(tipo_operacion, registro);
    }
    else if (strcmp(REG_CX, registro) == 0){
        return aluGpo2(tipo_operacion, registro);
    }
    else if (strcmp(REG_DX, registro) == 0){
        return aluGpo2(tipo_operacion, registro);
    }
    else{
        imprimirError(ERROR_REGISTRO_INVALIDO);
        return -1;
    }
}



