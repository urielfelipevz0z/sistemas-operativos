#include "include/controlador.h"

void gestorProcesos(char *argumento, PCB *arreglo_de_listas[]){
    PCB *nuevo;
    char arg_copia[256];
    char *archivos[50];
    int banderaGuardados = 0;

    strcpy(arg_copia,argumento);  //a.asm b.asm si.asm
    char *proceso = strtok(arg_copia, " "); //a.asm
    
    for(int i = 0; proceso != NULL; i++){
        archivos[i] = proceso;              // [a.asm, b.asm, si.asm] Guardar
        proceso = strtok(NULL, " ");
        banderaGuardados++;
    }

    for(int i = 0; i < banderaGuardados; i++){
        if(comprobarAsm(archivos[i]) == 0){
            nuevo = crear(archivos[i]);
            insertar(&(arreglo_de_listas[0]), nuevo);       //Se guardan todos los nodos en lista_listos
        }
    }
    //manejador(arreglo_de_listas);
}

PCB *crear(char *proceso){
    PCB *nuevo = (PCB *)malloc(sizeof(PCB));
    if(nuevo == NULL){
        imprimirError("No se ha podido crear el proceso\n");
        return NULL;
    }
    
    nuevo->archivo = fopen(proceso, "r");
    if (nuevo->archivo == NULL) {
        free(nuevo);
        return NULL;
    }
    id_listos++;
    nuevo->id = id_listos;
    nuevo->pc = 1;
    nuevo->ax = 0;
    nuevo->bx = 0;
    nuevo->cx = 0;
    nuevo->dx = 0;
    
    strcpy(nuevo->ir, "");
    strcpy(nuevo->estado, "");
    strcpy(nuevo->nombre, proceso); //a.asm
    
    nuevo->archivo = fopen(proceso, "r");
    nuevo->siguiente = NULL;
    return nuevo;
}

