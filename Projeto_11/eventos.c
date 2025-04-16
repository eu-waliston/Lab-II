#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "estrutura.h"

void inicializarFilas(FilaEventos* fila) {
    fila->Alta = fila->Alta = NULL;
    fila->Media = fila->Media = NULL;
    fila->Baixa = fila->Baixa = NULL;
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

    printf("\n[ALTA prioridade]\n");
    atual = fila->Alta;
    while (atual) {
        printf("- %s (Disp %d, Sensor %d)\n", atual->descricao, atual->dispositivo->id, atual->sensor->id);
        atual = atual->prox;
    }

    printf("[MEDIA prioridade]\n");
    atual = fila->Media;
    while (atual) {
        printf("- %s (Disp %d, Sensor %d)\n", atual->descricao, atual->dispositivo->id, atual->sensor->id);
        atual = atual->prox;
    }

    printf("[BAIXA prioridade]\n");
    atual = fila->Baixa;
    while (atual) {
        printf("- %s (Disp %d, Sensor %d)\n", atual->descricao, atual->dispositivo->id, atual->sensor->id);
        atual = atual->prox;
    }
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
    evento->dispositivo->status = !evento->dispositivo->status;
    printf("Status do dispositivo %d alterado para: %s\n", evento->dispositivo->id,
           evento->dispositivo->status ? "Ligado" : "Desligado");

    free(evento);
}
