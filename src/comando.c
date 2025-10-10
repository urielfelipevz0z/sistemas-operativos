#include "include/controlador.h"

char copia[TAMANIO_COMANDO];
char *token;

int extraerComando(buffer *bufferC){    //ejecuta a.asm     o   salir
        
    if(strcmp("", bufferC->comandoCompleto) == 0){ //ejecuta a.asm
        return -1;
    }

    strcpy(copia, bufferC->comandoCompleto);    //ejecuta a.asm b.asm. n.asm o salir o ejecuta a.asm
    strcpy(bufferC->comando, strtok(copia, " "));   //ejecuta o salir

    token = strtok(NULL, "");  //a.asm b.asm c.asm

    if(strcmp("salir", bufferC->comando) == 0 || strcmp("exit", bufferC->comando) == 0){
        printf("Saliendo...\n");
        endwin();
        exit(0);
    }
    else if(strcmp("ejecuta", bufferC->comando) == 0){  //ejecuta
        if(token == NULL){ //revisa la parte de la derecha a.asm
            imprimirError("Falta especificar archivo");
            return -1;
        }
        strcpy(bufferC->argumento, token); // a.asm b.asm c.asm Meter while abajo
        
        gestorProcesos(bufferC->argumento, &(arreglo_de_listas[0]));

        // if(comprobarAsm(bufferC->argumento, token)){
        //     return -1;
        // }

        // strcpy(reg_ir, "");
        // strcpy(reg_proceso, bufferC->argumento); //a.asm

    } else{
        imprimirError("Comando no reconocido");
        return -1;
    }
}

void leerComando(char *comando){
    getstr(comando);
    interprete(comando);
}

void limpiarBuffer(buffer *bufferC) {
    if (bufferC != NULL) {
        memset(bufferC, 0, sizeof(buffer));
    }
}
