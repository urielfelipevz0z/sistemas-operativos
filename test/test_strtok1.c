#include <stdio.h>
#include <string.h>

int comprobarAsm(char *proceso);
void si();

int main(){
    si();
    
}

int comprobarAsm(char *proceso){       //a.asm
    //printf("llego: %s\n",proceso);
    char *extension;
    char copia[128];
    if(proceso == NULL){
        return -1;
    }
    strcpy(copia, proceso);
    //printf("copia: %s\n",copia);

    if(strcmp(".",proceso) == 0){
        printf("Falta especificar extension\n");
        return -1;
    }
    if(strcmp(proceso,strtok(copia, ".")) == 0){     //a.asm
        printf("Falta especificar extension\n");
        return -1;
    }
    extension = strtok(NULL,".");	//asm
    //printf("extension: %s\n",extension);
    if(extension == NULL){
        printf("Falta especificar extension\n");
        return -1;
    }
    if(strcmp("asm", extension) != 0){
        printf("Extension invalida\n");
        return -1;
    }
    //printf("exito bro\n");
    return 0;
}

void si(){
    char arg_copia[256];
    strcpy(arg_copia,"a.asm b.asm c.asm");  //a.asm b.asm
    printf("copia: %s\n", arg_copia);
    
    char *proceso = strtok(arg_copia, " ");
    strcpy(arg_copia ,strtok(NULL, " "));
    printf("proceso: %s\n", proceso);

    while(proceso != NULL){
        comprobarAsm(proceso);
        proceso = strtok(NULL, " ");
        printf("procesoWhile: %s\n", proceso);
        
    }
    printf("copia: %s\n", arg_copia);
}





