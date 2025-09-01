#include <stdio.h>
#include <stdlib.h>


int main(){
    char MOV[] = "MOV";
    char ADD[] = "ADD";
    char MUL[] = "MUL";
    char SUB[] = "SUB";

    char token[10];
    scanf("%s",token);


    if (strcmp(MOV, token) == 0){
        printf("MOV: Las cadenas son iguales\n");
    }
    else if (strcmp(ADD, token) == 0){
        printf("ADD: Las cadenas son iguales\n");
    }
    else if (strcmp(MUL, token) == 0){
        printf("MUL: Las cadenas son iguales\n");
    }
    else if (strcmp(SUB, token) == 0){
        printf("SUB: Las cadenas son iguales\n");
    }
    else{
        printf("NO");
    }
    
    
    return 0;

}
