
#include<stdio.h>
#include<stdlib.h>

typedef struct columnas{
    float valor;
    int i;
    int j;
    struct columnas *sig;
}Columnas;

typedef struct filas {
    int i;
    Columnas *lista;
    Columnas *end;
    struct filas *sig;
}Filas;

typedef struct matriz {
    Filas *inicio;
    int filas;
    int columnas;
}Matriz;

Columnas *new_col(float valor, int i, int j);
Filas *new_fil(int i);
Columnas *add_col(Filas *filap ,float val,int i,int j);
Filas *add_fil(Filas *filap, int i);
Matriz AsignarElemento(int i, int j, float x, Matriz M);
float ObtenerElemento(Matriz M,int i ,int j);
void MostrarMatriz(Matriz M);
Matriz ProductoPorEscalar(float e, Matriz M);
Matriz Sumar (Matriz M1, Matriz M2);
Matriz Trasponer (Matriz M);
Matriz Producto(Matriz A, Matriz B);
