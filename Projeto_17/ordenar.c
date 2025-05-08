//
// Created by we on 08/05/25.
//


#include <stdlib.h>
#include <string.h>

// Estrutura auxiliar para ordenar
typedef struct {
    char timestamp[30];
    float valor;
} ValorTemp;

// Funções de comparação
int compararCrescente(const void* a, const void* b) {
    return strcmp(((ValorTemp*)a)->timestamp, ((ValorTemp*)b)->timestamp);
}

int compararDecrescente(const void* a, const void* b) {
    return strcmp(((ValorTemp*)b)->timestamp, ((ValorTemp*)a)->timestamp);
}

// Função para listar os valores ordenados
void listarValoresSensor(ListaDisp* lista, int idDispositivo, int idSensor, int ordemCrescente) {
    ListaDisp* disp = lista;
    while (disp && disp->id != idDispositivo) disp = disp->prox;
    if (!disp) {
        printf("Dispositivo com ID %d não encontrado.\n", idDispositivo);
        return;
    }

    ListaSensores* sensor = disp->sensores;
    while (sensor && sensor->id != idSensor) sensor = sensor->prox;
    if (!sensor) {
        printf("Sensor com ID %d não encontrado no dispositivo %d.\n", idSensor, idDispositivo);
        return;
    }

    // Contar quantos valores temos
    int count = 0;
    ListaValores* atual = sensor->valores;
    while (atual) {
        count++;
        atual = atual->prox;
    }

    if (count == 0) {
        printf("Nenhum valor registrado para este sensor.\n");
        return;
    }

    // Copiar os valores para um vetor
    ValorTemp* valores = (ValorTemp*) malloc(count * sizeof(ValorTemp));
    atual = sensor->valores;
    for (int i = 0; i < count; i++) {
        strcpy(valores[i].timestamp, atual->timestamp);
        valores[i].valor = atual->valor;
        atual = atual->prox;
    }

    // Ordenar
    qsort(valores, count, sizeof(ValorTemp),
          ordemCrescente ? compararCrescente : compararDecrescente);

    // Imprimir
    printf("Valores do sensor %d (ordem %s):\n", idSensor, ordemCrescente ? "crescente" : "decrescente");
    for (int i = 0; i < count; i++) {
        printf("  [%s] %.2f\n", valores[i].timestamp, valores[i].valor);
    }

    free(valores);
}
