#include <stdio.h>
#include <string.h>
#include "imprimir.h"

//Variables
#define TAMANIO 50 

/*
*Leera todo el comando por ejemplo "> ejecuta a.asm", "> salir"
*Se encargara de verificar si existe el archivo "a.asm" en este caso
*
*
*
*/

char cmd1[]="ejecuta"; //comando para ejecutar un archivo
char cmd2[]="salir"; //comando para salir del programa

int interprete(char *comando);

int interprete(char *comando){    //ejecuta a.asm
    printf("Comando: %s\n",comando);
    char copia[TAMANIO];
    char *delimitador=" ";
    char *token;

    strcpy(copia,comando);
    token = strtok(copia,delimitador);
    printf("Token: %s\n",token);


    if(strcmp(cmd1, token) != 0){                   //Comparacion del primer token con el comando
        return 1;                                   //El comando no coincide (comando erroneo)
    } else{
        printf("Ejecuta correctamente\n");
    }
    //comprueba que exista un archivo llamado igual que el token

}


void estados(int valor){
    switch (valor){
    case 1:
        printf("Error comando invalido\n");
        break;
    case 2:
        printf("Error archivo no encontrado\n");
        break;
    case 3:
        printf("\n");
        break;
    case 4:
        printf("\n");
        break;
    case 5:
        printf("\n");
        break;

    default:
        break;
    }


}