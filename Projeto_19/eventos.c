#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "estrutura.h"

// Inicializa as filas de eventos com NULL
void inicializarFilas(FilaEventos* fila) {
    fila->Alta = NULL;
    fila->Media = NULL;
    fila->Baixa = NULL;
}

// Funcao para adicionar um evento a fila correspondente
void adicionarEvento(FilaEventos* fila, ListaDisp* lista) {
    int idDisp, idSensor, valor, prioridade;
    char descricao[100];

    // Coletar dados do evento do usuario
    ListaDisp* disp = obterDispositivoPorID(lista);
    if (!disp) return;

    ListaSensores* anterior = NULL;
    ListaSensores* sensor = obterSensorPorID(disp, &anterior);
    if (!sensor) return;

    printf("Digite a descricao do evento: ");
    scanf(" %[^\n]", descricao);

    printf("Digite o novo valor: ");
    scanf("%d", &valor);

    printf("Digite a prioridade (1 para alta, 2 para media, 3 para baixa): ");
    scanf("%d", &prioridade);

    
    // Alocar memoria para o novo evento
    Evento* novo = (Evento*) malloc(sizeof(Evento));
    if (!novo) {
        printf("Erro ao alocar memoria para o evento\n");
        return;
    }
    novo->dispositivo = disp;
    novo->sensor = sensor;
    novo->valor = valor;
    strcpy(novo->descricao, descricao);
    novo->prox = NULL;

    if (!fila) {
        printf("ERRO: ponteiro fila e NULL\n");
        return;
    }

    // Escolher a fila com base na prioridade informada
    Evento** filaDestino = NULL;
    if (prioridade == 1) {
        filaDestino = &fila->Alta;
    } else if (prioridade == 2) {
        filaDestino = &fila->Media;
    } else if (prioridade == 3) {
        filaDestino = &fila->Baixa;
    } else {
        printf("Prioridade invalida. Deve ser 1 (alta), 2 (media) ou 3 (baixa)\n");
        free(novo);
        return;
    }

    // Inserir o evento na fila correspondente
    if (*filaDestino == NULL) {
        *filaDestino = novo;
    } else {
        Evento* aux = *filaDestino;
        while (aux->prox) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    printf("Evento adicionado com sucesso\n");
}

// Lista todos os eventos nas filas por prioridade
void listarEventos(FilaEventos* fila) {
    Evento* atual;

    printf("\n=========== EVENTOS AGENDADOS ===========\n");

    // Listar eventos de prioridade alta
    printf("\n[Prioridade ALTA]\n");
    atual = fila->Alta;
    if (!atual) {
        printf("Nenhum evento\n");
    }
    while (atual) {
        printf("- Evento: %s | Dispositivo ID: %d (%s) | Sensor ID: %d (%s)\n",
               atual->descricao,
               atual->dispositivo->id, atual->dispositivo->descricao,
               atual->sensor->id, atual->sensor->tipo);
        atual = atual->prox;
    }

    // Listar eventos de prioridade media
    printf("\n[Prioridade MEDIA]\n");
    atual = fila->Media;
    if (!atual) {
        printf("Nenhum evento\n");
    }
    while (atual) {
        printf("- Evento: %s | Dispositivo ID: %d (%s) | Sensor ID: %d (%s)\n",
               atual->descricao,
               atual->dispositivo->id, atual->dispositivo->descricao,
               atual->sensor->id, atual->sensor->tipo);
        atual = atual->prox;
    }

    // Listar eventos de prioridade baixa
    printf("\n[Prioridade BAIXA]\n");
    atual = fila->Baixa;
    if (!atual) {
        printf("Nenhum evento\n");
    }
    while (atual) {
        printf("- Evento: %s | Dispositivo ID: %d (%s) | Sensor ID: %d (%s)\n",
               atual->descricao,
               atual->dispositivo->id, atual->dispositivo->descricao,
               atual->sensor->id, atual->sensor->tipo);
        atual = atual->prox;
    }

    printf("=========================================\n");
}

// Executa o proximo evento de maior prioridade
void executarEvento(FilaEventos* fila) {
    if (!fila || (!fila->Alta && !fila->Media && !fila->Baixa)) {
        printf("Nenhum evento para executar\n");
        return;
    }

    Evento* evento = NULL;

    // Selecionar evento da fila de maior prioridade disponivel
    if (fila->Alta) {
        evento = fila->Alta;
        fila->Alta = fila->Alta->prox;
    } else if (fila->Media) {
        evento = fila->Media;
        fila->Media = fila->Media->prox;
    } else if (fila->Baixa) {
        evento = fila->Baixa;
        fila->Baixa = fila->Baixa->prox;
    }

    if (evento) {
        printf("\n========== EXECUTANDO EVENTO ==========\n");
        printf("Descricao: %s\n", evento->descricao);
        printf("Dispositivo: ID %d (%s)\n", evento->dispositivo->id, evento->dispositivo->descricao);
        printf("Sensor: ID %d (%s)\n", evento->sensor->id, evento->sensor->tipo);
        printf("Valor antigo: %f\n", evento->sensor->valor);
        printf("Novo valor: %f\n", evento->valor);

        // atualizar valor do sensor
        evento->sensor->valor = evento->valor;

        printf("Valor do sensor atualizado com sucesso\n");
        printf("=======================================\n");

        // Liberar memoria usada pelo evento
        free(evento);
    }
}

