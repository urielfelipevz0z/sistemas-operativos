#ifndef IMPRIMIR_H
#define IMPRIMIR_H

#include "include/controlador.h"

void imprimirEncabezado(void);
void imprimirFila(void);
void imprimirFilaConError(char *mensaje_error);
void imprimirTabla(void);
void imprimirError(char *mensaje);
void imprimirFilaPr(PCB *nodo);

#endif