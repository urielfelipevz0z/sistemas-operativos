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

#define TAMANIO_COMANDO 256
#define TAMANIO_LINEA 128

static const char *const REGISTROS[] = {"Ax", "Bx", "Cx", "Dx"};
static const char *const OPERACIONES_GPO1[] = {"MOV", "ADD", "SUB", "MUL", "DIV"};
static const char *const OPERACIONES_GPO2[] = {"INC", "DEC"};

#define NUM_REGISTROS 4
#define NUM_OPS_GPO1 5
#define NUM_OPS_GPO2 2

int interprete(char *comando);
int leerArchivo(char *nombre_archivo);
int analizadorGpo1(char *tipo_operacion, char *operandos);
int analizadorGpo2(char *tipo_operacion, char *registro);
int validarRegistro(const char *registro);
int tipoOperacion(const char *operacion);

#endif