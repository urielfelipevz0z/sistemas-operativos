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
            insertar(&(arreglo_de_listas[3]), nuevo);       //Se guardan todos los nodos en lista de nuevos
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
    
    FILE *f = fopen(proceso, "r");
    if (f == NULL) {
        free(nuevo);
        return NULL;
    }
    nuevo->archivo = f;

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
    
    // Generar prioridad aleatoria entre 1 y 4
    nuevo->prioridad = (rand() % 4) + 1;
    
    //nuevo->archivo = fopen(proceso, "r"); se abria el doc dos veces xd
    nuevo->siguiente = NULL;
    return nuevo;
}

void insertar(PCB *arreglo_de_listas[], PCB *nuevo){
    
    PCB *aux;
    PCB *anterior;
    
    if(arreglo_de_listas[0] == NULL){
       arreglo_de_listas[0] = nuevo;
    }
    else{
        aux = arreglo_de_listas[0];
        anterior = NULL;
        
        // Buscar la posición correcta según prioridad
        while(aux != NULL && aux->prioridad <= nuevo->prioridad){
            anterior = aux;
            aux = aux->siguiente;
        }
        
        // Insertar al inicio (mayor prioridad que el primero)
        if(anterior == NULL){
            nuevo->siguiente = arreglo_de_listas[0];
            arreglo_de_listas[0] = nuevo;
        }
        // Insertar en medio o al final
        else{
            anterior->siguiente = nuevo;
            nuevo->siguiente = aux;
        }
    }
    
}

