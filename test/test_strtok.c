#include <stdio.h>
#include <stdlib.h>

int main(){
    char comando[20];
    char copia[20];
    char *token;
    fgets(comando, sizeof(comando), stdin);
    strcpy(copia, comando);



    token = strtok(copia, " ");
    printf("Operación: %s\n", token);
    token = strtok(NULL, ",");
    printf("Registro: %s\n", token);
    token = strtok(NULL, ",");
    printf("Num: %s\n", token);
}


#include<stdio.h>
#include<string.h>

int claseProfe(){
    char cadena[50]= "Esto es una prueba";
    char copia[50];
    char *delimitador=" ";
    char *token;
        strcpy(copia,cadena);
        //printf("Cadena original:\n",cadena);
        token = strtok(cadena,delimitador);
        printf("Mi token %s\n",token);
        printf("Cadena despues del strtok %s\n",cadena);

        while (token !=NULL){
            printf("Token: %s\n",token);
            token=strtok(NULL,delimitador);
        }
        
return 1;
}