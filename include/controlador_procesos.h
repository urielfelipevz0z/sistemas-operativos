#ifndef CONTROLADOR_PROCESOS_H
#define CONTROLADOR_PROCESOS_H

void gestorProcesos(char *argumento, PCB *arreglo_de_listas[]);
PCB *crear(char *proceso);
void insertar(PCB *arreglo_de_listas[], PCB *nuevo);
void manejador();
void eliminar(PCB *arreglo_de_listas[]);
void recorrerListas(PCB *arreglo_de_listas[]);

#endif