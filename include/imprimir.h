#ifndef IMPRIMIR_H
#define IMPRIMIR_H

#include "include/controlador.h"
void imprimirError(char *mensaje);
void imprimirEncabezadoEjecucion(void);
void imprimirEncabezadoListos(void);
void imprimirEncabezadoterminado(void);
void imprimirFila(void);
void imprimirFilaConError(char *mensaje_error);
void imprimirTabla(void);

void imprimirFilaPr(PCB *nodo);

#endif