#ifndef GLOBALES_H
#define GLOBALES_H

#define TAMANIO_COMANDO 256
#define TAMANIO_LINEA 128

#define NUM_REGISTROS 4
#define NUM_OPS_GPO1 5
#define NUM_OPS_GPO2 2

extern int reg_ax, reg_bx, reg_cx, reg_dx = 0;
extern int reg_pc, reg_id = 0;
extern char reg_proceso[16] = "",reg_ir[16] = "";

static const char *const REGISTROS[] = {"Ax", "Bx", "Cx", "Dx"};
static const char *const OPERACIONES_GPO1[] = {"MOV", "ADD", "SUB", "MUL", "DIV"};
static const char *const OPERACIONES_GPO2[] = {"INC", "DEC"};

typedef struct{
    char comandoCompleto[TAMANIO_COMANDO];      //ejecuta a.asm
    char comando[TAMANIO_LINEA];                //ejecuta
    char argumento[TAMANIO_LINEA];              //a.asm
}buffer;

#endif