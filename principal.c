/**
 * @file principal.c
 * @brief Programa principal del simulador de sistema operativo
 * @author Equipo: Los sistématicos
 * @date 2025
 */

#include "include/interprete.h"
#include "include/alu.h"
#include "include/imprimir.h"



int main(){
    char comando[TAMANIO_COMANDO];
    int resultado;
    
    while (1) {
        printf(">> ");
        
        fgets(comando, sizeof(comando), stdin);
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