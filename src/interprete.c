#include "include/controlador.h"

void interprete(char *comando){    
    buffer *bufferC = NULL;
    bufferC = (buffer *)malloc(sizeof(buffer));
    limpiarBuffer(bufferC);
    strcpy(bufferC->comandoCompleto, comando);
    
    if(extraerComando(bufferC) == -1){
        free(bufferC);
        return;
    }
    
    free(bufferC);
    reg_ax = 0, reg_bx = 0, reg_cx = 0, reg_dx = 0, reg_pc = 0; 
}