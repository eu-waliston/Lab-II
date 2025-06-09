#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estrutura.h"

NodeArvore* criarNoArvore(const char* timestamp, float valor) {
    NodeArvore* novo = (NodeArvore*)malloc(sizeof(NodeArvore));
    strcpy(novo->timestamp, timestamp);
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

NodeArvore* construirArvoreBalanceada(Valor** array, int inicio, int fim) {
    if (inicio > fim) return NULL;
    int meio = (inicio + fim) / 2;
    NodeArvore* raiz = criarNoArvore(array[meio]->timestamp, array[meio]->valor);
    raiz->esquerda = construirArvoreBalanceada(array, inicio, meio - 1);
    raiz->direita = construirArvoreBalanceada(array, meio + 1, fim);
    return raiz;
}

void liberarArvore(NodeArvore* raiz) {
    if (!raiz) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

void mostrarArvoreInOrder(NodeArvore* raiz) {
    if (!raiz) return;
    mostrarArvoreInOrder(raiz->esquerda);
    printf("%s -> %.2f\n", raiz->timestamp, raiz->valor);
    mostrarArvoreInOrder(raiz->direita);
}

float buscarTimestamp(NodeArvore* raiz, const char* timestamp) {
    while (raiz != NULL) {
        int cmp = strcmp(timestamp, raiz->timestamp);
        if (cmp == 0) return raiz->valor;
        else if (cmp < 0) raiz = raiz->esquerda;
        else raiz = raiz->direita;
    }
    return -1.0f;
}

void construirArvoreParaSensor(ListaSensores* sensor) {
    // contar
    int count = 0;
    Valor* atual = sensor->valores;
    while (atual) {
        count++;
        atual = atual->prox;
    }
    if (count == 0) return;

    // copiar para vetor
    Valor** array = malloc(count * sizeof(Valor*));
    atual = sensor->valores;
    for (int i = 0; i < count; i++) {
        array[i] = atual;
        atual = atual->prox;
    }

    // ordenar
    qsort(array, count, sizeof(Valor*), compararTimestamps);

    // construir
    sensor->arvoreTimestamps = construirArvoreBalanceada(array, 0, count - 1);
    free(array);
}

void buscarComTempo(NodeArvore* raiz, const char* timestamp) {
    clock_t inicio = clock();
    float resultado = buscarTimestamp(raiz, timestamp);
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000.0;

    if (resultado == -1.0f)
        printf("Timestamp nao encontrado.\n");
    else
        printf("Valor encontrado: %.2f\n", resultado);

    printf("Tempo de busca: %.3f ms\n", tempo);
}
