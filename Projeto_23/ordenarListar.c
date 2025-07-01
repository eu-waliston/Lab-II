#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estrutura.h"

void listarValoresSensor(ListaDisp* lista) {
    int ordem;
    
    // Coletar dados do evento do usuário
    ListaDisp* disp = obterDispositivoPorID(lista);
    if (!disp) return;

    ListaSensores* anterior = NULL;
    ListaSensores* sensor = obterSensorPorID(disp, &anterior);
    if (!sensor) return;

    printf("Ordem:\n1 - Crescente\n2 - Decrescente\nEscolha: ");
    scanf("%d", &ordem);

    listarValores(sensor, ordem == 1);
}

int compararTimestamps(const void* a, const void* b) {
    Valor* va = *(Valor**)a;
    Valor* vb = *(Valor**)b;
    return strcmp(va->timestamp, vb->timestamp);
}

void listarValores(ListaSensores* sensor, int ordemCrescente) {
    int count = 0;
    Valor* atual = sensor->valores;

    // Contar elementos
    while (atual) {
        count++;
        atual = atual->prox;
    }

    if (count == 0) {
        printf("Nenhum valor registrado.\n");
        return;
    }

    // Copiar para array
    Valor** array = malloc(count * sizeof(Valor*));
    atual = sensor->valores;
    for (int i = 0; i < count; i++) {
        array[i] = atual;
        atual = atual->prox;
    }

    // Ordenar
    qsort(array, count, sizeof(Valor*), compararTimestamps);

    printf("\nValores do sensor %s (ID %d):\n", sensor->tipo, sensor->id);
    if (!ordemCrescente) {
        for (int i = count - 1; i >= 0; i--)
            printf("%s - %.2f\n", array[i]->timestamp, array[i]->valor);
    } else {
        for (int i = 0; i < count; i++)
            printf("%s - %.2f\n", array[i]->timestamp, array[i]->valor);
    }

    free(array);
}


