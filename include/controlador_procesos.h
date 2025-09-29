#ifndef CONTROLADOR_PROCESOS_H
#define CONTROLADOR_PROCESOS_H

gestorProcesos(char *argumento, PCB *listos);
crear(char *proceso);
insertar(char *proceso, PCB *lista);
manejador(PCB *listos);
eliminar(PCB *lista);

#endif