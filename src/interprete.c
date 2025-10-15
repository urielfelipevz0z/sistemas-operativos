#include "include/controlador.h"

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
//Iguala los registros locales a los globales
void igualarRegistros(PCB *nodo){
    nodo->ax = reg_ax;
    nodo->bx = reg_bx;
    nodo->cx = reg_cx;
    nodo->dx = reg_dx;
    nodo->pc = reg_pc;
    nodo->id = reg_id;
    strcpy(nodo->ir, reg_ir);
    strcpy(nodo->estado, reg_estado);
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