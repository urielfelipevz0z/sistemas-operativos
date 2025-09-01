#ifndef ALU_H
#define ALU_H

#include <stdio.h>
#include <string.h>
#include "globales.h"

int aluGpo1(char *operacion, char *registro, int *valor);
int aluGpo2(char *operacion, char *registro);
int* obtenerRegistro(const char *nombre);

#endif