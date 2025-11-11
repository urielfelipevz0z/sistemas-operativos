#include "include/controlador.h"

PCB *lista_listos = NULL;
PCB *lista_ejecucion = NULL;
PCB *lista_terminados = NULL;

PCB *arreglo_de_listas[4];

PCB *aux;

void inicializar_arreglo_listas() {
    arreglo_de_listas[0] = NULL;
    arreglo_de_listas[1] = NULL;
    arreglo_de_listas[2] = NULL;
    arreglo_de_listas[3] = NULL;
}

int reg_ax, reg_bx, reg_cx, reg_dx = 0, Q = 0;
int reg_pc, reg_id = 0;
char reg_proceso[16] = "", reg_ir[16] = "", reg_estado[REG_ESTADO_TAM] = "";
int bandera = 0, cant_procesos = 0;
char desc[256] = "";
int id_listos = 0;


char comando[TAMANIO_COMANDO] = "";
buffer *bufferC = NULL;
Ventana *ventana = NULL;

 int tiempo = 1000000 * SEGUNDOS;
// int tiempo = 500000 * SEGUNDOS;
// int tiempo = 100000 * SEGUNDOS;