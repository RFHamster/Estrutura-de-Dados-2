#include <bits/stdc++.h>

using namespace std;

vector<string> Codificacao;
int quantasLetras;

void shannon2(int inicio, int fim, vector<pair<char, int>> frequenciaLetra, string escrita){
    if(inicio == fim){
        Codificacao[inicio] += escrita;
        return;
    }
    if(inicio == fim-1){
        Codificacao[inicio] += escrita + "1"; 
        Codificacao[fim] += escrita + "0";
        return;
    }
    int total = 0;
    for(int i = inicio; i<=fim;i++){
        total += frequenciaLetra.at(i).second;
    }
    total = total/2;
    int index = inicio;
    total -= frequenciaLetra.at(index).second;
    while(total>0){
        index++;
        total -= frequenciaLetra.at(index).second;
    }

    shannon2(inicio, index-1, frequenciaLetra,escrita+"1");
    shannon2(index, fim, frequenciaLetra,escrita+"0");
}

void shannon(int inicio, int fim, vector<pair<char, int>> frequenciaLetra){
    if(inicio == fim){
        Codificacao[inicio] += "0";
        return;
    }
    if(inicio == fim-1){
        Codificacao[inicio] += "1"; 
        Codificacao[fim] += "0";
        return;
    }
    int total = 0;
    for(int i = inicio; i<=fim;i++){
        total += frequenciaLetra.at(i).second;
    }
    total = total/2;
    int index = inicio;
    total -= frequenciaLetra.at(index).second;
    while(total>0){
        index++;
        total -= frequenciaLetra.at(index).second;
    }

    shannon2(inicio, index-1, frequenciaLetra,"1");
    shannon2(index, fim, frequenciaLetra,"0");
}

string converteTexto(string texto, map<char,string> codigos){
    string s = "";
    for(int i = 0; i<texto.size();i++){
        char c = texto[i];
        s += codigos[c];
    }
    return s;
}

char BytesToBits(string s){
    int somador = 1;
    int caractere = 0;
    for(int i = 0; i<8;i++){
        if(s[i] == '1'){
            caractere += somador;
        }
        somador = somador * 2;
    }
    char c = caractere;
    return c;
}

string desconverteTexto(string texto, map<char,string> descodificarBitsBytes){
    string s = "";
    for(int i = 0; i<texto.size();i++){
        s += descodificarBitsBytes[texto[i]];
    }
    return s;
}

int main (){
    //Abrindo Arquivo
    FILE *arq1;
    arq1 = fopen("Texto.txt","r");
    if(arq1 == NULL){
        cout << "Arquivo Inexistente";
        return 0;
    }

    //Contando a Frequencia das Letras
    vector<pair<char, int>>frequenciaLetra;
    string texto;
    vector<int> frequencia;
    int totalLetras = 0;
    char c = fgetc(arq1);

    for(int i = 0; i<256;i++){
        frequencia.push_back(0);
    }

    do{
        frequencia[c]++;
        texto+=c;
    }while((c=fgetc(arq1)) != EOF);

    cout << " - Texto a ser Codificado - " << endl;
    cout << texto << endl;

    for(int i = 0;i<256;i++){
        if(frequencia[i] > 0){
            char letra = i;
            frequenciaLetra.emplace_back(letra,frequencia[i]);
            totalLetras+=frequencia[i];
        }
    }
    c = 26;
    frequenciaLetra.emplace_back(c,1);
    texto += c;
    sort(frequenciaLetra.begin(),frequenciaLetra.end(), [] (const auto &x, const auto &y) {return x.second < y.second;});

    quantasLetras = frequenciaLetra.size();
    for(int i = 0; i<quantasLetras;i++){
        Codificacao.push_back("");
    }
    shannon(0,(quantasLetras-1),frequenciaLetra);

    map<char,string> codigos;
    cout << "\n - Caracter - Frequencia - Codigos - " << endl;
    for(int i = 0; i<quantasLetras;i++){
        cout << frequenciaLetra.at(i).first << " : " << frequenciaLetra.at(i).second << " = " << Codificacao.at(i) << endl;
        codigos[frequenciaLetra.at(i).first] = Codificacao.at(i);
    }

    //Convertendo o texto para Bytes
    string textoBin = converteTexto(texto,codigos);
    cout << "\n - Texto em Bytes - " << endl;
    cout << textoBin << endl;

    string textoBits = "";
    int tamanho = 0;
    int tamanho2 = 8;
    while(tamanho2<=textoBin.size()-1){
        string converte = "";
        if(tamanho2 > textoBin.size()-1){
            int excedente = tamanho2 - textoBin.size()-1;
            for(int i = tamanho; i<excedente;i++){
                converte += textoBin[i];
            }
            for(int i = excedente; i<tamanho2;i++){
                converte += "0";
            }
        }else{
            for(int i = tamanho; i<tamanho2;i++){
                converte += textoBin[i];
            }
        }
        char c = BytesToBits(converte);
        textoBits.push_back(c);
        tamanho += 8;
        tamanho2 += 8;
    }

    cout << "\n - Texto em Bits - " << endl;
    cout << textoBits << endl;

    return 0;
}