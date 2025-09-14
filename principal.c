/**
 * @file principal.c
 * @brief Programa principal del simulador de sistema operativo
 * @author Equipo: Los sistématicos
 * @date 2025
 * gcc -I. principal.c src/alu.c src/imprimir.c src/interprete.c -o so
 */

#include "include/controlador.h"

int main(){
    char comando[TAMANIO_COMANDO];
    int resultado;
    
    while (1){
        printf(">> ");
        
        if (fgets(comando, sizeof(comando), stdin) == NULL){
            printf("\nError leyendo entrada\n");
            break;
        }
        comando[strcspn(comando, "\n")] = 0;
        
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