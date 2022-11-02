#include<stdio.h>
#include "matriz.h"
int main(){
    int N1,M1,cant;
    printf("***Bienvenido a la Calculadora de Matrices Dispersas***\n");
    printf("Ingrese las dimensiones de la matriz 1\n");
    scanf("%i %i",&N1,&M1);
    Matriz tabla1 = {NULL, N1, M1};
    printf("Ingrese cuantos elementos se van a asignar\n");
    scanf("%i",&cant);
    printf("Ingrese la posicion y el valor en el formato i j valor\n");
    for(int n=0; n < cant; ++n){
        int i,j;
        float valor;
        scanf("%i %i %f",&i, &j,&valor);
        tabla1 = AsignarElemento(i,j,valor, tabla1);
    }
    int opcion = 0;
    while(opcion == 0 || opcion == 1 || opcion == 2  || opcion == 4 || opcion == 6 || opcion == 7){
            printf("\nSeleccione que accion realizar\n");
            printf("1: ObtenerElemento(i,j)\n");
            printf("2: AsignarElemento(i,j,x)\n");
            printf("3: Sumar Matrices\n");
            printf("4: Multiplicar Matriz por Escalar\n");
            printf("5: Producto de matrices\n");
            printf("6: Transponer\n");
            printf("7: Imprimir matriz\n");
            printf("8: Salir\n");
            scanf("%i",&opcion);

            while(opcion < 1 || opcion > 8){
                printf("Opcion no valida, ingrese nuevamente\n");
                scanf("%i", &opcion);
            }

            if (opcion == 1){
                printf("ObtenerElemento: Ingrese i j\n");
                int i,j;
                scanf("%i %i",&i,&j);
                printf("Elemento en %i %i: %f\n",i,j,ObtenerElemento(tabla1, i, j));
            }
            if (opcion == 2){
                printf("AsignarElemento: Ingrese i j valor\n");
                int i,j;
                float valor;
                scanf("%i %i %f", &i, &j, &valor);
                tabla1 = AsignarElemento(i,j,valor,tabla1);
            }
            if (opcion == 4){
                printf("Multiplicar Matriz por escalar: Ingrese el escalar\n");
                float e;
                scanf("%f",&e);
                tabla1 = ProductoPorEscalar(e, tabla1);
            }
            if (opcion == 6){
                printf("Transponer:\n");
                tabla1 = Trasponer(tabla1);
                MostrarMatriz(tabla1);
            }

            if (opcion == 7){
                printf("Imprimir matriz:\n");
                MostrarMatriz(tabla1);
            }
        }

        if (opcion == 3){
            int N2,M2,cant2;
            printf("Sumar Matrices:\n");
            printf("Ingrese las dimensiones de la matriz 2\n");
            scanf("%i %i",&N2,&M2);
            while (N1 != N2 || M1 != M2){
                printf("Ambas matrices deben tener la misma cantidad de filas y columnas\n");
                scanf("%i %i",&N2, &M2);
            }
            Matriz tabla2 = {NULL, N2, M2};
            printf("Ingrese cuantos elementos se van a asignar\n");
            scanf("%i",&cant2);
            printf("Ingrese la posicion y el valor en el formato i j valor\n");
            for(int n=0; n < cant2; ++n){
                int i,j;
                float valor;
                scanf("%i %i %f",&i, &j,&valor);
                tabla2 = AsignarElemento(i,j,valor, tabla2);
            }
            Matriz tabla3 = Sumar(tabla1, tabla2);
            printf("Resultado de la Suma:\n");
            int opcion2 = 0;
            while(opcion2 == 0 || opcion2 == 1 ){
                printf("\nSeleccione que accion realizar\n");
                printf("1: ObtenerElemento(i,j)\n");
                printf("2: Imprimir matriz\n");
                printf("3: Salir\n");
                scanf("%i",&opcion2);
                if (opcion2 == 1){
                    printf("ObtenerElemento: Ingrese i j\n");
                    int i,j;
                    scanf("%i %i",&i,&j);
                    printf("Elemento en %i %i: %f\n",i,j,ObtenerElemento(tabla3, i, j));
                }
            }
            if (opcion2 == 2){
                printf("Resultado de la Suma:\n");
                MostrarMatriz(tabla3);
            }
        }
        if (opcion == 5){
            int N2,M2,cant2;
            printf("Producto de Matrices:\n");
            printf("Ingrese las dimensiones de la matriz 2\n");
            scanf("%i %i",&N2,&M2);
            while (M1 != N2){
                printf("La cantidad de columnas de la primera debe ser igual a la cantidad de filas de la segunta\n");
                scanf("%i %i",&N2, &M2);
            }
            Matriz tabla2 = {NULL, N2, M2};
            printf("Ingrese cuantos elementos se van a asignar\n");
            scanf("%i",&cant2);
            printf("Ingrese la posicion y el valor en el formato i j valor\n");
            for(int n=0; n < cant2; ++n){
                int i,j;
                float valor;
                scanf("%i %i %f",&i, &j,&valor);
                tabla2 = AsignarElemento(i,j,valor, tabla2);
            }
            printf("Resultado del producto:\n");
            Matriz tabla3 = Producto(tabla1,tabla2);

            int opcion2 = 0;
            while(opcion2 == 0 || opcion2 == 1 ){
                printf("\nSeleccione que accion realizar\n");
                printf("1: ObtenerElemento(i,j)\n");
                printf("2: Imprimir matriz\n");
                printf("3: Salir\n");
                scanf("%i",&opcion2);
                if (opcion2 == 1){
                    printf("ObtenerElemento: Ingrese i j\n");
                    int i,j;
                    scanf("%i %i",&i,&j);
                    printf("Elemento en %i %i: %f\n",i,j,ObtenerElemento(tabla3, i, j));
                }
            }
            if (opcion2 == 2){
                printf("Resultado del producto:\n");
                MostrarMatriz(tabla3);
            }
        }

    return 0;
}
