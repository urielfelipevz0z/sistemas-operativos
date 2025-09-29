#ifndef CONTROLADOR_PROCESOS_H
#define CONTROLADOR_PROCESOS_H

void gestorProcesos(char *argumento, PCB *arreglo_de_listas[]);
PCB *crear(char *proceso);
void insertar(char *proceso, PCB *arreglo_de_listas[]);
void manejador(PCB *arreglo_de_listas[]);
void eliminar(PCB *arreglo_de_listas[]);

#endif