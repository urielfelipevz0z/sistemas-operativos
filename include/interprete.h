/**
 * @file interprete.h
 * @brief Header para el módulo intérprete de comandos y ensamblador
 * @author Equipo: Los sistématicos
 * @date 2025
 */

#ifndef INTERPRETE_H
#define INTERPRETE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alu.h"
#include "imprimir.h"

#define TAMANIO_COMANDO 256
#define TAMANIO_LINEA 128

#define DELIMITADOR_ESPACIO ' '
#define DELIMITADOR_COMA ','

#define ERROR_COMANDO_DESCONOCIDO -10
#define ERROR_ARCHIVO_NO_ENCONTRADO -11

#define ERROR_INSTRUCCION_NO_RECONOCIDA -12
#define ERROR_REGISTRO_INVALIDO -13
#define ERROR_CANTIDAD_INCORRECTA_OPERANDOS_O_SINTAXIS -14
#define ERROR_SEPARADOR_INCORRECTO -15
#define ERROR_USO_INCORRECTO_DE_VALORES -16
#define ERROR_DIVISION_POR_CERO -17


static const char REG_AX[] = "Ax";
static const char REG_BX[] = "Bx";
static const char REG_CX[] = "Cx";
static const char REG_DX[] = "Dx";

static const char OP_MOV[] = "MOV";
static const char OP_ADD[] = "ADD";
static const char OP_SUB[] = "SUB";
static const char OP_MUL[] = "MUL";
static const char OP_DIV[] = "DIV";
static const char OP_INC[] = "INC";
static const char OP_DEC[] = "DEC";


/** 
 * @brief Función principal del intérprete que procesa comandos
 * @param comando String con el comando a interpretar
 * @return 0 si debería de continuar el programa, 1 si debería de salir, -1 si dio error
*/
int interprete(char *comando);

/**
 * @brief Función encargada de abrir/leer un archivo
 * @param nombre_archivo String del archivo a leer
 * @return 0 si deberia de continuar el programa y -1 si dio error
 */
int leerArchivo(char *nombre_archivo);

/**
 * @brief Función encargada de verificar que la LINEA sea correcta para el grupo uno (MOV, ADD, SUB, DIV, MUL). 
 * @param tipo_operacion String que indica la operacion a realizar
 * @param operandos String que indica el registro asi como el delimitador y el numero entero
 * @return 0 si deberia de continuar el programa y -1 si dio error
 */
int analizadorGpo1(char *tipo_operacion, char *operandos);

/**
 * @brief Función encargada de verificar que la LINEA sea correcta para el grupo dos (INC, DEC). 
 * @param tipo_operacion String que indica la operacion a realizar
 * @param registro Apuntador que indicar al registro donde se realizará la operación
 * @return 0 si deberia de continuar el programa y -1 si dio error
 */
int analizadorGpo2(char *tipo_operacion, char *registro);

#endif