#ifndef CPU_H
#define CPU_H

#include "include/controlador.h"

int aluGpo1(char *operacion, char *registro, int *valor);
int aluGpo2(char *operacion, char *registro);

int analizadorGpo1(char *tipo_operacion, char *operandos);
int analizadorGpo2(char *tipo_operacion, char *registro);

int validarRegistro(const char *registro);
int tipoOperacion(const char *operacion);
int esNumeroValido(const char *str);
int *obtenerRegistro(const char *nombre);
int comprobarAsm(char *proceso);

#endif