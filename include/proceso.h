#ifndef PROCESO_H
#define PROCESO_H

#include "include/controlador.h"

void gestorProcesos(char *argumento, PCB *arreglo_de_listas[]);
PCB *crear(char *proceso);
void insertar(PCB *arreglo_de_listas[], PCB *nuevo);
void manejador();
void eliminar(PCB *arreglo_de_listas[]);
void recorrerListas(PCB *arreglo_de_listas[]);

int leerArchivo(PCB *proceso);
int ejecutarInstruccion(FILE *archivo);

#endif