#include "interprete.h"
#include "alu.h"
#include "imprimir.h"
#include "globales.h"

int reg_id = 0;
char reg_proceso[16] = "";
int reg_pc = 0;
char reg_ir[16] = "";

int interprete(char *comando){
    if (comando == NULL || strlen(comando) == 0) {
        return 0;
    }
    
    char copia[TAMANIO_COMANDO];
    strcpy(copia, comando);
    char *token = strtok(copia, " ");
    
    if (token == NULL) {
        return 0;
    }
    
    if(strcmp("ejecuta", token) == 0){
        token = strtok(NULL, " ");
        if (token == NULL) {
            imprimirError("Falta especificar archivo");
            return 0;
        }
        
        reg_id++;
        
        reg_ax = 0;
        reg_bx = 0;
        reg_cx = 0;
        reg_dx = 0;
        reg_pc = 0;
        strcpy(reg_ir, "");
        
        strcpy(reg_proceso, token);
        leerArchivo(token);
        return 0;
    }
    else if(strcmp("salir", token) == 0){
        return 1;
    }
    else{
        imprimirError("Comando no reconocido");
        return 0;
    }
}

int leerArchivo(char *nombre_archivo){
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL){
        imprimirError("Archivo no encontrado");
        return -1;
    }

    char linea[TAMANIO_LINEA];
    reg_pc = 0;   
    
    imprimirEncabezado();
    
    while (fgets(linea, sizeof(linea), archivo) != NULL){
        reg_pc++;
        
        if (linea[strlen(linea)-1] == '\n') {
            linea[strlen(linea)-1] = '\0';
        }
        
        if (strlen(linea) == 0) {
            continue;
        }
        
        strcpy(reg_ir, linea);
        
        char copia[TAMANIO_LINEA];
        strcpy(copia, linea);
        char *token = strtok(copia, " ");
        
        if (token == NULL) {
            continue;
        }
        
        int tipo_op = tipoOperacion(token);
        
        if (tipo_op == 1) {
            char *operandos = strtok(NULL, "");
            if (operandos == NULL) {
                imprimirFilaConError("Faltan operandos");
                continue;
            }
            if (analizadorGpo1(token, operandos) == 0) {
                imprimirFila();
            }
        } else if (tipo_op == 2) {
            char *registro = strtok(NULL, " ,");
            if (registro == NULL) {
                imprimirFilaConError("Falta registro");
                continue;
            }
            
            char *extra = strtok(NULL, " ,");
            if (extra != NULL) {
                imprimirFilaConError("Sintaxis incorrecta");
                continue;
            }
            if (analizadorGpo2(token, registro) == 0) {
                imprimirFila();
            }
        } else {
            imprimirFilaConError("Instrucción no reconocida");
            continue;
        }
    }

    fclose(archivo);
    return 0;
}

int analizadorGpo1(char *tipo_operacion, char *operandos){
    char *registro = strtok(operandos, ",");
    char *valor_str = strtok(NULL, " ");
    
    if (registro == NULL || valor_str == NULL) {
        imprimirFilaConError("Sintaxis incorrecta");
        return -1;
    }
    
    int numero = atoi(valor_str);
    
    if (validarRegistro(registro) != -1) {
        return aluGpo1(tipo_operacion, registro, &numero);
    } else {
        imprimirFilaConError("Registro inválido");
        return -1;
    }
}

int analizadorGpo2(char *tipo_operacion, char *registro){
    if (registro == NULL) {
        imprimirFilaConError("Falta registro");
        return -1;
    }
    
    if (validarRegistro(registro) != -1) {
        return aluGpo2(tipo_operacion, registro);
    } else {
        imprimirFilaConError("Registro inválido");
        return -1;
    }
}

int validarRegistro(const char *registro) {
    for (int i = 0; i < NUM_REGISTROS; i++) {
        if (strcmp(REGISTROS[i], registro) == 0) {
            return i;
        }
    }
    return -1;
}

int tipoOperacion(const char *operacion) {
    for (int i = 0; i < NUM_OPS_GPO1; i++) {
        if (strcmp(OPERACIONES_GPO1[i], operacion) == 0) {
            return 1;
        }
    }
    
    for (int i = 0; i < NUM_OPS_GPO2; i++) {
        if (strcmp(OPERACIONES_GPO2[i], operacion) == 0) {
            return 2;
        }
    }
    
    return -1;
}
