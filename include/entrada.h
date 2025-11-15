#ifndef ENTRADA_H
#define ENTRADA_H

#include "include/controlador.h"

int extraerComando(buffer *bufferC);
void leerComando(char *comando);
void limpiarBuffer(buffer *bufferC);

void reiniciarRegistros();
void guardarContexto(PCB *nodo);
void cargarContexto(PCB *nodo);
void interprete(char *comando);
int kbhito(void);
void killProceso(PCB *arreglo_de_listas[], int valor);

#endif