/**
 * @file principal.c
 * @brief Programa principal del simulador de sistema operativo
 * @author Los papus y uriel
 * @date 2025
 */

#include "include/interprete.h"
#include "include/alu.h"
#include "include/imprimir.h"

int main() {
    char comando[TAMANIO_COMANDO];
    int resultado;
    
    /* Inicializar sistema */
    alu_inicializar();
    
    /* Mostrar bienvenida */
    imprimir_bienvenida();
    
    /* Bucle principal */
    while (1) {
        printf(">> ");
        fflush(stdout);
        
        /* Leer comando del usuario */
        if (fgets(comando, sizeof(comando), stdin) == NULL) {
            /* EOF o error de lectura */
            printf("\nSaliendo...\n");
            break;
        }
        
        /* Procesar comando */
        resultado = interprete(comando);
        
        /* Verificar si debe salir */
        if (resultado == 1) {
            break; /* Comando 'salir' */
        } else if (resultado == -1) {
            /* Error crítico, pero continuar */
            printf("Error procesando comando\n");
        }
    }
    
    printf("Sistema terminado.\n");
    return 0;
}