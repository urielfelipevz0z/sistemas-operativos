#include "include/controlador.h"

PCB *lista_listos = NULL;
PCB *lista_ejecucion = NULL;
PCB *lista_terminados = NULL;

PCB *arreglo_de_listas[3];

void inicializar_arreglo_listas() {
    arreglo_de_listas[0] = lista_listos;
    arreglo_de_listas[1] = lista_ejecucion;
    arreglo_de_listas[2] = lista_terminados;
}


int reg_ax, reg_bx, reg_cx, reg_dx = 0;
int reg_pc, reg_id = 0;
char reg_proceso[16] = "", reg_ir[16] = "";

char comando[TAMANIO_COMANDO] = "";

WINDOW *ventana = NULL;