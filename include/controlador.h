#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "include/globales.h"                       //Contiene la var. globales
#include "include/alu.h"                            //Controla la alu
#include "include/imprimir.h"                       //Imprime
#include "include/interprete.h"                     //Inicializa la estructura buffer
#include "include/comando.h"                        //Resuelve el comando
#include "include/controlador_procesos.h"           //Realiza las funciones de una lista
#include "include/instrucciones.h"                  //Analizadores de Gpo1 y Gpo2
#include "include/validar.h"                        //Valida las cosas :)
#include "include/leer_archivo.h"                   //quien sabe xd
#include "kbhit.h"                                  


#include <sys/time.h>   // Para struct timeval
#include <sys/types.h>  // Para fd_set (en algunos sistemas)
#include <unistd.h>     // Para STDIN_FILENO
#include <sys/select.h> // Para select(), FD_SET, FD_ZERO, etc.


#endif