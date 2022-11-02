
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

Columnas *new_col(float valor, int i, int j){  //Crea un elemento de tipo Columnas
    Columnas *c;
    if ( (c = (Columnas*)malloc(sizeof(Columnas))) == NULL ){
        fprintf(stderr,"new_cel: Error reservando la memoria");
        exit(1);
    }
    c->valor = valor;
    c->i = i;
    c->j = j;
    c->sig = NULL;

    return c;
}

Filas *new_fil(int i){                        //Crea  un elemento de tipo Filas
    Filas *f;
    if ( (f = (Filas*)malloc(sizeof(Filas))) == NULL){
        fprintf(stderr, "new_fil: Error reservando la memoria");
        exit(1);
    }
    f->i = i;
    f->lista = NULL;
    f->sig = NULL;
    return f;
}

Columnas *add_col(Filas *filap ,float val,int i,int j){   //Agrega una nueva columna al final de la fila
    if (filap->lista == NULL){
        filap->lista = new_col(val,i,j);
        filap->end = filap->lista;
        return filap->lista;
        }
    //printf("Paso el if de add_col\n");
    //Columnas *tmp;
    //for(tmp = filap->lista; tmp->sig != NULL; tmp = tmp->sig);
    filap->end->sig = new_col(val,i,j);
    filap->end = filap->end->sig;
   // printf("añadio broma al final\n");
    return filap->lista;
}

Filas *add_fil(Filas *filap, int i){
    if (filap == NULL)                                     //Agrega una fila al final
        return new_fil(i);
    Filas *tmp;
    for(tmp = filap; tmp->sig != NULL; tmp = tmp->sig);
    tmp->sig = new_fil(i);
    return filap;
}

Matriz AsignarElemento(int i, int j, float x, Matriz M){ //Asigna un elemento en la posicion i j

    if (M.inicio == NULL && x!=0){//Si la matriz esta vacia devuelve solo el nuevo elemento
        M.inicio = new_fil(i);
        M.inicio->lista = new_col(x,i,j);
        M.inicio->end = M.inicio->lista;
        return M;
    }
    if (M.inicio == NULL && x==0) return M; //Si la matriz esta vacia y el elemento a agregar es cero se devuelve la matriz sin agregar nada
    if(i < M.inicio->i && x!=0){    //Si el elemento a agregar esta antes que el primer elemento no nulo de la matriz
        Filas *newp = new_fil(i);
        newp->lista = new_col(x,i,j);
        newp->sig = M.inicio;
        M.inicio = newp;
        return M;
    }

    Filas *tmp = M.inicio, *prev = NULL;
    for(; tmp != NULL && tmp->i <= i; tmp = tmp->sig){        //Busca la Fila en la que se va a añadir el elemento (Insertar Ordenado)
        prev =tmp;
        if (tmp->i == i){
            if(j < tmp->lista->j){    //Si dicha fila se encuentra, ahora hay que buscar la columna (Insertar Ordenado)
                Columnas *newp2 = new_col(x,i,j);
                newp2->sig = tmp->lista;
                tmp->lista = newp2;
                return M;
            }
            //añadir columna ordenada
            Columnas *tmp2 = tmp->lista, *prev2 = NULL;
            for(; tmp2 != NULL && tmp2->j <= j; tmp2 = tmp2->sig){

                if (tmp2->j == j){
                    if(x==0){
                        if(prev2 == NULL)
                            tmp->lista = tmp2->sig;
                        else
                            prev2->sig = tmp2->sig;
                        free(tmp2);
                        return M;
                    }
                    tmp2->valor = x;
                    return M;
                }
                prev2 = tmp2;
            }

            prev2->sig = new_col(x,i,j);
            if(prev2 == tmp->end)            //Si no se encuentra se crea una nueva columna
                tmp->end = prev2->sig;
            if (tmp2 != NULL)
                prev2->sig->sig = tmp2;
            return M;
        }

    }
    if(x!=0){                         //Si no se encuentra se crea una nueva fila y se le inserta de una vez el nuevo elemento
        prev->sig = new_fil(i);
        prev->sig->lista = new_col(x,i,j);
        if (tmp != NULL)
            prev->sig->sig = tmp;
        return M;
    }
    return M;
}
float ObtenerElemento(Matriz M,int i ,int j){     //Recorre la matriz hasta encontrar el elemento, sino lo encuentra es que es igual a cero, y devuelve cero
    if (M.inicio == NULL)
        return 0;
    Filas *tmp = M.inicio;
    for(; tmp != NULL && tmp->i <= i ; tmp = tmp->sig){
        if(tmp->i == i){
            //Ahora buscamos j
            Columnas *tmp2 = tmp->lista;
            for(; tmp2 != NULL && tmp2->j <=j; tmp2 = tmp2->sig){
                if(tmp2->j == j){
                    return tmp2->valor;

                }
            }
        }
    }
    return 0;   //Si el elemento no esta en la matriz es que vale 0
}

