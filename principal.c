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
    
    while (1) {
        printf(">> ");
        
        if (fgets(comando, sizeof(comando), stdin) == NULL) {
            printf("\nError leyendo entrada\n");
            break;
        }
        
        size_t len = strlen(comando);
        if (len > 0 && comando[len-1] == '\n') {
            comando[len-1] = '\0';
        }
        
        resultado = interprete(comando);
        
        if (resultado == 1) {
            break;
        } else if (resultado == -1) {
            printf("Error procesando comando\n");
        }
    }
    
    printf("Sistema terminado.\n");
    return 0;
}