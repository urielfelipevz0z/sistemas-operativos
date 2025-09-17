#ifndef COMANDO_H
#define COMANDO_H

#include "include/controlador.h"

int extraerComando(buffer *bufferC);
void leerComando(char *comando);
void limpiarBuffer(buffer *bufferC);

#endif // COMANDO_H