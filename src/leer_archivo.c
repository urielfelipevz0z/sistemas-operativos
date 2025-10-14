#include "include/controlador.h"
int bandera = 0;
char desc[256];

int leerArchivo(PCB *proceso){  //a.asm
    reiniciarRegistros();
    reg_id++;
    FILE *archivo = proceso->archivo;
    if (archivo == NULL){
        imprimirError("Archivo no encontrado");
        return -1;
    }

    char linea[TAMANIO_LINEA];

    imprimirTabla();
    
    while (fgets(linea, sizeof(linea), archivo) != NULL){   //linea = MOV Ax,7 o INC Ax
        bandera = 0;
        linea[strcspn(linea, "\n")] = 0;
        
        strcpy(reg_ir, linea);
        
        char copia[TAMANIO_LINEA];
        strcpy(copia, linea);
        char *token = strtok(copia, " ");       //token = MOV
        
        if (token == NULL){
            continue;
        }

        if (strcmp("END", token) == 0){
            bandera = 1;
            sprintf(desc, "Archivo %s finalizado por instruccion END", reg_proceso);
            imprimirError(desc);
            strcpy(reg_estado, "CORRECTO");
            fclose(archivo);
            reg_pc++;
            return 0;
        }
        
        int tipo_op = tipoOperacion(token);     //1 o 2
        
        char *operandos = strtok(NULL, "");     //Ax,7
        if (operandos == NULL){
            imprimirFilaConError("Cantidad incorrecta de operandos");
            continue;
        }

        if (tipo_op == 1){
            analizadorGpo1(token, operandos);   //MOV y Ax,7
        } else if (tipo_op == 2){
            analizadorGpo2(token, operandos);
        } else{
            imprimirFilaConError("Instrucción no reconocida");
            continue;
        }
    }

    if(bandera == 0){
        sprintf(desc, "[WARNING]: Finalizo pero no se encontró la instruccion END en el archivo %s", reg_proceso);
        imprimirError(desc);
    }
    
    fclose(archivo);
    return 0;
}