void MostrarMatriz(Matriz M){ //Imprime en pantalla la matriz
    Filas *Factual = M.inicio;
    Columnas *Cactual;

    if (M.inicio != NULL)
        Cactual = Factual->lista;
    else
        Cactual = NULL;

    for(int i = 1; i <= M.filas; ++i){
        for(int j = 1; j <= M.columnas; ++j){
            if (Cactual != NULL && Cactual->i == i && Cactual->j == j){  //Con dos for recorre la matriz y si las coordenadas coinciden imprime el elemento y avanza
                printf("%.2f ",Cactual->valor);
                if (Cactual->sig == NULL){            //Si llega al final de la columna, avanza a la fila siguiente
                    if (Factual->sig != NULL){
                        Factual = Factual->sig;
                        Cactual = Factual->lista;
                    }else
                        Cactual = NULL;        //Si la proxima fila es nula, ya recorrio todos los elementos diferentes de cero
                }else
                    Cactual = Cactual->sig;    //Avanza al siguiente elemento de la misma fila
            }else
                printf("%i ",0);    //Si las coordenadas no coiciden solo imprime 0

        }
        printf("\n");   //Salto de linea
    }

}
Matriz ProductoPorEscalar(float e, Matriz M){ //Devuelve el producto de la matriz por un escalar
    if (e==0 || M.inicio == NULL){
        Matriz M2 = {NULL, M.filas, M.columnas};
        return M2;
    }
    Filas *Factual = M.inicio;
    Columnas *Cactual;
    if (M.inicio != NULL)
        Cactual = Factual->lista;
    else
        Cactual = NULL;

    for(; Factual != NULL ; Factual = Factual->sig){
        Cactual = Factual->lista;
        for(; Cactual != NULL ; Cactual = Cactual->sig){
            Cactual->valor = Cactual->valor * e;
        }
    }
    return M;
}

