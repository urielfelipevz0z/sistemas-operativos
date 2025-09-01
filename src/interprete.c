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

int interprete(char *comando){  //ejecuta a.asm
    char copia[TAMANIO_COMANDO];
    char *token;
    strcpy(copia, comando);
    token = strtok(copia, DELIMITADOR_ESPACIO); //ejecuta
    printf("%s\n",token);
    token[strcspn(token, "\n")] = 0;
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
    nombre_archivo[strcspn(nombre_archivo, "\n")] = 0;
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL){
        imprimirError(ERROR_ARCHIVO_NO_ENCONTRADO);
        return -1;
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
            analizadorGpo1(token, strtok(NULL, DELIMITADOR_ESPACIO)); //Ax,7
        }
        else if (strcmp(OP_ADD, token) == 0){
            analizadorGpo1(token, strtok(NULL, DELIMITADOR_ESPACIO));
        }
        else if (strcmp(OP_SUB, token) == 0){
            analizadorGpo1(token, strtok(NULL, DELIMITADOR_ESPACIO));
        }
        else if (strcmp(OP_MUL, token) == 0){
            analizadorGpo1(token, strtok(NULL, DELIMITADOR_ESPACIO));
        }
        else if (strcmp(OP_DIV, token) == 0){
            analizadorGpo1(token, strtok(NULL, DELIMITADOR_ESPACIO));
        }
        else if (strcmp(OP_INC, token) == 0){
            analizadorGpo2(token, strtok(NULL, DELIMITADOR_ESPACIO));
        }
        else if (strcmp(OP_DEC, token) == 0){
            analizadorGpo2(token, strtok(NULL, DELIMITADOR_ESPACIO));
        }
        else{
            imprimirError(ERROR_INSTRUCCION_NO_RECONOCIDA);
        }
    }

    fclose(archivo);
}


int analizadorGpo1(char *tipo_operacion, char *operandos){  //Ax,7
    char *registro = strtok(operandos, DELIMITADOR_COMA);   //Ax
    int numero_entero = atoi(strtok(NULL, DELIMITADOR_ESPACIO)); //7
    
    if(strcmp(REG_AX, registro) == 0){
        aluGpo1(tipo_operacion,registro, &numero_entero);
    }
    else if(strcmp(REG_BX, registro) == 0){
        aluGpo1(tipo_operacion,registro, &numero_entero);
    }
    else if(strcmp(REG_CX, registro) == 0){
        aluGpo1(tipo_operacion,registro, &numero_entero);
    }
    else if(strcmp(REG_DX, registro) == 0){
        aluGpo1(tipo_operacion,registro, &numero_entero);
    }
    else{
        imprimirError(ERROR_REGISTRO_INVALIDO);
    }
}


int analizadorGpo2(char *tipo_operacion, char *registro){   //Ax
    if (strcmp(REG_AX, registro) == 0){
        aluGpo2(tipo_operacion, registro);
    }
    else if (strcmp(REG_BX, registro) == 0){
        aluGpo2(tipo_operacion, registro);
    }
    else if (strcmp(REG_CX, registro) == 0){
        aluGpo2(tipo_operacion, registro);
    }
    else if (strcmp(REG_DX, registro) == 0){
        aluGpo2(tipo_operacion, registro);
    }
    else{
        imprimirError(ERROR_REGISTRO_INVALIDO);
    }
}