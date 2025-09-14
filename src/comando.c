#include "include/controlador.h"

int extraerComando(buffer *bufferC){    //ejecuta a.asm     o   salir
    char copia[TAMANIO_COMANDO];
    char *token;
    
    if(strcmp("", bufferC->comandoCompleto) == 0){ //ejecuta a.asm
        return -1;
    }

    strcpy(copia, bufferC->comandoCompleto);
    strcpy(bufferC->comando, strtok(copia, " "));   //ejecuta o salir 
    token = strtok(NULL, " ");

    if(strcmp("salir", bufferC->comando) == 0){
        printf("Saliendo...\n");
        exit(0);
    }
    else if(strcmp("ejecuta", bufferC->comando) == 0){  //ejecuta
        if(token == NULL){
            return -1;
        }
        strcpy(bufferC->argumento, token); // a.asm
        strcpy(reg_ir, "");
        strcpy(reg_proceso, bufferC->argumento);

        if (bufferC->argumento == NULL){
            imprimirError("Falta especificar archivo");
            return -1;
        }
        else if (leerArchivo(bufferC->argumento) == -1){     //a.asm
        reg_id--;
        strcpy(reg_proceso, "");
        }
    } else{
        imprimirError("Comando no reconocido");
        return -1;
    }
}

void limpiarBuffer(buffer *bufferC) {
    if (bufferC != NULL) {
        memset(bufferC, 0, sizeof(buffer));
    }
}