#include "include/controlador.h"


int reg_ax, reg_bx, reg_cx, reg_dx = 0;
int reg_pc, reg_id = 0;
char reg_proceso[16] = "", reg_ir[16] = "";

char comando[TAMANIO_COMANDO] = "";

WINDOW *ventana = NULL;