int manejador(){
    if(arreglo_de_listas[0] != NULL){       //Hay algo en listos?
    recorrerListas(&(arreglo_de_listas[0]));

        if(arreglo_de_listas[1] == NULL){       //Si no hay nada en ejecución
            aux = arreglo_de_listas[0];         //cargar el 1er nodo de listos 
            arreglo_de_listas[0] = aux->siguiente;
            aux->siguiente = NULL;
            insertar(&(arreglo_de_listas[1]), aux); //Se mueve el 1er nodo de listos a ejecución 
            cargarContexto(aux);                    //Para todos los casos se carga contexto
            recorrerListas(&(arreglo_de_listas[0]));
            strcpy(reg_proceso, aux[0].nombre); 

            int res = leerArchivo(aux);
            if(res == -1){      //si no existe el archivo a.asm se acaba la funcion pq son puros if anidados
                strcpy(reg_proceso, "");
                bandera = 0;
            }
            else if(res == 1){      //existe el archivo a.asm pero termino al cargarse en ejecucion (evita el problea de archivos con 4*n+1 lineas)
                aux = arreglo_de_listas[1];
                arreglo_de_listas[1] = NULL;
                guardarContexto(aux);   //se extrae el nodo y se guarda el valor de los registros
                if (aux->archivo != NULL){  //se cierra
                    fclose(aux->archivo);
                    aux->archivo = NULL;
                }
                aux->siguiente = NULL;  
                insertar(&(arreglo_de_listas[2]), aux); //Se manda a terminados
                cant_procesos--;
                recorrerListas(&(arreglo_de_listas[0]));
                if(bandera == 0){
                    sprintf(desc, "[WARNING] Finalizo pero no se encontró la instruccion END en el archivo %s", reg_proceso);
                    imprimirError(desc);
                    strcpy(reg_estado, "ERROR");
                }
                imprimirEncabezadoEjecucion();
                return 1;
            }

        }
        else{       //Hay algo en ejecucion
            if(ejecutarInstruccion(arreglo_de_listas[1]->archivo)){
                aux = arreglo_de_listas[1];
                arreglo_de_listas[1] = NULL;
                guardarContexto(&aux[0]);
                if (aux->archivo != NULL){
                    fclose(aux->archivo);
                    aux->archivo = NULL;
                }
                aux->siguiente = NULL;
                insertar(&(arreglo_de_listas[2]), aux);   //Se mueve el nodo de ejecución a terminados 
                cant_procesos--;
                recorrerListas(&(arreglo_de_listas[0]));
                if(bandera == 0){
                    sprintf(desc, "[WARNING] Finalizo pero no se encontró la instruccion END en el archivo %s", reg_proceso);
                    imprimirError(desc);
                    strcpy(reg_estado, "ERROR");
                }
                imprimirEncabezadoEjecucion();
                return 1;   //Si se termina el proceso termina el ciclo FOR Q
            }
        }      
    }
    else if(arreglo_de_listas[1] != NULL){       //Entra cuando no hay nada en listos pero si en ejecución
        if(ejecutarInstruccion(arreglo_de_listas[1]->archivo)){
            aux = arreglo_de_listas[1];
            arreglo_de_listas[1] = NULL;
            guardarContexto(&aux[0]); 
            if (aux->archivo != NULL){
            fclose(aux->archivo);
            aux->archivo = NULL;
            }
            aux->siguiente = NULL;
            insertar(&(arreglo_de_listas[2]), aux);   //Se mueve el nodo de ejecución a terminados 
            cant_procesos--;
            recorrerListas(&(arreglo_de_listas[0]));
            if(bandera == 0){
                sprintf(desc, "[WARNING] Finalizo pero no se encontró la instruccion END en el archivo %s", reg_proceso);
                imprimirError(desc);
                strcpy(reg_estado, "ERROR");
            }
            imprimirEncabezadoEjecucion();            
            return 1;       //Si se termina el proceso termina el ciclo FOR Q
        }
    }
    return 0;
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

    for(int i = 0; i < 4; i++){
        j = 0;
        if(i == 0){ //lista de listos
            lista = arreglo_de_listas[i];
            // Limpia y dibuja la ventana solo una vez
            werase(ventana->ventana[3]);
            box(ventana->ventana[3], 0, 0);
            mvwprintw(ventana->ventana[3], 1, 1, "-----  LISTOS  -----");
            mvwprintw(ventana->ventana[3],2,1,"%-5s %-5s %-5s %-5s %-5s %-5s %-7s %-10s %-10s %-10s",
                "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Priori", "Proceso", "IR", "Status");
            mvwprintw(ventana->ventana[3],3,1,"----------------------------------------------------------------------------------");
            while(lista != NULL){
                aux = lista;
                lista = lista->siguiente;
                mvwprintw(ventana->ventana[3], j+4, 1, "%-5d %-5d %-5d %-5d %-5d %-5d %-7d %-10s %-10s %-10s",
                    aux->id, aux->pc, aux->ax, aux->bx, aux->cx, aux->dx, aux->prioridad,
                    aux->nombre, aux->ir, aux->estado);
                j++;
            }
            wrefresh(ventana->ventana[3]);
        }
        else if(i == 2){    //Lista de terminados
            lista = arreglo_de_listas[i];
            box(ventana->ventana[4], 0, 0);
            mvwprintw(ventana->ventana[4],2,1,"%-5s %-5s %-5s %-5s %-5s %-5s %-7s %-10s %-10s %-10s",
                "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Priori", "Proceso", "IR", "Status");
            mvwprintw(ventana->ventana[4],3,1,"----------------------------------------------------------------------------------");
            j = 0;
            while(lista != NULL){
                aux = lista;
                lista = lista->siguiente;
                mvwprintw(ventana->ventana[4], j+4, 1, "%-5d %-5d %-5d %-5d %-5d %-5d %-7d %-10s %-10s %-10s",
                    aux->id, aux->pc, aux->ax, aux->bx, aux->cx, aux->dx, aux->prioridad,
                    aux->nombre, aux->ir, aux->estado);
                j++;
            }
            wrefresh(ventana->ventana[4]);
        }
        else if(i == 3){    //Lista de nuevos
            lista = arreglo_de_listas[i];
            werase(ventana->ventana[5]);
            box(ventana->ventana[5], 0, 0);
            mvwprintw(ventana->ventana[5], 1, 1, "-----  NUEVOS  -----");
            mvwprintw(ventana->ventana[5],2,1,"%-10s %-17s %-15s %-15s",
                "ID", "Prioridad", "Proceso", "Status");
            mvwprintw(ventana->ventana[5],3,1,"--------------------------------------------------------------");
            j = 0;
            while(lista != NULL){
                aux = lista;
                lista = lista->siguiente;
                mvwprintw(ventana->ventana[5], j+4, 1, "%-10d %-17d %-15s %-15s",
                    aux->id, aux->prioridad, aux->nombre, strcpy(aux->estado,"NUEVO"));
                j++;
                strcpy(aux->estado,"");
            }
            wrefresh(ventana->ventana[5]);
        }
    }
}

