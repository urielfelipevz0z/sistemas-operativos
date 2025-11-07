#include "include/controlador.h"

//Imprimir el cuadro de mensajes de errores
void imprimirError(char *mensaje){
    werase(ventana->ventana[1]);
    box(ventana->ventana[1], 0, 0);
    mvwprintw(ventana->ventana[1], 1, 1, "Mensaje: %s", mensaje);
    wrefresh(ventana->ventana[1]);
    wmove(ventana->ventana[0], 1, 4);
    wrefresh(ventana->ventana[0]);
}

void imprimirEncabezadoEjecucion(void){
    werase(ventana->ventana[2]);
    box(ventana->ventana[2], 0, 0);
    mvwprintw(ventana->ventana[2], 1, 1, "-----  EJECUCION  -----");
    mvwprintw(ventana->ventana[2],2,1,"%-6s%-6s%-6s%-6s%-6s%-6s%-14s%-21s%s",
           "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Proceso", "IR", "Status");
    mvwprintw(ventana->ventana[2],3,1,"-------------------------------------------------------------------------------");
    wrefresh(ventana->ventana[2]);

}

void imprimirFila(void){
    mvwprintw(ventana->ventana[2],4,1,"%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s",
           reg_id, reg_pc, reg_ax, reg_bx, reg_cx, reg_dx, 
           reg_proceso, reg_ir, "Correcto");
    wrefresh(ventana->ventana[2]);
    usleep(tiempo);
}

void imprimirFilaConError(char *mensaje_error){
    mvwprintw(ventana->ventana[2],4,1,"%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s",
           reg_id, reg_pc, reg_ax, reg_bx, reg_cx, reg_dx, 
           reg_proceso, reg_ir, mensaje_error);
    wrefresh(ventana->ventana[2]);
    usleep(tiempo);
}

void imprimirTabla(void){
    imprimirEncabezadoEjecucion();
    imprimirFila();
}

void imprimirListos(PCB *nodo, int renglon){
    werase(ventana->ventana[3]);
    box(ventana->ventana[3], 0, 0);
    mvwprintw(ventana->ventana[3], 1, 1, "-----  LISTOS  -----");
    mvwprintw(ventana->ventana[3],2,1,"%-6s%-6s%-6s%-6s%-6s%-6s%-14s%-21s%s",
           "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Proceso", "IR", "Status");
    mvwprintw(ventana->ventana[3],3,1,"---------------------------------------");
    mvwprintw(ventana->ventana[3], renglon+4, 1, "%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s",
           nodo->id, nodo->pc, nodo->ax, nodo->bx, nodo->cx, nodo->dx, 
           nodo->nombre, nodo->ir, nodo->estado);
    wrefresh(ventana->ventana[3]);
    usleep(tiempo);
}

void imprimirTerminados(PCB *nodo, int renglon){
    box(ventana->ventana[4], 0, 0);
    mvwprintw(ventana->ventana[4],2,1,"%-6s%-6s%-6s%-6s%-6s%-6s%-14s%-21s%s",
           "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Proceso", "IR", "Status");
    mvwprintw(ventana->ventana[4],3,1,"---------------------------------------");
    mvwprintw(ventana->ventana[4], renglon+4, 1, "%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s",
           nodo->id, nodo->pc, nodo->ax, nodo->bx, nodo->cx, nodo->dx, 
           nodo->nombre, nodo->ir, nodo->estado);
    wrefresh(ventana->ventana[4]);
    usleep(tiempo);
}

void inicializarVentanas(Ventana *ventana){

    ventana->ventana[0] = newwin(3,105,0,0);    //Promt
    ventana->ventana[1] = newwin(3,105,3,0);    //Mensajes de error
    ventana->ventana[2] = newwin(7,105,6,0);    //Lista de Ejecucion
    ventana->ventana[3] = newwin(12,105,13,0);   //Lista de Listos
    ventana->ventana[4] = newwin(12,105,25,0);   //Lista de Terminados
    ventana->update[0] = 1;
    ventana->update[1] = 1;
    ventana->update[2] = 1;
    ventana->update[3] = 1;
    ventana->update[4] = 1;
}

void imprimirVentanas(Ventana *ventana){

    ventanaPromt(ventana);
    ventanaMensaje(ventana);
    ventanaEjecucion(ventana);
    ventanaListos(ventana);
    ventanaTerminados(ventana);
}

void ventanaPromt(Ventana *ventana){
    werase(ventana->ventana[0]);                    //Borrar todo el contenido de la ventana
    box(ventana->ventana[0], 0, 0);                 //Dibujar nuevamente el borde de la ventana
    mvwprintw(ventana->ventana[0], 1, 1, ">> ");    //Imprimir prompt 
    wmove(ventana->ventana[0], 1, 4);
    wrefresh(ventana->ventana[0]);
}

void ventanaMensaje(Ventana *ventana){
    werase(ventana->ventana[1]);
    mvwprintw(ventana->ventana[1], 1, 1, "Mensaje: ");
    box(ventana->ventana[1],0,0);    
    ventana->update[1] = 0;                         //ponemos el estado en ya actualizado
    wrefresh(ventana->ventana[1]);                  //Refresca la ventana para mostrar el borde
}

void ventanaEjecucion(Ventana *ventana){
    werase(ventana->ventana[2]);
    mvwprintw(ventana->ventana[2], 1, 1, "-----  EJECUCION  -----");
    box(ventana->ventana[2],0,0);
    ventana->update[2] = 0;                         //ponemos el estado en ya actualizado
    wrefresh(ventana->ventana[2]);
}

void ventanaListos(Ventana *ventana){
    werase(ventana->ventana[3]);                    //Borrar todo el contenido de la ventana
    mvwprintw(ventana->ventana[3], 1, 1, "-----  LISTOS  -----");
    box(ventana->ventana[3], 0, 0);                 //Dibujar nuevamente el borde de la ventana
    ventana->update[3] = 0;                         
    wrefresh(ventana->ventana[3]);
}

void ventanaTerminados(Ventana *ventana){
    werase(ventana->ventana[4]);                    //Borrar todo el contenido de la ventana
    mvwprintw(ventana->ventana[4], 1, 1, "-----  TERMINADOS  -----");
    box(ventana->ventana[4], 0, 0);                 //Dibujar nuevamente el borde de la ventana
    ventana->update[4] = 0;                         
    wrefresh(ventana->ventana[4]);
}

void actualizaVentanas(Ventana *ventana, buffer *bufferC){
    if(ventana->update[0]){
        //printbuffer(ventana, bufferC);
    }
}



