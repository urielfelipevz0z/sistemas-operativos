# Estándares de Código - Proyecto Sistemas Operativos

## 1. Estándares Generales de C

### Estilo de Código
- **Estándar**: C99 (ISO/IEC 9899:1999) como mínimo
- **Indentación**: Tabuladores
- **Codificación**: UTF-8

### Nomenclatura

#### Variables y Funciones
```c
// Variables: snake_case en minúsculas
int contador_instrucciones;
char *nombre_archivo;
struct cpu_state estado_cpu;

// Funciones: camelCase en minúsculas
int leerArchivo(char *nombre);
void ejecutarInstruccion(struct instruccion *inst);
```

#### Constantes y Macros
```c
// Constantes: UPPER_CASE con guiones bajos
#define MAX_BUFFER_SIZE 256
#define NUMERO_REGISTROS 4
#define ERROR_ARCHIVO_NO_ENCONTRADO -1
```

#### Nombres de archivos
```c
// Archivos de código fuente: kebab-case con sufijo .c
// Ejemplo: alu.c, interprete-asm.c
```

```c
// Estructuras: snake_case con sufijo descriptivo
struct cpu_registers {
    int ax, bx, cx, dx;
};

struct error_info {
    int codigo;
    char mensaje[100];
};

### Organización de Archivos

#### Estructura de Directorios
```
proyecto/
├── src/                    # Código fuente (.c)
├── include/               # Headers (.h)
├── tests/                 # Pruebas unitarias
├── docs/                  # Documentación
├── examples/              # Archivos de ejemplo (.asm)
├── build/                 # Archivos compilados
└── scripts/               # Scripts de compilación
```

#### Convenciones de Nombres de Archivo
- **Headers**: `modulo.h` (ej: `alu.h`, `interprete.h`)
- **Código fuente**: `modulo.c` (ej: `alu.c`, `interprete.c`)
- **Archivos assembly**: `ejemplo.asm`
- **Tests**: `test_modulo.c`

## 2. Estructura de Headers (.h)

### Plantilla Estándar
```c
#ifndef MODULO_H
#define MODULO_H

#include <stdio.h>
#include <stdlib.h>
/* otros includes estándar */

/* includes locales */
#include "otro_modulo.h"

/* Constantes */
#define CONSTANTE_MODULO 100

/* Tipos de datos */
typedef struct {
    int campo1;
    char campo2[50];
} estructura_t;

/* Declaraciones de funciones */
int funcion_publica(int parametro);
void otra_funcion(estructura_t *datos);

#endif /* MODULO_H */
```

## 3. Estructura de Archivos Fuente (.c)

### Plantilla Estándar
```c
/**
 * @file modulo.c
 * @brief Descripción breve del módulo
 * @author Equipo Sistemas Operativos
 * @date Fecha de creación
 */

#include "modulo.h"

/* Variables estáticas (privadas al módulo) */
static int variable_privada = 0;

/* Funciones estáticas (privadas al módulo) */
static void funcion_privada(void) {
    // implementación
}

/* Implementación de funciones públicas */
int funcion_publica(int parametro) {
    // implementación
    return 0;
}
```

## 4. Comentarios y Documentación

### Comentarios de Funciones
```c
/**
 * @brief Ejecuta una instrucción en la ALU
 * @param operacion Tipo de operación (MOV, ADD, SUB, etc.)
 * @param registro Registro destino (Ax, Bx, Cx, Dx)
 * @param valor Valor o registro fuente
 * @return 0 si éxito, código de error negativo si falla
 */
int alu_ejecutar(operacion_tipo_t operacion, int registro, int valor);
```

### Comentarios en Línea
```c
/* 
 * Parsear la línea de instrucción
 * Formato esperado: "OPERACION registro, valor"
 */
token = strtok(linea, " ");
```

## 5. Manejo de Errores

### Códigos de Error Estándar
```c
#define SUCCESS 0
#define ERROR_ARCHIVO_NO_ENCONTRADO -1
#define ERROR_COMANDO_INVALIDO -2
#define ERROR_REGISTRO_INVALIDO -3
#define ERROR_DIVISION_POR_CERO -4
#define ERROR_OPERACION_INVALIDA -5
#define ERROR_MEMORIA_INSUFICIENTE -6
```

### Estructura de Error
```c
typedef struct {
    int codigo;
    char mensaje[256];
    char archivo[100];
    int linea;
} error_info_t;
```

### Espacios en Operadores
```c
// Correcto
int resultado = a + b * c;
if (x == y && z != w)

// Incorrecto
int resultado=a+b*c;
if(x==y&&z!=w)
```

## 6. Compilación y Makefile

### Flags de Compilación Requeridos
```makefile
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -g -O0
INCLUDES = -Iinclude
```

### Estructura del Makefile
```makefile
# Variables
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TARGET = sistema_operativo

# Regla principal
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

# Compilar objetos
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Limpiar
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean
```

## 7. Control de Versiones (Git)

### Mensajes de Commit
```
feat: agregar función de multiplicación en ALU
fix: corregir error de división por cero
docs: actualizar documentación de la API
refactor: reorganizar estructura de archivos
test: agregar pruebas unitarias para interprete
```

### Archivos a Ignorar (.gitignore)
```
# Archivos compilados
*.o
*.out
*.exe
build/

# Archivos del editor
*.swp
*.swo
*~

# Archivos de depuración
*.gdb
core

# Archivos temporales
*.tmp
*.bak
```

## 10. Documentación de Equipo

### README.md Template
```markdown
# Sistema Operativo Simulado

## Descripción
Simulador de sistema operativo que interpreta instrucciones de assembly.

## Compilación
```bash
make
```

---

**Notas Importantes:**
- Documentar cualquier decisión de diseño no obvia
- Mantener el código simple y legible antes que optimizado
- Revisar código en pares antes de hacer commit
- Los papus son unos monos
