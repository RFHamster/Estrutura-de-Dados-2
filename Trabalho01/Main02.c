#include <stdio.h>
#include "TAD.h"
#include <time.h>

Complexidade comp;

int funcaox(int a){
    if (a<2){
        return 1;
    }else{
        contarCp(&comp.contadorMat, 1);
        return funcaox(a-1) + funcaox(a-2); 
    }
}

int main(){

    iniciarCp(&comp);

    int n = 30;
    funcaox(n);

    finalizarCp(&comp, n);
    
    return 0;
}   