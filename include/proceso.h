#ifndef PROCESO_H
#define PROCESO_H

#include "include/controlador.h"

void gestorProcesos(char *argumento, PCB *arreglo_de_listas[]);
PCB *crear(char *proceso);
void insertar(PCB *arreglo_de_listas[], PCB *nuevo);
int manejador();
void eliminar(PCB *arreglo_de_listas[]);
void recorrerListas(PCB *arreglo_de_listas[]);

int leerArchivo(PCB *proceso);
int Max(PCB *proceso);
int MaxRecursos(PCB *proceso);
int Get(char *linea);
void liberarRecursos(PCB *proceso);


int ejecutarInstruccion(FILE *archivo);

void insertarPrioridad(PCB *arreglo_de_listas[],PCB *nuevo);
int quantum();
int planificadorLP();
int planificadorMP();

#endif