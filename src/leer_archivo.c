#include "include/controlador.h"
int bandera = 0;

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
            imprimirFilaConError("Terminado por instruccion END");
            mvprintw(6,0,"Archivo finalizado\n");
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

    if(bandera == 1){
        mvprintw(6,0,"Archivo finalizado\n");
    }else{
        mvprintw(6,0,"[WARNING]: No se encontró la instruccion END...\n");
    }
    
    fclose(archivo);
    return 0;
}




