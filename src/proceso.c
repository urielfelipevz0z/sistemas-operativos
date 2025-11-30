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
    
    // Inicializar recursos
    nuevo->RMax[0] = 0;
    nuevo->RMax[1] = 0;
    nuevo->RMax[2] = 0;
    nuevo->RAsig[0] = 0;
    nuevo->RAsig[1] = 0;
    nuevo->RAsig[2] = 0;
    nuevo->RGet[0] = 0;
    nuevo->RGet[1] = 0;
    nuevo->RGet[2] = 0;
    
    strcpy(nuevo->ir, "");
    strcpy(nuevo->estado, "");
    strcpy(nuevo->nombre, proceso); //a.asm
    
    // Generar prioridad aleatoria entre 1 y 4
    nuevo->prioridad = (rand() % 4) + 1;
    
    //nuevo->archivo = fopen(proceso, "r"); se abria el doc dos veces xd
    nuevo->siguiente = NULL;
    return nuevo;
}

void insertarPrioridad(PCB *arreglo_de_listas[], PCB *nuevo){
    
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

void liberarRecursos(PCB *proceso){
    
    recursos[0] += proceso->RAsig[0];
    recursos[1] += proceso->RAsig[1];
    recursos[2] += proceso->RAsig[2];
    
    proceso->RAsig[0] = 0;
    proceso->RAsig[1] = 0;
    proceso->RAsig[2] = 0;
    
    // Después de liberar recursos, revisar si se pueden desbloquear procesos
    planificadorMP();
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
                liberarRecursos(aux);   //Liberar recursos antes de terminar
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
            int res = ejecutarInstruccion(arreglo_de_listas[1]->archivo);
            if(res == 1){
                // Proceso terminó
                aux = arreglo_de_listas[1];
                arreglo_de_listas[1] = NULL;
                guardarContexto(&aux[0]);
                if (aux->archivo != NULL){
                    fclose(aux->archivo);
                    aux->archivo = NULL;
                }
                aux->siguiente = NULL;
                liberarRecursos(aux);   //Liberar recursos antes de terminar
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
            } else if(res == 2){
                // Proceso bloqueado por recursos
                aux = arreglo_de_listas[1];
                arreglo_de_listas[1] = NULL;
                guardarContexto(&aux[0]);
                aux->siguiente = NULL;
                insertar(&(arreglo_de_listas[4]), aux);   //Se mueve a bloqueados
                recorrerListas(&(arreglo_de_listas[0]));
                imprimirEncabezadoEjecucion();
                return 1;   //Termina el ciclo FOR Q
            }
        }      
    }
    else if(arreglo_de_listas[1] != NULL){       //Entra cuando no hay nada en listos pero si en ejecución
        int res = ejecutarInstruccion(arreglo_de_listas[1]->archivo);
        if(res == 1){
            aux = arreglo_de_listas[1];
            arreglo_de_listas[1] = NULL;
            guardarContexto(&aux[0]); 
            if (aux->archivo != NULL){
            fclose(aux->archivo);
            aux->archivo = NULL;
            }
            aux->siguiente = NULL;
            liberarRecursos(aux);   //Liberar recursos antes de terminar
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
        } else if(res == 2){
            // Proceso bloqueado por recursos
            aux = arreglo_de_listas[1];
            arreglo_de_listas[1] = NULL;
            guardarContexto(&aux[0]);
            aux->siguiente = NULL;
            insertar(&(arreglo_de_listas[4]), aux);   //Se mueve a bloqueados
            recorrerListas(&(arreglo_de_listas[0]));
            imprimirEncabezadoEjecucion();
            return 1;       //Termina el ciclo FOR Q
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

    for(int i = 0; i < 5; i++){
        j = 0;
        if(i == 0){ //lista de listos (Ventana 87 chars)
            lista = arreglo_de_listas[i];
            werase(ventana->ventana[3]);
            box(ventana->ventana[3], 0, 0);
            mvwprintw(ventana->ventana[3], 1, 1, "-----  LISTOS  -----");
            mvwprintw(ventana->ventana[3],2,1,"%-3s %-3s %-4s %-4s %-4s %-4s %-5s %-12s %-12s %-18s",
                "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Prior", "Proceso", "IR", "Status");
            mvwprintw(ventana->ventana[3],3,1,"--------------------------------------------------------------------------------");
            while(lista != NULL){
                aux = lista;
                lista = lista->siguiente;
                mvwprintw(ventana->ventana[3], j+4, 1, "%-3d %-3d %-4d %-4d %-4d %-4d %-5d %-12s %-12s %-18s",
                    aux->id, aux->pc, aux->ax, aux->bx, aux->cx, aux->dx, aux->prioridad,
                    aux->nombre, aux->ir, aux->estado);
                j++;
            }
            wrefresh(ventana->ventana[3]);
        }
        else if(i == 2){    //Lista de terminados (Ventana 87 chars)
            lista = arreglo_de_listas[i];
            werase(ventana->ventana[4]);
            box(ventana->ventana[4], 0, 0);
            mvwprintw(ventana->ventana[4], 1, 1, "----- TERMINADOS -----");
            mvwprintw(ventana->ventana[4],2,1,"%-3s %-3s %-4s %-4s %-4s %-4s %-5s %-12s %-12s %-18s",
                "ID", "PC", "Ax", "Bx", "Cx", "Dx", "Prior", "Proceso", "IR", "Status");
            mvwprintw(ventana->ventana[4],3,1,"--------------------------------------------------------------------------------");
            j = 0;
            while(lista != NULL){
                aux = lista;
                lista = lista->siguiente;
                mvwprintw(ventana->ventana[4], j+4, 1, "%-3d %-3d %-4d %-4d %-4d %-4d %-5d %-12s %-12s %-18s",
                    aux->id, aux->pc, aux->ax, aux->bx, aux->cx, aux->dx, aux->prioridad,
                    aux->nombre, aux->ir, aux->estado);
                j++;
            }
            wrefresh(ventana->ventana[4]);
        }
        else if(i == 3){    //Lista de nuevos (Ventana 65 chars - solo datos relevantes)
            lista = arreglo_de_listas[i];
            werase(ventana->ventana[5]);
            box(ventana->ventana[5], 0, 0);
            mvwprintw(ventana->ventana[5], 1, 1, "-----  NUEVOS  -----");
            mvwprintw(ventana->ventana[5],2,1,"%-4s %-6s %-15s %-10s %-18s",
                "ID", "Prior", "Proceso", "RMax", "Status");
            mvwprintw(ventana->ventana[5],3,1,"-------------------------------------------------------------");
            j = 0;
            while(lista != NULL){
                aux = lista;
                lista = lista->siguiente;
                char rmax[12];
                sprintf(rmax, "%d,%d,%d", aux->RMax[0], aux->RMax[1], aux->RMax[2]);
                mvwprintw(ventana->ventana[5], j+4, 1, "%-4d %-6d %-15s %-10s %-18s",
                    aux->id, aux->prioridad, aux->nombre, rmax, "NUEVO");
                j++;
            }
            wrefresh(ventana->ventana[5]);
        }
        else if(i == 4){    //Lista de bloqueados (Ventana 65 chars - datos relevantes)
            lista = arreglo_de_listas[i];
            werase(ventana->ventana[7]);
            box(ventana->ventana[7], 0, 0);
            mvwprintw(ventana->ventana[7], 1, 1, "----- BLOQUEADOS -----");
            mvwprintw(ventana->ventana[7],2,1,"%-4s %-4s %-6s %-12s %-12s %-16s",
                "ID", "PC", "Prior", "Proceso", "IR", "Status");
            mvwprintw(ventana->ventana[7],3,1,"-------------------------------------------------------------");
            j = 0;
            while(lista != NULL){
                aux = lista;
                lista = lista->siguiente;
                mvwprintw(ventana->ventana[7], j+4, 1, "%-4d %-4d %-6d %-12s %-12s %-16s",
                    aux->id, aux->pc, aux->prioridad, aux->nombre, aux->ir, aux->estado);
                j++;
            }
            wrefresh(ventana->ventana[7]);
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
    int res = ejecutarInstruccion(f);
    return res;
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
        char *token = strtok(copia, " ");       //token = MOV, GET
        
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
        
        int tipo_op = tipoOperacion(token);     //1 o 2 o 3
        
        char *operandos = strtok(NULL, "");     //Ax,7 o Ax o 1,2,3
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
        } else if (tipo_op == 3){
            int res = analizadorGpo3(token, operandos, arreglo_de_listas[1]);
            if(res == -2){
                // Error de recursos - terminar el proceso
                bandera = 1;
                strcpy(reg_estado, arreglo_de_listas[1]->estado);
                reg_pc++;
                return 1;  // Retornar 1 para terminar el proceso
            } else if(res == -3){
                // Recursos insuficientes - bloquear proceso
                bandera = 1;
                strcpy(reg_estado, arreglo_de_listas[1]->estado);
                return 2;  // Retornar 2 para bloquear el proceso
            } else if(res != 0){
                bandera = 1;
                strcpy(reg_estado, "ERROR DE SINTAXIS");
                reg_pc++;
                return -1;
            }  
        } 
        else{
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
    // Revisar procesos bloqueados antes de ejecutar
    planificadorMP();
    
    for(Q = 0; Q < 4 ;Q++){
        recorrerListas(&(arreglo_de_listas[0]));
        sprintf(desc, "Recursos-> X:%d Y:%d Z:%d", recursos[0],recursos[1],recursos[2]);
        imprimirRecursos(desc);
        if (kbhito()) {
           leerComando(comando);   ////solo llamas si hay entrada
        }
        sprintf(desc, " %d/4 del proceso: %s", Q+1, reg_proceso);
        imprimirQuantum(desc);

        if(manejador() == 1){
            // Revisar si se pueden desbloquear procesos
            planificadorMP();
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

int MaxRecursos(PCB* aux){
    //Comprobar que lo que solicita MAX sean <= que los recursos totales del sistema (10)
    if(aux->RMax[0] <= 10 && aux->RMax[1] <= 10 && aux->RMax[2] <= 10){
        // Si los recursos son válidos para el sistema, insertar en listos
        // El bloqueo por falta de recursos se maneja cuando ejecuta GET, no aquí
        insertarPrioridad(&(arreglo_de_listas[0]), aux);
        recorrerListas(&(arreglo_de_listas[0]));
        return 0; //Se logro encolar a listos 
    }
    else{ // Los recursos exceden los totales del sistema - proceso inválido
        liberarRecursos(aux);   //Liberar recursos antes de terminar
        insertar(&(arreglo_de_listas[2]), aux); //insertamos a terminados
        recorrerListas(&(arreglo_de_listas[0]));
        return 0; //Se manda a terminados no hay que realizar nada mas 
    }
}

int planificadorLP(){
    PCB *aux;
    
    while(arreglo_de_listas[3] != NULL){
        aux = arreglo_de_listas[3];
        arreglo_de_listas[3] = aux->siguiente;
        aux->siguiente = NULL;

        if(Max(aux) == 1){ // Existe la instruccion MAX
            if(MaxRecursos(aux) == -1){   //Salio mal
                // Error en recursos
            }
        }
        else{ //Si no exite la instruccion MAX insertar en Terminados
            insertar(&(arreglo_de_listas[2]), aux);
            recorrerListas(&(arreglo_de_listas[0]));
        }

    }





    // while(arreglo_de_listas[3] != NULL){   //Si hay algo en Nuevos y espacio en listos Guardar en Listos
    //     aux = arreglo_de_listas[3];         
    //     arreglo_de_listas[3] = aux->siguiente;
    //     aux->siguiente = NULL;
    //     //Comprobar que exista la instruccion MAX
    //     if(Max(aux) == 1){ // todo good
    //         MaxRecursos(aux);
    //     }
    //     else{ //Si no exite la instruccion MAX insertar en Terminados
    //         insertar(&(arreglo_de_listas[2]), aux);
    //         recorrerListas(&(arreglo_de_listas[0]));
    //     }
    // }
    // if(mov){
    //     recorrerListas(&(arreglo_de_listas[0]));
    // }
    // return mov;
    return 0;
}

int planificadorMP(){
    // Planificador a Mediano Plazo - revisa procesos bloqueados
    // Solo desbloquea el PRIMER proceso que pueda obtener recursos
    PCB *aux;
    PCB *anterior = NULL;
    PCB *actual = arreglo_de_listas[4];  // Lista de bloqueados
    
    while(actual != NULL){
        // Verificar si ahora hay recursos suficientes para el GET pendiente
        if(actual->RGet[0] <= recursos[0] && 
           actual->RGet[1] <= recursos[1] && 
           actual->RGet[2] <= recursos[2]){
            
            // Hay recursos suficientes - desbloquear este proceso
            aux = actual;
            
            // Remover de lista de bloqueados
            if(anterior == NULL){
                arreglo_de_listas[4] = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            
            aux->siguiente = NULL;
            
            // Cambiar estado y mover a listos
            strcpy(aux->estado, "LISTO");
            insertarPrioridad(&(arreglo_de_listas[0]), aux);
            
            sprintf(desc, "Proceso ID:%d desbloqueado - reintentará GET", aux->id);
            imprimirError(desc);
            
            recorrerListas(&(arreglo_de_listas[0]));
            
            // Solo desbloquear UN proceso por llamada
            return 1;
        }
        
        // No hay recursos suficientes para este proceso, seguir al siguiente
        anterior = actual;
        actual = actual->siguiente;
    }
    
    return 0;  // No se desbloqueó ningún proceso
}

int Max(PCB* proceso){
    char linea[TAMANIO_COMANDO];
    if (fgets(linea, sizeof(linea), proceso->archivo) != NULL){   //linea = MAX 1,2,3
        linea[strcspn(linea, "\n")] = 0;
        
        char copia[TAMANIO_LINEA];
        strcpy(copia, linea);
        char *token = strtok(copia, " ");       //token = MAX
        
        if (token == NULL){
            return 0;
        }

        if(strcmp("MAX", token) == 0){
        char *operandos;
            for(int i = 0; i < 3; i++){
            operandos = strtok(NULL, ",");     //1 luego 2 luego 3
                if(!esNumeroValido(operandos)){
                    imprimirFilaConError("Uso incorrecto de valores");
                    strcpy(proceso->ir, linea);
                    strcpy(proceso->estado, "ERROR DE RECURSOS");
                    return -1;
                }
                proceso->RMax[i] = atoi(operandos);
            }
        }
        else{
            imprimirFilaConError("No MAX");
            strcpy(proceso->ir, linea);
            strcpy(proceso->estado, "ERROR DE RECURSOS");
            return -1;
        }
    }
    return 1;
}

int Get(char *linea){       //GET 1,2,3
    PCB *aux = arreglo_de_listas[1];
    int get[3]= {0,0,0};

    char copia[TAMANIO_LINEA];
    strcpy(copia, linea);
    char *token = strtok(copia, " ");       //token = GET
    
    if (token == NULL){
        return 0;
    }

    if(strcmp("GET", token) == 0){      //GET 1,2,3  despues de la suma Asig <= Globales
    char *operandos;
        for(int i = 0; i < 3; i++){
        operandos = strtok(NULL, ",");     //1 luego 2 luego 3
            if(!esNumeroValido(operandos)){
                imprimirFilaConError("Uso incorrecto de valores");
                strcpy(aux->ir, linea);
                strcpy(aux->estado, "ERROR DE RECURSOS");
                return -1;
            }
            get[i] = atoi(operandos);   // {1,2,3}
        }
        if(get[0] <= recursos[0] && get[1] <= recursos[1] && get[2] <= recursos[2]){
            aux->RAsig[0] += get[0]; aux->RAsig[1] += get[1]; aux->RAsig[2] += get[2];
            recursos[0] -= get[0]; recursos[1] -= get[1]; recursos[2] -= get[2];
        }
        else{
            insertar(&(arreglo_de_listas[4]), aux);       //Se inserta en la lista de bloqueados
        }

    }
    return 0;
}



