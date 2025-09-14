#ifndef INTERPRETE_H
#define INTERPRETE_H

#include "controlador.h"

int interprete(char *comando);
int leerArchivo(char *nombre_archivo);
void analizadorGpo1(char *tipo_operacion, char *operandos);
void analizadorGpo2(char *tipo_operacion, char *registro);
int validarRegistro(const char *registro);
int tipoOperacion(const char *operacion);
int esNumeroValido(const char *str);

#endif