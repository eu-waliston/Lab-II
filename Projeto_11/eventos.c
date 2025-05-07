#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "estrutura.h"

void inicializarFilas(FilaEventos* fila) {
    fila->Alta = NULL;
    fila->Media = NULL;
    fila->Baixa = NULL;
}

void adicionarEvento(FilaEventos* fila, ListaDisp* lista, int idDispositivo, int idSensor, char* descricao, char prioridade) {
    ListaDisp* disp = lista;
    while (disp != NULL && disp->id != idDispositivo) disp = disp->prox;
    if (!disp) {
        printf("Dispositivo com ID %d nao encontrado.\n", idDispositivo);
        return;
    }

    ListaSensores* sensor = disp->sensores;
    while (sensor != NULL && sensor->id != idSensor) sensor = sensor->prox;
    if (!sensor) {
        printf("Sensor com ID %d nao encontrado no dispositivo %d.\n", idSensor, idDispositivo);
        return;
    }

    Evento* novo = (Evento*) malloc(sizeof(Evento));
    novo->dispositivo = disp;
    novo->sensor = sensor;
    strcpy(novo->descricao, descricao);
    novo->prox = NULL;

    Evento** inicio = NULL;
    Evento** fim = NULL;

    if (prioridade == 'A') {
        inicio = &fila->Alta;
        fim = &fila->Alta;
    } else if (prioridade == 'M') {
        inicio = &fila->Media;
        fim = &fila->Media;
    } else {
        inicio = &fila->Baixa;
        fim = &fila->Baixa;
    }

    if (*inicio == NULL) {
        *inicio = *fim = novo;
    } else {
        (*fim)->prox = novo;
        *fim = novo;
    }

    printf("Evento adicionado com sucesso!\n");
}

void listarEventos(FilaEventos* fila) {
    Evento* atual;

    printf("\n=========== EVENTOS AGENDADOS ===========\n");

    // Alta prioridade
    printf("\n[Prioridade ALTA]\n");
    atual = fila->Alta;
    if (!atual) {
        printf("Nenhum evento.\n");
    }
    while (atual) {
        printf("- Evento: %s | Dispositivo ID: %d (%s) | Sensor ID: %d (%s)\n",
               atual->descricao,
               atual->dispositivo->id, atual->dispositivo->descricao,
               atual->sensor->id, atual->sensor->nome);
        atual = atual->prox;
    }

    // Média prioridade
    printf("\n[Prioridade MÉDIA]\n");
    atual = fila->Media;
    if (!atual) {
        printf("Nenhum evento.\n");
    }
    while (atual) {
        printf("- Evento: %s | Dispositivo ID: %d (%s) | Sensor ID: %d (%s)\n",
               atual->descricao,
               atual->dispositivo->id, atual->dispositivo->descricao,
               atual->sensor->id, atual->sensor->nome);
        atual = atual->prox;
    }

    // Baixa prioridade
    printf("\n[Prioridade BAIXA]\n");
    atual = fila->Baixa;
    if (!atual) {
        printf("Nenhum evento.\n");
    }
    while (atual) {
        printf("- Evento: %s | Dispositivo ID: %d (%s) | Sensor ID: %d (%s)\n",
               atual->descricao,
               atual->dispositivo->id, atual->dispositivo->descricao,
               atual->sensor->id, atual->sensor->nome);
        atual = atual->prox;
    }

    printf("=========================================\n");
}


void executarEvento(FilaEventos* fila) {
    Evento** filaAtual = NULL;

    if (fila->Alta) filaAtual = &fila->Alta;
    else if (fila->Media) filaAtual = &fila->Media;
    else if (fila->Baixa) filaAtual = &fila->Baixa;
    else {
        printf("Nenhum evento agendado.\n");
        return;
    }

    Evento* evento = *filaAtual;
    *filaAtual = evento->prox;

    printf("\nExecutando evento: %s\n", evento->descricao);

    if (strcmp(evento->dispositivo->status, "Ligado") == 0) {
        strcpy(evento->dispositivo->status, "Desligado");
    } else {
        strcpy(evento->dispositivo->status, "Ligado");
    }

    free(evento);
}