int leerArchivo(PCB *proceso){  //a.asm
    //reiniciarRegistros();
    // reg_id++;
    if (proceso == NULL || proceso->archivo == NULL){
        imprimirError("Archivo no encontrado");
        return -1;
    }
    FILE *f = proceso->archivo;
    if(ejecutarInstruccion(f)){
        // fclose(f);
        // proceso->archivo = NULL;
        return 1;
    }
    return 0;
}

int ejecutarInstruccion(FILE *archivo){
    char linea[TAMANIO_LINEA];
    if(archivo == NULL){
        return 1;
    }

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
            sprintf(desc, "Finalizo se encontró la instruccion END en el archivo %s", reg_proceso);
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
            strcpy(reg_estado, "ERROR DE SINTAXIS");
            return -1;
        }

        if (tipo_op == 1){
            if(analizadorGpo1(token, operandos)){ //MOV y Ax,7
                bandera = 1;
                strcpy(reg_estado, "ERROR DE SINTAXIS");
                reg_pc++;
                return -1;
            }  
        } else if (tipo_op == 2){
            if(analizadorGpo2(token, operandos)){ 
                bandera = 1;
                strcpy(reg_estado, "ERROR DE SINTAXIS");
                reg_pc++;
                return -1;
            }  
        } else{
            imprimirFilaConError("Instrucción no reconocida");
            return -1;
        }
        return 0;
    }
    else{
        return 1;
    }
}

int quantum(){
    PCB *aux;
    if(planificadorLP()){
        return 0;
    }
    for(Q = 0; Q < 4 ;Q++){
        if (kbhito()) {
           leerComando(comando);   ////solo llamas si hay entrada
        }
        sprintf(desc, " %d/4 del proceso: %s", Q+1, reg_proceso);
        imprimirQuantum(desc);

        if(manejador() == 1){
            break;
        }
    }
    if(arreglo_de_listas[1] != NULL){ //Se termino el Q, pero aun no se termina el archivo se guarda como pendiente
        aux = arreglo_de_listas[1];
        strcpy(reg_estado, "PENDIENTE");
        guardarContexto(aux);    
        aux->siguiente = NULL; 
        insertar(&(arreglo_de_listas[0]), aux); //Se regresa el nodo actual a la lista de listos.
        recorrerListas(&(arreglo_de_listas[0]));
        arreglo_de_listas[1] = NULL;
    }

    return 0;
}

int planificadorLP(){
    PCB *aux;
    int mov = 0;
    while(arreglo_de_listas[3] != NULL && cant_procesos < 3){   //Si hay algo en Nuevos y espacio en listos Guardar en Listos
        aux = arreglo_de_listas[3];         
        arreglo_de_listas[3] = aux->siguiente;
        aux->siguiente = NULL;
        insertar(&(arreglo_de_listas[0]), aux); //Se mueve el 1er nodo de nuevos a ejecucion
        cant_procesos++;
        mov = 1;
    }
    if(mov){
        recorrerListas(&(arreglo_de_listas[0]));
    }
    return mov;
}