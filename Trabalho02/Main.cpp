#include <bits/stdc++.h>

using namespace std;

typedef struct no
{
    int dados;
    struct no *prox;
}noptr;

noptr *inicio;

void insereLista(int valor){
    noptr *novo;
    novo = (struct no *) malloc (sizeof(noptr));
    if(!novo){
        printf("\nSem Memoria!!!!\n");
        return;
    }
    novo->dados = valor;
    if(inicio == NULL){
        novo->prox = NULL;
    }else{
        novo->prox = inicio;
    }
    inicio = novo;
}

int removeLista(){
    noptr *p;
    int valor;
    if(inicio == NULL){
        return -1;
    }else{
        p = inicio;
        valor = p->dados;
        inicio = p->prox;
        free(p);
    }
    return valor;
}

int prefixo(string c, string p, int tc, int tp, int pos)
{
    int i;
    for (i=0; i<tp; i++){
        if ( c[ i + pos ] != p[ i ] ){
            return 0;
        }
    }
    insereLista(pos);
    return 1;
} 


int buscaboyler(string cadeia, string palavra, int tc, int tp)
{
    int simb[256]; //tabela indicando a útima ocorrência do símbolo na palavra
    int i;
    for (i=0; i<256; i++) simb[i] = -1; //inicia os símbolos com -1
    for (i=0; i<tp; i++) simb[ palavra[ i ] ] = i; //verifica as aparições dos símbolos
    // na palavra
    i = 0;
    while (i <= (tc - tp) ){
    prefixo(cadeia, palavra, tc, tp, i);
    i=i + tp ; // avanca uma palavra
    i=i - simb[cadeia[i]]; //recua para inicio da palavra ou avanca mais 1
    }
    return 0;
} 


int main(){
    FILE *arq1, *arq2;
    string aux, s;

    cout << "Digite o nome do Arquivo (lembre-se do .txt)" << endl;
    cin >> aux;
    arq1 = fopen(aux.data(), "r");
    if(arq1 == NULL){
        cout << "Arquivo Inexistente" << endl;
        return 0;
    }

    int i = 0;
    char c;
    while((c=fgetc(arq1)) != EOF){
        s+=c;
        i++;
    }
    cout << s << endl;

    string palavraTrocar;
    string palavraAchar;
    cout << "Digite a palavra a ser encontrada" << endl;
    cin.sync();
    getline(cin, palavraAchar);
    while(!palavraAchar.empty()){
        cout << "Digite a palavra para colocar no lugar" << endl;
        cin >> palavraTrocar;
        cin.sync();

        buscaboyler(s,palavraAchar,s.length(),palavraAchar.length());

        int num = removeLista();
        while(num != -1){
            s.replace(num, palavraAchar.length(), palavraTrocar);
            num = removeLista();
        }

        cout << s << endl;
        cout << "Digite a palavra a ser encontrada" << endl;
        getline(cin, palavraAchar);
    }
    
    cout << "Digite o nome do Arquivo a ser Criado" << endl;
    cin >> aux;
    arq2 = fopen(aux.data(), "w");
    for(i = 0; i<s.length();i++){
        putc(s[i],arq2);
    }  
}