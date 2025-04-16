//
// Created by we on 07/04/25.
//

#include "estrutura.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------
// GERENCIAMENTO DE SENSORES
// ---------------------------

void adicionarSensor(ListaDisp* lista, int idDispositivo, int idSensor, const char* nome, const char* tipo, const char* subtipo) {
    ListaDisp* atual = lista;
    while (atual != NULL) {
        if (atual->id == idDispositivo) {
            ListaSensores* novo = (ListaSensores*) malloc(sizeof(ListaSensores));
            novo->id = idSensor;
            strcpy(novo->nome, nome);
            strcpy(novo->tipo, tipo);
            strcpy(novo->subtipo, subtipo);
            novo->prox = atual->sensores;
            atual->sensores = novo;
            printf("Sensor adicionado ao dispositivo %d com sucesso!\n", idDispositivo);
            return;
        }
        atual = atual->prox;
    }
    printf("Dispositivo com ID %d nao encontrado.\n", idDispositivo);
}

void listarSensores(ListaDisp* lista, int idDispositivo) {
    ListaDisp* atual = lista;
    while (atual != NULL) {
        if (atual->id == idDispositivo) {
            ListaSensores* sensor = atual->sensores;
            printf("Sensores do dispositivo %d:\n", idDispositivo);
            while (sensor != NULL) {
                printf("ID: %d | Nome: %s | Tipo: %s | Subtipo: %s\n",
                       sensor->id, sensor->nome, sensor->tipo, sensor->subtipo);
                sensor = sensor->prox;
            }
            return;
        }
        atual = atual->prox;
    }
    printf("Dispositivo com ID %d nao encontrado.\n", idDispositivo);
}

void removerSensor(ListaDisp* lista, int idDispositivo, int idSensor) {
    ListaDisp* atual = lista;
    while (atual != NULL) {
        if (atual->id == idDispositivo) {
            ListaSensores* anterior = NULL;
            ListaSensores* atualSensor = atual->sensores;
            while (atualSensor != NULL) {
                if (atualSensor->id == idSensor) {
                    if (anterior == NULL) {
                        atual->sensores = atualSensor->prox;
                    } else {
                        anterior->prox = atualSensor->prox;
                    }
                    free(atualSensor);
                    printf("Sensor %d removido do dispositivo %d.\n", idSensor, idDispositivo);
                    return;
                }
                anterior = atualSensor;
                atualSensor = atualSensor->prox;
            }
        }
        atual = atual->prox;
    }
    printf("Dispositivo ou sensor nao encontrado.\n");
}

// ---------------------------
// GERENCIAMENTO DE FILAS E EVENTOS
// ---------------------------

void inicializarFilas(FilaEventos* fila) {
    fila->inicioAlta = fila->fimAlta = NULL;
    fila->inicioMedia = fila->fimMedia = NULL;
    fila->inicioBaixa = fila->fimBaixa = NULL;
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
        inicio = &fila->inicioAlta;
        fim = &fila->fimAlta;
    } else if (prioridade == 'M') {
        inicio = &fila->inicioMedia;
        fim = &fila->fimMedia;
    } else {
        inicio = &fila->inicioBaixa;
        fim = &fila->fimBaixa;
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
    atual = fila->inicioAlta;
    while (atual) {
        printf("- %s (Disp %d, Sensor %d)\n", atual->descricao, atual->dispositivo->id, atual->sensor->id);
        atual = atual->prox;
    }

    printf("[MEDIA prioridade]\n");
    atual = fila->inicioMedia;
    while (atual) {
        printf("- %s (Disp %d, Sensor %d)\n", atual->descricao, atual->dispositivo->id, atual->sensor->id);
        atual = atual->prox;
    }

    printf("[BAIXA prioridade]\n");
    atual = fila->inicioBaixa;
    while (atual) {
        printf("- %s (Disp %d, Sensor %d)\n", atual->descricao, atual->dispositivo->id, atual->sensor->id);
        atual = atual->prox;
    }
}

void executarEvento(FilaEventos* fila) {
    Evento** filaAtual = NULL;

    if (fila->inicioAlta) filaAtual = &fila->inicioAlta;
    else if (fila->inicioMedia) filaAtual = &fila->inicioMedia;
    else if (fila->inicioBaixa) filaAtual = &fila->inicioBaixa;
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

