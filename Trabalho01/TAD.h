#include <math.h>
#include <stdio.h>

typedef struct 
{
    long int contadorMat;
}Complexidade;

void iniciarCp(Complexidade *c){
    c->contadorMat = 0;
}

void contarCp(long int *c, int add){
    *c += add;
}

void finalizarCp(Complexidade *c, int n){
    if(c->contadorMat == 1){
        printf("Contador = %ld, logo O(1)", c->contadorMat);
    }else if (c->contadorMat<=log10(n)){
        printf("Contador = %ld, logo O(1) < contador <= O(Log(n))", c->contadorMat);
    }else if(c->contadorMat<=n){
        printf("Contador = %ld, logo O(Log(n)) < contador <= O(n)", c->contadorMat);
    }else if(c->contadorMat <= n * log10(n)){
        printf("Contador = %ld, logo O(n) < contador <= O(N * Log(n))", c->contadorMat);
    }else if(c->contadorMat <= pow(n,2)){
        printf("Contador = %ld, logo O(N * Log(n)) < contador <= O(n^2)", c->contadorMat);
    }else if(c->contadorMat<= pow(n,3)){
        printf("Contador = %ld, logo O(n^2) < contador <= O(n^3)", c->contadorMat);
    }else if (c->contadorMat<=pow(2,n)){
        printf("Contador = %ld, logo O(n^3) < contador <= O(2^n)", c->contadorMat);
    }else{
        printf("Contador = %ld, contador > O(2^n)", c->contadorMat);
    }
}