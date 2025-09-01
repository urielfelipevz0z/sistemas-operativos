#include <stdio.h>
#include <stdlib.h>

int main(){
    char comando[20];
    char copia[20];
    char *token;
    fgets(comando, sizeof(comando), stdin);
    strcpy(copia, comando);

    MOV Ax,7


    token = strtok(copia, " ");
    printf("Operación: %s\n", token);
    token = strtok(NULL, ",");
    printf("Registro: %s\n", token);
    token = strtok(NULL, ",");
    printf("Num: %s\n", token);
}
