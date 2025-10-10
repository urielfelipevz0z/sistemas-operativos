Ahora la impresión debera hacerse en una sola linea. Haciendo uso de la libreria NCURSES

Tendremos que investigar 
curses.h
unistd.h

//esto nos indica que vamos trabajar con una ventana
WINDOW *window=NULL
    window=initscr()        //Inicializamos la ventana
    mvprintw(x,y,"texto")   //coordenasdas en donde queremos que aparezca la ventana 
    refresh()               //tenemos que refrescar la pagina
    endwind()               //Asi como la iniciamos tambien la tenemos que finalizar 
    usleep(100);                 //Se puede utilizar para pausar ejecución 

Podemos utilizar mas funciones de NCURSES si no con estas son mas que suficientes
    //Tambien tenemos que investigar como compilar con NCURSES, por que tenemos que agregar 
    //una bandera a la hora de compilar 

Finalizamos con el modulo 1 ;(

Entregar hoy lo que tenemos hasta el momento en classroom

Fecha de entrega para subir el proyecto completo de hoy en ocho y el priximo viernes asignamos
fecha de entrega

Que entregar dentro del modulo 1
    Documentación del codigo fuente
        Dentro de la Documentación comando para compilar y ejecutar
        Asi como algunas notacion importanto para que el codigo funcione bien