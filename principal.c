/**
 * @file principal.c
 * @brief Programa principal del simulador de sistema operativo
 * @author Equipo: Los sistématicos
 * @date 2025
 */

/**
 * Compilación del proyecto versión detallada que hace make:

gcc -Iinclude -c principal.c -o build/principal.o
gcc -Iinclude -c src/alu.c -o build/alu.o
gcc -Iinclude -c src/interprete.c -o build/interprete.o
gcc -Iinclude -c src/imprimir.c -o build/imprimir.o
gcc build/principal.o build/alu.o build/interprete.o build/imprimir.o -o bin/sistema_operativo

* Compilación del proyecto versión simplificada:

gcc principal.c src/alu.c src/interprete.c src/imprimir.c -o bin/sistema_operativo -Iinclude

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