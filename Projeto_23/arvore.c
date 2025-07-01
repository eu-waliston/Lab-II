#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estrutura.h"

Arvore* criarArvoreBalanceadaAux(Valor** array, int inicio, int fim) {
    if (inicio > fim) return NULL;
    int meio = (inicio + fim) / 2;
    Arvore* no = (Arvore*)malloc(sizeof(Arvore));
    strcpy(no->timestamp, array[meio]->timestamp);
    no->valor = array[meio]->valor;
    no->esquerda = criarArvoreBalanceadaAux(array, inicio, meio - 1);
    no->direita = criarArvoreBalanceadaAux(array, meio + 1, fim);

    return no;
}

// Transforma lista encadeada de valores em vetor ordenado por timestamp
Arvore* criarArvoreBalanceada(ListaDisp* dispositivos) {
    ListaDisp* disp = obterDispositivoPorID(dispositivos);
    ListaSensores* anterior = NULL;
    ListaSensores* sensor = obterSensorPorID(disp, &anterior);

    // Contar elementos
    int count = 0;
    Valor* temp = sensor->valores;
    while (temp != NULL) {
        count++;
        temp = temp->prox;
    }

    // Copiar para vetor
    Valor** vetor = (Valor**)malloc(count * sizeof(Valor*));
    temp = sensor->valores;
    for (int i = 0; i < count; i++) {
        vetor[i] = temp;
        temp = temp->prox;
    }

   
    qsort(vetor, count, sizeof(Valor*), compararTimestamps);

    // Criar árvore balanceada
    Arvore* raiz = criarArvoreBalanceadaAux(vetor, 0, count - 1);
    free(vetor);
    return raiz;
}

// Função para liberar a árvore
void apagarArvore(Arvore* raiz) {
    if (raiz == NULL) return;
    apagarArvore(raiz->esquerda);
    apagarArvore(raiz->direita);
    free(raiz);
}

// Mostrar árvore 
void mostrarArvore(Arvore* raiz) {
    if (raiz != NULL) {
        mostrarArvore(raiz->esquerda);
        printf("Timestamp: %s - Valor: %.2f\n", raiz->timestamp, raiz->valor);
        mostrarArvore(raiz->direita);
    }
}

// Função para buscar um timestamp com interação
void buscarTimestampMenu(Arvore* raiz) {
    char ts[30];
    printf("Digite o timestamp (formato igual ao registrado): ");
    scanf(" %[^\n]", ts);
    
    float resultado = buscarTimestamp(raiz, ts);

    if (resultado == -1)
        printf("Timestamp nao encontrado.\n");
    else
        printf("Valor encontrado: %.2f\n", resultado);
}


// Função para buscar timestamp
float buscarTimestamp(Arvore* raiz, const char* timestamp) {
    clock_t inicio = clock();

    while (raiz != NULL) {
        int cmp = strcmp(timestamp, raiz->timestamp);
        if (cmp == 0) {
            clock_t fim = clock();
            double tempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;
            printf("Tempo de busca: %.2f ms\n", tempo);
            return raiz->valor;
        } else if (cmp < 0) {
            raiz = raiz->esquerda;
        } else {
            raiz = raiz->direita;
        }
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;
    printf("Tempo de busca: %.2f ms\n", tempo);
    return -1;
}
