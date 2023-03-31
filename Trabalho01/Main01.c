#include <stdio.h>
#include "TAD.h"
#include <time.h>

int main(){
    Complexidade comp;
    iniciarCp(&comp);

    int n,i,a;
    n = 30;
    a=2;

    for (i=0;i<n;i++){
        a=a*2;
        contarCp(&comp.contadorMat,2);
    }
    finalizarCp(&comp, n);

    return 0;
}