void insertar(PCB *arreglo_de_listas[], PCB *nuevo){
    
    PCB *aux;
    
    if(arreglo_de_listas[0] == NULL){
       arreglo_de_listas[0] = nuevo;
    }
    else{
        aux = arreglo_de_listas[0];
        while(aux->siguiente != NULL){ //Recorre la lista hasta el final 
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
    }
}

void manejador(){
        if(arreglo_de_listas[0] != NULL){
        recorrerListas(&(arreglo_de_listas[0]));
        //imprimir lista de listos
        // while (arreglo_de_listas[0] != NULL){ 
        
        if(arreglo_de_listas[1] == NULL){
            aux = arreglo_de_listas[0]; 
            arreglo_de_listas[0] = aux->siguiente;
            aux->siguiente = NULL;
            insertar(&(arreglo_de_listas[1]), aux); //Se mueve el 1er nodo de listos a ejecución 
            recorrerListas(&(arreglo_de_listas[0]));
            strcpy(reg_proceso, aux[0].nombre); 
            if (leerArchivo(&aux[0]) == -1){ //a.asm 
                reg_id--;
                strcpy(reg_proceso, ""); 
                bandera = 0; //reinicio de la bandera
            } 
        }
        else{
            if(ejecutarInstruccion(arreglo_de_listas[1]->archivo)){
                if(bandera == 0){
                    sprintf(desc, "[WARNING] Finalizo pero no se encontró la instruccion END en el archivo %s", reg_proceso);
                    imprimirError(desc);
                }
                igualarRegistros(&aux[0]);
                arreglo_de_listas[1] = NULL;
                insertar(&(arreglo_de_listas[2]), aux);   //Se mueve el nodo de ejecución a terminados 
                recorrerListas(&(arreglo_de_listas[0]));
            }
        }      
    }
    if(arreglo_de_listas[1] != NULL){
        if(ejecutarInstruccion(arreglo_de_listas[1]->archivo)){
                igualarRegistros(&aux[0]); 
                arreglo_de_listas[1] = NULL;
                insertar(&(arreglo_de_listas[2]), aux);   //Se mueve el nodo de ejecución a terminados 
                recorrerListas(&(arreglo_de_listas[0]));
            if(bandera == 0){
                sprintf(desc, "[WARNING] Finalizo pero no se encontró la instruccion END en el archivo %s", reg_proceso);
                imprimirError(desc);
            }
        imprimirEncabezadoEjecucion();            
        }
    }
}

void eliminar(PCB *arreglo_de_listas[]){
    PCB *aux;
    PCB *lista = arreglo_de_listas[0];
    
    if(lista == NULL){
        imprimirError("No hay procesos en la lista\n");
    }
    else{
        while(lista != NULL){
            aux = lista;
            lista = lista->siguiente;
            free(aux);
        }
        arreglo_de_listas[0] = NULL;
    }
}

void recorrerListas(PCB *arreglo_de_listas[]){
    PCB *aux;
    PCB *lista;
    int j;

    for(int i = 0; i < 3; i++){
        j = 0;
        if(i == 0){ //lista de listos
            lista = arreglo_de_listas[i];
            // Limpia y dibuja la ventana solo una vez
            werase(ventana->ventana[3]);
            box(ventana->ventana[3], 0, 0);
            mvwprintw(ventana->ventana[3], 1, 1, "-----  LISTOS  -----");
            mvwprintw(ventana->ventana[3],2,1,"%-6s%-6s%-6s%-6s%-6s%-6s%-14s%-21s%s",
                "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Proceso", "IR", "Status");
            mvwprintw(ventana->ventana[3],3,1,"---------------------------------------");
            while(lista != NULL){
                aux = lista;
                lista = lista->siguiente;
                mvwprintw(ventana->ventana[3], j+4, 1, "%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s",
                    aux->id, aux->pc, aux->ax, aux->bx, aux->cx, aux->dx,
                    aux->nombre, "-", "-");
                j++;
            }
            wrefresh(ventana->ventana[3]);
        }
        else if(i == 2){    //Lista de terminados
            lista = arreglo_de_listas[i];
            box(ventana->ventana[4], 0, 0);
            mvwprintw(ventana->ventana[4],2,1,"%-6s%-6s%-6s%-6s%-6s%-6s%-14s%-21s%s",
                "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Proceso", "IR", "Status");
            mvwprintw(ventana->ventana[4],3,1,"---------------------------------------");
            j = 0;
            while(lista != NULL){
                aux = lista;
                lista = lista->siguiente;
                mvwprintw(ventana->ventana[4], j+4, 1, "%-6d%-6d%-6d%-6d%-6d%-6d%-14s%-21s%s",
                    aux->id, aux->pc, aux->ax, aux->bx, aux->cx, aux->dx,
                    aux->nombre, aux->ir, aux->estado);
                j++;
            }
            wrefresh(ventana->ventana[4]);
        }
    }
}

int leerArchivo(PCB *proceso){  //a.asm
    reiniciarRegistros();
    reg_id++;
    FILE *archivo = proceso->archivo;
    if (archivo == NULL){
        imprimirError("Archivo no encontrado");
        return -1;
    }
    if(ejecutarInstruccion(archivo)){
        fclose(archivo);
    }
    
    return 0;
}

int ejecutarInstruccion(FILE *archivo){
    char linea[TAMANIO_LINEA];

    imprimirTabla();
    if (fgets(linea, sizeof(linea), archivo) != NULL){   //linea = MOV Ax,7 o INC Ax
        bandera = 0;
        linea[strcspn(linea, "\n")] = 0;
        
        strcpy(reg_ir, linea);
        
        char copia[TAMANIO_LINEA];
        strcpy(copia, linea);
        char *token = strtok(copia, " ");       //token = MOV
        
        if (token == NULL){
            return 0;
        }

        //END
        if (strcmp("END", token) == 0){
            bandera = 1;
            imprimirError(desc);
            strcpy(reg_estado, "CORRECTO");
            // fclose(archivo);
            reg_pc++;
            return 1;
        }
        
        int tipo_op = tipoOperacion(token);     //1 o 2
        
        char *operandos = strtok(NULL, "");     //Ax,7
        if (operandos == NULL){
            imprimirFilaConError("Cantidad incorrecta de operandos");
            return 0;
        }

        if (tipo_op == 1){
            if(analizadorGpo1(token, operandos)){ //MOV y Ax,7
                bandera = 1;
                strcpy(reg_estado, "ERROR DE SINTAXIS");
                reg_pc++;
                return 1;
            }  
        } else if (tipo_op == 2){
            if(analizadorGpo2(token, operandos)){ 
                bandera = 1;
                strcpy(reg_estado, "ERROR DE SINTAXIS");
                reg_pc++;
                return 1;
            }  
        } else{
            imprimirFilaConError("Instrucción no reconocida");
            return 0;
        }
    }
    else{
        return 1;
    }
}









