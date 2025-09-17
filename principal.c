/**
 * @file principal.c
 * @brief Programa principal del simulador de sistema operativo
 * @author Equipo: Los sistématicos
 * @date 2025
 * gcc -I. principal.c src/alu.c src/imprimir.c src/interprete.c src/comando.c src/globales.c src/manejador_archivos.c src/instrucciones.c src/validar.c -o sistematicos
 */

#include "include/controlador.h"

int main(){
        
    while (1){
        printf(">> ");
        leerComando(comando);
    }
}