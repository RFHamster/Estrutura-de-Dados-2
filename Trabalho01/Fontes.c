#include <stdio.h>
#include "TAD.h"
#include <time.h>

/* Programa 1
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
*/

/*Programa 2
Complexidade comp;

int funcaox(int a){
    if (a<2){
        return 1;
    }else{
        contarCp(&comp.contadorMat, 3);
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
*/

/*Programa 3
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
*/
