#include "include/controlador.h"

int aluGpo1(char *operacion, char *registro, int *valor){
    int *reg = obtenerRegistro(registro);
    if (reg == NULL){
        imprimirFilaConError("Registro inválido");
        return -1;
    }
    
    reg_pc++;
    
    if (strcmp("MOV", operacion) == 0){
        *reg = *valor;
    }else if (strcmp("ADD", operacion) == 0){
        *reg += *valor;
    }else if (strcmp("SUB", operacion) == 0){
        *reg -= *valor;
    }else if (strcmp("MUL", operacion) == 0){
        *reg *= *valor;
    }else if (strcmp("DIV", operacion) == 0){
        if (*valor == 0){
            //reg_pc--;
            imprimirFilaConError("Division por cero");
            return -1;
        }
        *reg /= *valor;
    } else{
        //reg_pc--;
        imprimirFilaConError("Operación no reconocida");
        return -1;
    }

    return 0;
}

int aluGpo2(char *operacion, char *registro){
    int *reg = obtenerRegistro(registro);
    if (reg == NULL){
        imprimirFilaConError("Registro inválido");
        return -1;
    }
    
    reg_pc++;
    
    if (strcmp("INC", operacion) == 0){
        (*reg)++;
    } else if (strcmp("DEC", operacion) == 0){
        (*reg)--;
    } else{
        //reg_pc--;
        imprimirFilaConError("Operación no reconocida");
        return -1;
    }
        
    return 0;
}

int analizadorGpo1(char *tipo_operacion, char *operandos){     //MOV y Ax,7
    if (strchr(operandos, '.') != NULL){    //cadena[] = {'.','@','_','-',';',':','+','*','/','!'}

        imprimirFilaConError("Separador incorrecto");
        return 1;
    }

    char *registro = strtok(operandos, ",");       //Ax
    char *valor = strtok(NULL, "");                 //7
    
    if (valor == NULL){
        imprimirFilaConError("Cantidad incorrecta de operandos");
        return 1;
    }
    
    if (validarRegistro(registro) == -1){
        imprimirFilaConError("Registro inválido");
        return 1;
    }
    
    if (!esNumeroValido(valor)){
        imprimirFilaConError("Uso incorrecto de valores");
        return 1;
    }

    int numero = atoi(valor);
    int resultado = aluGpo1(tipo_operacion, registro, &numero);
    if (resultado == 0){
        imprimirFila();
    }
    
    return 0;
}

int analizadorGpo2(char *tipo_operacion, char *registro){  //INC y Ax
    if (registro == NULL){
        imprimirFilaConError("Cantidad incorrecta de operandos");
        return 1;
    }
    
    if (strchr(registro, ',') != NULL){                 //Ax,7 -> truena
        imprimirFilaConError("Cantidad incorrecta de operandos");
        return 1;
    }
    
    if (validarRegistro(registro) == -1){
        imprimirFilaConError("Registro inválido");
        return 1;
    }
    
    int resultado = aluGpo2(tipo_operacion, registro);
    if (resultado == 0){
        imprimirFila();
    }

    return 0;
}

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




