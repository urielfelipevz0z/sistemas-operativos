#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "include/controlador.h"


void imprimirError(char *mensaje);
void imprimirDebug(char *mensaje);
void imprimirRecursos(char *mensaje);
void imprimirEncabezadoEjecucion(void);
void imprimirEncabezadoListos(void);
void imprimirEncabezadoterminado(void);
void imprimirFila(void);
void imprimirFilaConError(char *mensaje_error);
void imprimirQuantum(char *mensaje);
void imprimirTabla(void);
void imprimirListos(PCB *nodo, int renglon);
void imprimirTerminados(PCB *nodo, int renglon);

void inicializarVentanas(Ventana *ventana);
void imprimirVentanas(Ventana *ventana);
void ventanaPromt(Ventana *ventana);
void ventanaMensaje(Ventana *ventana);
void ventanaEjecucion(Ventana *ventana);
void ventanaListos(Ventana *ventana);
void ventanaTerminados(Ventana *ventana);
void ventanaNuevos(Ventana *ventana);
void ventanaQuantum(Ventana *ventana);
void ventanaDebug(Ventana *ventana);
void ventanaRecursos(Ventana *ventana);

void actualizaVentanas(Ventana *ventan, buffer *bufferCa);


#endif