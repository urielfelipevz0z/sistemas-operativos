#include <ncurses.h>
#include <stdlib.h>

typedef struct ventana{
    WINDOW *ventana[5];
}Ventana;

int main(){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    
    Ventana *ventana = malloc(sizeof(ventana));
    if(!ventana){
        endwin();
        return 1;
    }

    ventana->ventana[0] = newwin(5,40,0,0);
    if(!ventana->ventana[0]){
        endwin();
            printf("Error\n");
            exit(1);
    }

    refresh();
    box(ventana->ventana[0],0,0);
    mvwprintw(ventana->ventana[0],2,2,">> ");
    wrefresh(ventana->ventana[0]);
    
    getch();
    delwin(ventana->ventana[0]);
    free(ventana);
    endwin();
    return 0;
}
