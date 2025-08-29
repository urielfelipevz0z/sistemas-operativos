#include <stdio.h>
#include "include/interprete.h"
#include "include/alu.h"
#include "include/imprimir.h"

int main(){
    char comando[TAMANIO];
    
    while (1) {
        printf(">> ");
        //scanf("%[^\n]", comando);
        fgets(comando, sizeof(comando), stdin);
        interprete(comando);    //ejecuta a.asm     //salir         //ejecuta pedro.asm
    }
    
    
         
    return 0;
}