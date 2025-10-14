#ifndef GLOBALES_H
#define GLOBALES_H

#define TAMANIO_COMANDO 100
#define TAMANIO_LINEA 128

#define NUM_REGISTROS 4
#define NUM_OPS_GPO1 5
#define NUM_OPS_GPO2 2
#define SEGUNDOS 1


typedef struct{
    char comandoCompleto[TAMANIO_COMANDO];      //ejecuta a.asm
    char comando[TAMANIO_LINEA];                //ejecuta
    char argumento[TAMANIO_LINEA];              //a.asm
}buffer;

typedef struct pcb{
    int id;
    int pc;
    int ax;
    int bx;
    int cx;
    int dx;
    char ir[16];
    char estado[10];    // Nuevo, Listo, Terminado(Bien o Mal), Bloqueado, Suspendido
    char nombre[30]; //nombre del archivo
    FILE *archivo; //puntero al archivo
    struct pcb *siguiente; //puntero al siguiente PCB
}PCB;

typedef struct ventana{
    WINDOW *ventana[5];
    int update[5]; 
}Ventana;

extern int reg_ax, reg_bx, reg_cx, reg_dx;
extern int reg_pc, reg_id;
extern char reg_proceso[16], reg_ir[16], comando[TAMANIO_COMANDO];

extern buffer *bufferC;
extern PCB *arreglo_de_listas[3];
extern Ventana *ventana;

static const char *const REGISTROS[] = {"Ax", "Bx", "Cx", "Dx"};
static const char *const OPERACIONES_GPO1[] = {"MOV", "ADD", "SUB", "MUL", "DIV"};
static const char *const OPERACIONES_GPO2[] = {"INC", "DEC"};

extern int tiempo;

#endif