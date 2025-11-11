#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include "include/cpu.h"
// #include "include/proceso.h"


#include "include/globales.h"                       //Contiene la var. globales

#include "include/proceso.h"
#include "include/interfaz.h"
#include "include/entrada.h"

#include <sys/time.h>   // Para struct timeval
#include <sys/types.h>  // Para fd_set (en algunos sistemas)
#include <unistd.h>     // Para STDIN_FILENO
#include <sys/select.h> // Para select(), FD_SET, FD_ZERO, etc.


#endif