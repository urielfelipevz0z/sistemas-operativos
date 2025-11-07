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

    } else{
        imprimirError("Comando no reconocido");
        return -1;
    }
}

void leerComando(char *comando){
    wgetnstr(ventana->ventana[0],comando,100);
    interprete(comando);
    ventanaPromt(ventana);
}

void limpiarBuffer(buffer *bufferC) {
    if (bufferC != NULL) {
        memset(bufferC, 0, sizeof(buffer));
    }
}

void reiniciarRegistros(){
    reg_ax = 0;
    reg_bx = 0;
    reg_cx = 0;
    reg_dx = 0;
    reg_pc = 1;
    strcpy(reg_ir, "");
    strcpy(reg_estado, "ERROR");
    //strcpy(reg_proceso, "");
}

void guardarContexto(PCB *nodo){
    nodo->ax = reg_ax;
    nodo->bx = reg_bx;
    nodo->cx = reg_cx;
    nodo->dx = reg_dx;
    nodo->pc = reg_pc;
    nodo->id = reg_id;
    strcpy(nodo->ir, reg_ir);
    strcpy(nodo->estado, reg_estado);
}

void cargarContexto(PCB *nodo){
    Q = 0;
    reg_ax = nodo->ax;
    reg_bx = nodo->bx;
    reg_cx = nodo->cx;
    reg_dx = nodo->dx;
    reg_pc = nodo->pc;
    reg_id = nodo->id;
    strcpy(nodo->estado, "");
}


void interprete(char *comando){    
    buffer *bufferC = NULL;
    bufferC = (buffer *)malloc(sizeof(buffer));
    limpiarBuffer(bufferC);
    strcpy(bufferC->comandoCompleto, comando);
    
    
    if(extraerComando(bufferC) == -1){
        if(bufferC != NULL){
            free(bufferC);
            bufferC = NULL;
        }
        
        return;
    }
    
    if(bufferC != NULL){
            free(bufferC);
            bufferC = NULL;
        }
}

int kbhito(void){
    struct timeval tv;
    fd_set read_fd;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&read_fd);
    FD_SET(0,&read_fd);
    if(select(1, &read_fd, NULL, NULL, &tv) == -1){
        return 0;    
    }

    if(FD_ISSET(0, &read_fd)){
        return 1;
    }
    return 0;
}








