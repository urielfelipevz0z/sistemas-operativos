#include <stdio.h>
#include <stdlib.h>
#include "alu.h"

#define ANCHO_COLUMNA_ID 4
#define ANCHO_COLUMNA_PC 4
#define ANCHO_COLUMNA_REG 4
#define ANCHO_COLUMNA_PROCESO 12
#define ANCHO_COLUMNA_IR 15
#define ANCHO_COLUMNA_STATUS 25

void imprimirEncabezado(void);
void imprimirEstadoSistema(int mostrar_solo_encabezado);
void imprimirEstadoCompleto(void);
void imprimirError(char *mensaje);