Matriz Sumar (Matriz M1, Matriz M2){  //Devuelve el resultado de la suma de dos matrices
    Matriz M3 = {NULL, M1.filas, M1.columnas};
    Filas *F3 = M3.inicio;
    Filas *F1 = M1.inicio, *F2 = M2.inicio;
    Columnas *C1, *C2;
    if (M1.inicio != NULL)
        C1 = M1.inicio->lista;
    else
        C1 = NULL;
    if (M2.inicio != NULL)
        C2 = M2.inicio->lista;
    else
        C2 = NULL;

    while(C1 != NULL && C2 != NULL){    //Recorre ambas matrices hasta que alguna se acabe
        if (C1->i == C2->i ){     //si estan en la misma fila
            if (F3 == NULL ){
                M3.inicio =  add_fil(F3, C1->i);
                F3 = M3.inicio;
            }
            if(C1->j == C2->j){       //si estan en la misma columna y fila se suman y ambas avanzan
                if (C1->valor + C2->valor != 0){
                    if(F3->i != C1->i ){
                        M3.inicio = add_fil(M3.inicio, C1->i);
                        F3 = F3->sig;
                    }
                    F3->lista = add_col(F3, C1->valor + C2->valor,C1->i,C1->j);
                }
                if(C1->sig == NULL){  //avanza en la matriz 1
                    if(F1->sig != NULL){
                        F1 = F1->sig;
                        C1 = F1->lista;
                    }else
                        C1 = NULL;
                }else
                    C1 = C1->sig;

                if (C2->sig == NULL){     //avanza en la matriz 2
                    if(F2->sig != NULL){
                        F2 = F2->sig;
                        C2 = F2->lista;
                    }else
                        C2 = NULL;
                }else
                    C2 = C2->sig;
            }else{
            if(C1->j < C2->j){
                                            //C1 esta antes q C2 en la misma fila
                if(F3->i != C1->i){
                        F3 = add_fil(F3, C1->i);
                        F3 = F3->sig;
                    }
                F3->lista = add_col(F3, C1->valor, C1->i,C1->j);  //agrega C1 y avanza
                if(C1->sig == NULL){
                    if(F1->sig != NULL){
                        F1 = F1->sig;
                        C1 = F1->lista;
                    }else
                        C1 = NULL;
                }else
                    C1 = C1->sig;
            }else{
                                                //C2 esta antes q C1 en la misma fila
                if(F3->i != C2->i){
                        F3 = add_fil(F3, C2->i);
                        F3 = F3->sig;
                    }
                F3->lista = add_col(F3, C2->valor, C2->i,C2->j);//agrega C2 y avanza
                if (C2->sig == NULL){
                    if(F2->sig != NULL){
                        F2 = F2->sig;
                        C2 = F2->lista;
                    }else
                        C2 = NULL;
                }else
                    C2 = C2->sig;
            }

            }



        }else
        if (C1->i < C2->i){   //C1 esta en una fila anterior
            if (F3 == NULL ){
                M3.inicio =  add_fil(F3, C1->i);
                F3 = M3.inicio;
            }
            if(F3->i != C1->i){
                F3 = add_fil(F3, C1->i);
                F3 = F3->sig;
            }
            F3->lista = add_col(F3, C1->valor, C1->i, C1->j); //C1 se añade y avanza
            if(C1->sig == NULL){
                    if(F1->sig != NULL){
                        F1 = F1->sig;
                        C1 = F1->lista;
                    }else
                        C1 = NULL;
                }else
                    C1 = C1->sig;

        }else{      //C2 esta en una fila anterior
            if (F3 == NULL ){
                M3.inicio =  add_fil(F3, C2->i);
                F3 = M3.inicio;
            }
            if(F3->i != C2->i){
                F3 = add_fil(F3, C2->i);
                F3 = F3->sig;
            }
            F3->lista = add_col(F3, C2->valor, C2->i, C2->j);//Se agrega C2 y avanza
            if (C2->sig == NULL){
                    if(F2->sig != NULL){
                        F2 = F2->sig;
                        C2 = F2->lista;
                    }else
                        C2 = NULL;
                }else
                    C2 = C2->sig;
        }
    }
    while(C1 != NULL){ //Se termino de recorrer la segunda matriz, se terminan de agregar los elementos restantes de la primera
        if (F3 == NULL ){
            M3.inicio =  add_fil(F3, C1->i);
            F3 = M3.inicio;
            printf("%i",F3->i);
        }
        if(F3->i != C1->i){
                F3 = add_fil(F3, C1->i);
                F3 = F3->sig;
            }
            F3->lista = add_col(F3, C1->valor, C1->i, C1->j);
            if(C1->sig == NULL){
                    if(F1->sig != NULL){
                        F1 = F1->sig;
                        C1 = F1->lista;
                    }else
                        C1 = NULL;
                }else
                    C1 = C1->sig;
    }
    while(C2 != NULL){ //Se termino de agregar la primera matriz, se terminan de agregar los elementos restantes de la segunda
        if (F3 == NULL ){
            M3.inicio =  add_fil(F3, C2->i);
            F3 = M3.inicio;
        }
        if(F3->i != C2->i){
                M3.inicio = add_fil(M3.inicio, C2->i);
                F3 = F3->sig;
            }
            F3->lista = add_col(F3, C2->valor, C2->i, C2->j);
            if(C2->sig == NULL){
                    if(F2->sig != NULL){
                        F2 = F2->sig;
                        C2 = F2->lista;
                    }else
                        C2 = NULL;
                }else
                    C2 = C2->sig;
    }
    return M3;
}

