/**
 * @file principal.c
 * @brief Programa principal del simulador de sistema operativo
 * @author Equipo: Los sistématicos
 * @date 2025
 */

#include "interprete.h"
#include "alu.h"
#include "imprimir.h"

int main(){
    char comando[TAMANIO_COMANDO];
    int resultado;
    
    while (1){
        printf(">> ");
        
        if (fgets(comando, sizeof(comando), stdin) == NULL){
            printf("\nError leyendo entrada\n");
            break;
        }
        
        if (comando[strlen(comando)-1] == '\n'){
            comando[strlen(comando)-1] = '\0';
        }
        
        resultado = interprete(comando);
        
        if (resultado == 1){
            break;
        } else if (resultado == -1){
            printf("Error procesando comando\n");
        }
    }
    
    printf("Sistema terminado.\n");
    return 0;
}