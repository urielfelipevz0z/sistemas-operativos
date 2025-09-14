#include "include/controlador.h"

int interprete(char *comando){    
    buffer *bufferC = NULL;
    bufferC = (buffer *)malloc(sizeof(buffer));
    limpiarBuffer(bufferC);
    strcpy(bufferC->comandoCompleto, comando);
    
    if(extraerComando(bufferC) == -1){
        return 0;
    }
    
    reg_ax, reg_bx, reg_cx, reg_dx, reg_pc= 0; 
    return 0;
}


int leerArchivo(char *nombre_archivo){  //a.asm
    reg_id++;
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL){
        imprimirError("Archivo no encontrado");
        return -1;
    }

    char linea[TAMANIO_LINEA];
    reg_pc = 1;     //Reinicio de PC
    
    imprimirTabla();
    
    while (fgets(linea, sizeof(linea), archivo) != NULL){   //linea = MOV Ax,7 o INC Ax
        linea[strcspn(linea, "\n")] = 0;
        
        strcpy(reg_ir, linea);
        
        char copia[TAMANIO_LINEA];
        strcpy(copia, linea);
        char *token = strtok(copia, " ");       //token = MOV
        
        if (token == NULL){
            continue;
        }
        
        int tipo_op = tipoOperacion(token);     //1 o 2
        
        
        char *operandos = strtok(NULL, "");     //Ax,7
        if (operandos == NULL){
            imprimirFilaConError("Cantidad incorrecta de operandos");
            continue;
        }

        if (tipo_op == 1){
            analizadorGpo1(token, operandos);   //MOV y Ax,7
        } else if (tipo_op == 2){
            analizadorGpo2(token, operandos);
        } else{
            imprimirFilaConError("Instrucción no reconocida");
            continue;
        }
    }

    fclose(archivo);
    return 0;
}

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