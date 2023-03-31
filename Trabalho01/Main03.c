#include <stdio.h>
#include "TAD.h"
#include <time.h>

int main(){
    Complexidade comp;
    iniciarCp(&comp);

    int i, j, k,n;
    int a = 0;
    n = 30;
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
           for (k=0;k<n;k++){
                a=a*2;
                contarCp(&comp.contadorMat,2);
            }
            contarCp(&comp.contadorMat,1);
        }
        contarCp(&comp.contadorMat,1);
    }

    finalizarCp(&comp, n);
    
    return 0;
}