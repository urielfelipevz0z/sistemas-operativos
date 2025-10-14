#ifndef VENTANA_H
#define VENTANA_H

void inicializarVentanas(Ventana *ventana);
void imprimirVentanas(Ventana *ventana);

void ventanaPromt(Ventana *ventana);
void ventanaMensaje(Ventana *ventana);
void ventanaEjecucion(Ventana *ventana);
void ventanaListos(Ventana *ventana);
void ventanaTerminados(Ventana *ventana);


void actualizaVentanas(Ventana *ventan, buffer *bufferCa);
#endif