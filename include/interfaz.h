#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "include/controlador.h"


void imprimirError(char *mensaje);
void imprimirDebug(char *mensaje);
void imprimirRecursos(char *mensaje);
void imprimirEncabezadoEjecucion(void);
void imprimirFila(void);
void imprimirFilaConError(char *mensaje_error);
void imprimirQuantum(char *mensaje);
void imprimirTabla(void);

void inicializarVentanas(Ventana *ventana);
void imprimirVentanas(Ventana *ventana);
void ventanaPromt(Ventana *ventana);
void ventanaMensaje(Ventana *ventana);
void ventanaEjecucion(Ventana *ventana);
void ventanaListos(Ventana *ventana);
void ventanaTerminados(Ventana *ventana);
void ventanaNuevos(Ventana *ventana);
void ventanaQuantum(Ventana *ventana);
void ventanaBloqueados(Ventana *ventana);
void ventanaRecursos(Ventana *ventana);
void ventanaDebug(Ventana *ventana);

#endif