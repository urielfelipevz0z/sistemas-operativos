/**
 * @file alu.h
 * @brief Header para el módulo ALU
 * @author Equipo: Los sistématicos
 * @date 2025
 */

#ifndef ALU_H
#define ALU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globales.h"

/**
 * @brief Función encargada de realizar las operaciones (MOV, ADD, SUB, DIV, MUL) 
 * @param tipo_operacion string que indica la operacion a realizar
 * @param registro Apuntador que indicar al registro donde se realizará la operación
 * @param dato Numero entero con el que se haran las operaciones
 * @return 0 si deberia de continuar el programa y -1 si dio error
 */
int aluGpo1(char *tipo_operacion, char *registro, int *dato);


/**
 * @brief Función encargada de realizar las operacines (INC, DEC) 
 * @param tipo_operacion string que indica la operacion a realizar
 * @param registro apuntador que indicar al registro donde se realizará la operación
 * @return 0 si deberia de continuar el programa y -1 si dio error
 */
int aluGpo2(char *tipo_operacion, char *registro);

#endif