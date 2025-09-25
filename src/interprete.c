#include "include/interprete.h"
#include "include/alu.h"
#include "include/imprimir.h"
#include "include/globales.h"
#include <stdlib.h>

int reg_id = 0;
char reg_proceso[16] = "";
int reg_pc = 0;
char reg_ir[16] = "";

int interprete(char *comando){    
    char copia[TAMANIO_COMANDO];
    strcpy(copia, comando);
    char *token = strtok(copia, " ");
    
    if (token == NULL){
        return 0;
    }
    
    if(strcmp("ejecuta", token) == 0){
        token = strtok(NULL, "\0"); // ejecuta a.asm/0
        if (token == NULL){
            imprimirError("Falta especificar archivo");
            return 0;
        }
        
        reg_ax = 0;
        reg_bx = 0;
        reg_cx = 0;
        reg_dx = 0;
        reg_pc = 0;
        strcpy(reg_ir, "");
        strcpy(reg_proceso, token);
        
        if (leerArchivo(token) == -1){
            reg_id--;
            strcpy(reg_proceso, "");
        }

        reg_id++;
        return 0;
    } else if(strcmp("salir", token) == 0){
        return 1;
    } else{
        imprimirError("Comando no reconocido");
        return 0;
    }
}

int leerArchivo(char *nombre_archivo){  //a.asm
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL){
        imprimirError("Archivo no encontrado");
        return -1;
    }

    char linea[TAMANIO_LINEA];
    reg_pc = 0;     //Reinicio de PC
    
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
        
        if (strcmp("END", token) == 0){
            imprimirFilaConError("Instruccion END encontrada, cierre del documento");
            fclose(archivo);
            reg_pc++;
            return 0;
        }
        
        int tipo_op = tipoOperacion(token);     //1 o 2
        
        
        char *operandos = strtok(NULL, "");     //Ax,7
        if (operandos == NULL){
		reg_pc++;
            imprimirFilaConError("Cantidad incorrecta de operandos");
            continue;
        }

        if (tipo_op == 1){
            analizadorGpo1(token, operandos);   //MOV y Ax,7
        } else if (tipo_op == 2){
            analizadorGpo2(token, operandos);
        } else{
		reg_pc++;
            imprimirFilaConError("Instrucción no reconocida");
            continue;
        }
    }

    fclose(archivo);
    return 0;
}

void analizadorGpo1(char *tipo_operacion, char *operandos){     //MOV y Ax,7
//printf("tipo: %s y operando: %s\n", tipo_operacion, operandos);
if (strchr(operandos, '.') != NULL){    //cadena[] = {'.','@','_','-',';',':','+','*','/','!'}
        reg_pc++;
	imprimirFilaConError("Separador incorrecto");
        return;
    }

    
    
    char *registro = strtok(operandos, ",");       //Ax
    char *valor = strtok(NULL, "");                 //7
  //  printf("reg: %s, valor:%s\n",registro,valor);
    if (valor == NULL){
	reg_pc++;
        imprimirFilaConError("Cantidad incorrecta de operandos");
        return;
    }
   // printf("registro: %s\n", registro);
    if (validarRegistro(registro) == -1){
//printf("NOOOO\n");
	reg_pc++;
        imprimirFilaConError("Registro inválido");
        return;
    }
    
    if (!esNumeroValido(valor)){
	reg_pc++;
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
  //  printf("Entre al analizador gp2\n");
	if (registro == NULL){
	reg_pc++;
        imprimirFilaConError("Cantidad incorrecta de operandos");
        return;
    }
    
    if (strchr(registro, ',') != NULL){                 //Ax,7 -> truena
	reg_pc++;
        imprimirFilaConError("Cantidad incorrecta de operandos");
        return;
    }
    
    if (validarRegistro(registro) == -1){
	reg_pc++;
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
//	printf("REGISTRO: %s, compararcion: %s\n", REGISTROS[i], registro);
  //      printf("Valor de i:%d\n",i);    
	return i;
        }
    }
//printf("Retorno de -1\n");
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