Matriz Trasponer (Matriz M){
    Matriz M2 = {NULL, M.columnas, M.filas};
    if(M.inicio == NULL){
        return M2;
    }

    //Recorrer M e ir agregando los elementos a M2
    Filas *tmp = M.inicio;

    for(; tmp != NULL; tmp = tmp->sig){
        Columnas *tmp2 = tmp->lista;
        for(;tmp2 != NULL; tmp2  = tmp2->sig){

            if(M2.inicio!=NULL && tmp2->j < M2.inicio->i){
                Filas *newp = new_fil(tmp2->j);
                newp->lista = add_col(newp,tmp2->valor,tmp2->j,tmp2->i);
                newp->sig = M2.inicio;
                M2.inicio = newp;
            }else{

                Filas *tmp3 = M2.inicio, *prev = NULL;
                int encontro = 0;
                for(; tmp3 != NULL && tmp3->i <= tmp2->j; tmp3 = tmp3->sig){              //Busca la Fila en la que se va a añadir el elemento (Insertar Ordenado)
                    prev =tmp3;
                    if (tmp3->i == tmp2->j){
                //añadir columna al final
                        tmp3->lista = add_col(tmp3,tmp2->valor,tmp2->j,tmp2->i);
                        encontro = 1;
                    }
                }// Si no se encuentra, se crea otra fila
                if(!encontro){
                    if (prev==NULL){//se agrega en la primera fila
                        M2.inicio = new_fil(tmp2->j);
                        M2.inicio->lista = add_col(M2.inicio,tmp2->valor, tmp2->j, tmp2->i);
                    }else{  //Se agrega en una fila intermedia
                        prev->sig = new_fil(tmp2->j);
                        prev->sig->lista = add_col(prev->sig, tmp2->valor,tmp2->j,tmp2->i);
                        if (tmp3 != NULL)
                            prev->sig->sig = tmp3;
                    }
                }
            }
        }
    }
    return M2;
}
Matriz Producto(Matriz A, Matriz B){ //Devuelve el producto de dos matrices
    Matriz BT = Trasponer(B);
    Matriz C = {NULL, A.filas, B.columnas};
    Filas *tmpC = NULL;
    if (A.inicio == NULL || B.inicio == NULL) return C;

    Filas *tmpA = A.inicio;
    for(;tmpA!=NULL; tmpA = tmpA->sig){
        Filas *tmpB = BT.inicio;
        for(;tmpB != NULL; tmpB = tmpB->sig){
            Columnas *C1 = tmpA->lista, *C2 = tmpB->lista;
            float acumulador = 0;

            while(C1 != NULL && C2 != NULL){
                if(C1->j == C2->j){
                    acumulador += C1->valor * C2->valor;
                    C1 = C1->sig;
                    C2 = C2->sig;
                }else
                    if(C1->j < C2->j){
                        C1 = C1->sig;
                    }else
                        C2 = C2->sig;
            }

            if(acumulador!=0){
                if(tmpC == NULL){
                    tmpC = new_fil(tmpA->i);
                    tmpC->lista = add_col(tmpC,acumulador,tmpA->i,tmpB->i);
                    C.inicio = tmpC;
                }else{
                    if(tmpA->i == tmpC->i){
                        tmpC->lista = add_col(tmpC,acumulador,tmpA->i,tmpB->i);
                    }else{
                        tmpC->sig = new_fil(tmpA->i);
                        tmpC = tmpC->sig;
                        tmpC->lista = add_col(tmpC,acumulador,tmpA->i,tmpB->i);
                    }
                }
            }
        }
    }
    return C;
}
