#include <stdio.h>
#include <stdlib.h>

#define SIZE 5  // Tamanho da grade (5x5)

// Estrutura para representar um vértice do grafo
typedef struct Noptr {
    int vert;
    struct Noptr* prox;
} Noptr;

typedef struct {
    Noptr* inicio;
} AdjList;

typedef struct {
    int cor;
///    int qtdArestas;
    AdjList* listaAdjacente;
} Vertice;

// Função para adicionar um vértice à lista de adjacência de um vértice
void addVert(AdjList* listaAdjacente, int vert) {
    Noptr* newNode = (Noptr*)malloc(sizeof(Noptr));
    newNode->vert = vert;
    newNode->prox = NULL;

    if (listaAdjacente->inicio == NULL) {
        listaAdjacente->inicio = newNode;
    } else {
        Noptr* atual = listaAdjacente->inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = newNode;
    }
}

// Função para verificar se dois vértices são adjacentes
int verificaAdjacente(Vertice grafo[], int u, int v) {
    Noptr* atual = grafo[u].listaAdjacente->inicio;
    while (atual != NULL) {
        if (atual->vert == v) {
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

// Função para colorir o grafo
void colorirGrafo(Vertice grafo[]) {
    int corAtual = 1;
    int numVertices = SIZE * SIZE;

    while (1) {
        int todosColoridos = 1;

        for (int i = 0; i < numVertices; i++) {
            if (grafo[i].cor == 0) {
                int adjacenteColorido = 0;

                for (int j = 0; j < numVertices; j++) {
                    if (verificaAdjacente(grafo, i, j) && grafo[j].cor == corAtual) {
                        adjacenteColorido = 1;
                        break;
                    }
                }

                if (!adjacenteColorido) {
                    grafo[i].cor = corAtual;
                } else {
                    todosColoridos = 0;
                }
            }
        }

        if (todosColoridos) {
            break;
        }

        corAtual++;
    }
}

int main() {
    Vertice grafo[SIZE * SIZE];  // Grafo representado como um array de vértices
    char cores[][15] = {"", "Rosa", "Verde claro", "Verde escuro", "Azul"};

    // Inicialização do grafo e construção da lista de adjacência para cada vértice
    for (int i = 0; i < SIZE * SIZE; i++) {
        grafo[i].cor = 0;  // Cor indefinida
///        grafo[i].qtdArestas = 4; // Qtd de arestas inicial (assumindo que não são vértices das bordas)
        grafo[i].listaAdjacente = (AdjList*)malloc(sizeof(AdjList));
        grafo[i].listaAdjacente->inicio = NULL;

        // Ajuste da qtd de arestas para vértices nas bordas
        int lin = i / SIZE;
        int col = i % SIZE;

        //printf("\n\nLin: %d, Col: %d\n\n", lin, col);
/**       if (lin == 0 || lin == SIZE - 1 || col == 0 || col == SIZE - 1) {
            grafo[i].qtdArestas = 3;
        }*/

        // Adiciona os vizinhos à lista de adjacência
        if (lin > 0) {
            addVert(grafo[i].listaAdjacente, i - SIZE);  // Vizinho superior
        }
        if (lin < SIZE - 1) {
            addVert(grafo[i].listaAdjacente, i + SIZE);  // Vizinho inferior
        }
        if (col > 0) {
            addVert(grafo[i].listaAdjacente, i - 1);  // Vizinho à esquerda
        }
        if (col < SIZE - 1) {
            addVert(grafo[i].listaAdjacente, i + 1);  // Vizinho à direita
        }
        if (lin > 0 && col > 0) {
            addVert(grafo[i].listaAdjacente, i - SIZE - 1);  // Vizinho superior esquerdo
        }
        if (lin > 0 && col < SIZE - 1) {
            addVert(grafo[i].listaAdjacente, i - SIZE + 1);  // Vizinho superior direito
        }
        if (lin < SIZE - 1 && col > 0) {
            addVert(grafo[i].listaAdjacente, i + SIZE - 1);  // Vizinho inferior esquerdo
        }
        if (lin < SIZE - 1 && col < SIZE - 1) {
            addVert(grafo[i].listaAdjacente, i + SIZE + 1);  // Vizinho inferior direito
        }
    }

    // Chamada da função de coloração do grafo
    colorirGrafo(grafo);

    // Contagem do número de provas diferentes e distribuição
    int numProvas = 0;
    int numCadaProva[SIZE * SIZE] = {0};
    int provaPorAluno[SIZE * SIZE];

    for (int i = 0; i < SIZE * SIZE; i++) {
        if (grafo[i].cor > numProvas) {
            numProvas = grafo[i].cor;
        }
        numCadaProva[grafo[i].cor]++;
        provaPorAluno[i] = grafo[i].cor;
    }

    // Impressão dos resultados
    printf("Numero de provas diferentes: %d\n", numProvas);
    printf("Quantidade de cada prova:\n");
    for (int i = 1; i <= numProvas; i++) {
        printf("Prova %d: %d\n", i, numCadaProva[i]);
    }

    printf("\nDistribuicao das provas pelos alunos:\n");
    for (int i = 0; i < SIZE * SIZE; i++) {
        printf("Aluno %d: Prova %d de Cor: %s\n", i+1, provaPorAluno[i], cores[provaPorAluno[i]]);
    }


    return 0;
}