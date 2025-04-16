// estrutura.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

Dispositivo* criar_dispositivo(int id, const char *nome) {
    Dispositivo *novo = (Dispositivo*)malloc(sizeof(Dispositivo));
    novo->id = id;
    strncpy(novo->nome, nome, MAX_NOME);
    novo->sensores = NULL;
    novo->prox = NULL;
    return novo;
}

void adicionar_dispositivo(Dispositivo **lista, Dispositivo *novo) {
    novo->prox = *lista;
    *lista = novo;
}

Dispositivo* buscar_dispositivo(Dispositivo *lista, int id) {
    while (lista) {
        if (lista->id == id) return lista;
        lista = lista->prox;
    }
    return NULL;
}

Sensor* criar_sensor(int id, TipoDispositivo tipo, SubtipoSensor subtipo) {
    Sensor *novo = (Sensor*)malloc(sizeof(Sensor));
    novo->id = id;
    novo->tipo = tipo;
    novo->subtipo = subtipo;
    novo->prox = NULL;
    return novo;
}

void adicionar_sensor(Dispositivo *disp, Sensor *novo) {
    novo->prox = disp->sensores;
    disp->sensores = novo;
}

void remover_sensor(Dispositivo *disp, int id_sensor) {
    Sensor *atual = disp->sensores, *anterior = NULL;
    while (atual) {
        if (atual->id == id_sensor) {
            if (anterior) anterior->prox = atual->prox;
            else disp->sensores = atual->prox;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

void listar_sensores(Dispositivo *disp) {
    Sensor *atual = disp->sensores;
    while (atual) {
        printf("ID: %d | Tipo: %s | Subtipo: %d\n",
               atual->id,
               atual->tipo == SENSOR ? "Sensor" : "Atuador",
               atual->subtipo);
        atual = atual->prox;
    }
}

void inicializar_filas(FilaEvento *alta, FilaEvento *media, FilaEvento *baixa) {
    alta->inicio = alta->fim = NULL;
    media->inicio = media->fim = NULL;
    baixa->inicio = baixa->fim = NULL;
}

Evento* criar_evento(int id, Dispositivo *disp, Sensor *sensor, const char *desc, Prioridade prioridade) {
    Evento *novo = (Evento*)malloc(sizeof(Evento));
    novo->id_evento = id;
    novo->dispositivo = disp;
    novo->sensor = sensor;
    strncpy(novo->descricao, desc, 200);
    novo->prioridade = prioridade;
    novo->prox = NULL;
    return novo;
}

void adicionar_evento(FilaEvento *fila, Evento *evento) {
    if (!fila->inicio) {
        fila->inicio = fila->fim = evento;
    } else {
        fila->fim->prox = evento;
        fila->fim = evento;
    }
}

void executar_evento(FilaEvento *alta, FilaEvento *media, FilaEvento *baixa) {
    FilaEvento *fila_exec = NULL;
    if (alta->inicio) fila_exec = alta;
    else if (media->inicio) fila_exec = media;
    else if (baixa->inicio) fila_exec = baixa;

    if (fila_exec && fila_exec->inicio) {
        Evento *ev = fila_exec->inicio;
        printf("Executando Evento ID %d: %s\n", ev->id_evento, ev->descricao);
        fila_exec->inicio = ev->prox;
        if (!fila_exec->inicio) fila_exec->fim = NULL;
        free(ev);
    } else {
        printf("Nenhum evento para executar.\n");
    }
}

void listar_eventos(FilaEvento *fila) {
    Evento *atual = fila->inicio;
    while (atual) {
        printf("Evento ID: %d | Descricao: %s | Prioridade: %d\n",
               atual->id_evento, atual->descricao, atual->prioridade);
        atual = atual->prox;
    }
}

void remover_evento(FilaEvento *fila, int id_evento) {
    Evento *atual = fila->inicio, *anterior = NULL;
    while (atual) {
        if (atual->id_evento == id_evento) {
            if (anterior) anterior->prox = atual->prox;
            else fila->inicio = atual->prox;
            if (atual == fila->fim) fila->fim = anterior;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}
