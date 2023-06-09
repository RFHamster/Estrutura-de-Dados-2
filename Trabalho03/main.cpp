#include <bits/stdc++.h>

using namespace std;

vector<string> Codificacao;
int quantasLetras;

//Nessa função de shannon, ela somente escreve no vector de codificação quando entra
//numa encruzilhada da árvore que irá acabar, ou seja, quando, ao fazer o shannon, sobra um par ou um elemento sozinho
//assim, nesses cassos ele escreve no vector, entretanto, se isso não acontecer, ele armazena essa escrita na string escrita
//e vai repetindo o processo até chegar na encruzilhada e escrever todos os chars
void shannon(int inicio, int fim, vector<pair<char, int>> frequenciaLetra, string escrita){
    if(inicio == fim){
        if(escrita == ""){
            Codificacao[inicio] += "0";
        }
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
    shannon(inicio, index-1, frequenciaLetra,escrita+"1");
    shannon(index, fim, frequenciaLetra,escrita+"0");
}

//Função para converter uma string texto para um texto de bits (0s e 1s), pegando cada char na cadeia
//e vendo o valor dele na codificação, convertendo o mesmo para um bit
string converteTexto(string texto, map<char,string> codigos){
    string s = "";
    for(int i = 0; i<texto.size();i++){
        char c = texto[i];
        s += codigos[c];
    }
    return s;
}

//Função que converte um byte com 8 bits (00010101) para um char, assim fazendo uma compressão
//basicamente eu converto essa cadeia de bits para seu referencial em decimal
//e esse decimal eu converto para a tabela ASCII
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

//Função que desconverte o texto, pegando cada char da cadeia e transformando em 0s e 1s atraves 
//da descodificação passada como parâmetro
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
    //primeiro criando um vetor de tamanho 256
    //para comportar todos os chars da ASCII
    vector<pair<char, int>>frequenciaLetra;
    string texto;
    vector<int> frequencia;
    int totalLetras = 0;
    char c = fgetc(arq1);

    for(int i = 0; i<256;i++){
        frequencia.push_back(0);
    }


    //Lê o texto e vai contando a sua frequencia no vetor frequencia
    do{
        frequencia[c]++;
        texto+=c;
    }while((c=fgetc(arq1)) != EOF);

    cout << " - Texto a ser Codificado - " << endl;
    cout << texto << endl;

    //criando um par, char e sua frequencia,
    //e adicinando todos esses que a frequencia é maior que 0
    for(int i = 0;i<256;i++){
        if(frequencia[i] > 0){
            char letra = i;
            frequenciaLetra.emplace_back(letra,frequencia[i]);
            totalLetras+=frequencia[i];
        }
    }
    //adicionando o EOF
    c = 26;
    frequenciaLetra.emplace_back(c,1);
    texto += c;
    //Ordenando o vetor de forma crescente de frequencia
    sort(frequenciaLetra.begin(),frequenciaLetra.end(), [] (const auto &x, const auto &y) {return x.second < y.second;});

    quantasLetras = frequenciaLetra.size();
    for(int i = 0; i<quantasLetras;i++){
        Codificacao.push_back("");
    }

    //utilizando a função shannon, que precisa do inicio do vector, seu tamanho-1, a tabela de frequencia
    //que sera usada para criar a codificação e uma string vazia para escrever depois
    string escrita = "";
    shannon(0,(quantasLetras-1),frequenciaLetra,escrita);


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

    //com o texto em 0s e 1s, a gente agrupa ele 8 a 8
    //e vai passando cada um desses para a função que converte 1 byte para char,
    //adicionadno o resultado na string de TextoBits
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