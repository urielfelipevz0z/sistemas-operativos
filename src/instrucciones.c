#include "include/controlador.h"

void analizadorGpo1(char *tipo_operacion, char *operandos){     //MOV y Ax,7
    if (strchr(operandos, '.') != NULL){    //cadena[] = {'.','@','_','-',';',':','+','*','/','!'}
        imprimirFilaConError("Separador incorrecto");
        return;
    }

    char *registro = strtok(operandos, ",");       //Ax
    char *valor = strtok(NULL, "");                 //7
    
    if (valor == NULL){
        imprimirFilaConError("Cantidad incorrecta de operandos");
        return;
    }
    
    if (validarRegistro(registro) == -1){
        imprimirFilaConError("Registro inválido");
        return;
    }
    
    if (!esNumeroValido(valor)){
        imprimirFilaConError("Uso incorrecto de valores");
        return;
    }

    int numero = atoi(valor);
    int resultado = aluGpo1(tipo_operacion, registro, &numero);
    if (resultado == 0){
        imprimirFila();
    }
    // No imprimir nada si hubo error, ya se manejó en aluGpo1
}

void analizadorGpo2(char *tipo_operacion, char *registro){  //INC y Ax
    if (registro == NULL){
        imprimirFilaConError("Cantidad incorrecta de operandos");
        return;
    }
    
    if (strchr(registro, ',') != NULL){                 //Ax,7 -> truena
        imprimirFilaConError("Cantidad incorrecta de operandos");
        return;
    }
    
    if (validarRegistro(registro) == -1){
        imprimirFilaConError("Registro inválido");
        return;
    }
    
    int resultado = aluGpo2(tipo_operacion, registro);
    if (resultado == 0){
        imprimirFila();
    }
}