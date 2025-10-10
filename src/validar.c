#include "include/controlador.h"


int validarRegistro(const char *registro){      //Ax, Bx, etc.
    for (int i = 0; i < NUM_REGISTROS; i++) {
        if (strcmp(REGISTROS[i], registro) == 0){
            return i;
        }
    }
    return -1;
}

int tipoOperacion(const char *operacion){       //MOV
    for (int i = 0; i < NUM_OPS_GPO1; i++){
        if (strcmp(OPERACIONES_GPO1[i], operacion) == 0){
            return 1;
        }
    }
    
    for (int i = 0; i < NUM_OPS_GPO2; i++){
        if (strcmp(OPERACIONES_GPO2[i], operacion) == 0){
            return 2;
        }
    }
    
    return -1;
}

int esNumeroValido(const char *str){ // Ax, Z, A, 8, as, 1026,   234A -3
    int len = strlen(str);
    int i = 0;
    
    if (str[0] == '-') i = 1;       //Acepta los negativos
    
    for (; i < len; i++){
        if (str[i] < '0' || str[i] > '9'){ //0,1,2,3,4,5,6,7,8,9
            return 0;
        }
    }

    return 1;
}

int *obtenerRegistro(const char *nombre){
    if (strcmp("Ax", nombre) == 0) return &reg_ax;
    if (strcmp("Bx", nombre) == 0) return &reg_bx;
    if (strcmp("Cx", nombre) == 0) return &reg_cx;
    if (strcmp("Dx", nombre) == 0) return &reg_dx;
    return NULL;
}

// Cambiar logica de comprobacion usando strtok(ya no)
int comprobarAsm(char *proceso){    //a.asm
    char *extension;
    char copia[128];
    if(proceso == NULL){
        return -1;
    }
    strcpy(copia, proceso);

    if(strcmp(proceso,".") == 0){   //.
        imprimirError("Falta especificar extension");
        return -1;
    }
    if(strcmp(proceso,strtok(copia, ".")) == 0){     //a
        imprimirError("Falta especificar extension");
        return -1;
    }
    extension = strtok(NULL,".");	//asm o txt o c o java
    if(extension == NULL){
        imprimirError("Falta especificar extension");
        return -1;
    }
    if(strcmp("asm", extension) != 0){
        imprimirError("Extension invalida");
        return -1;
    }
    return 0;
}