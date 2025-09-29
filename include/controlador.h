#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "include/globales.h"                       //Contiene la var. globales
#include "include/alu.h"                            //Controla la alu
#include "include/imprimir.h"                       //Imprime
#include "include/interprete.h"                     //Inicializa la estructura buffer
#include "include/comando.h"                        //Resuelve el comando
#include "include/controlador_procesos.h"           //Realiza las funciones de una lista
#include "include/instrucciones.h"                  //Analizadores de Gpo1 y Gpo2
#include "include/validar.h"                        //Valida las cosas :)
#include "include/leer_archivo.h"                   //quien sabe xd

#endif