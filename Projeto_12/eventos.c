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

void adicionarEvento(FilaEventos* fila, ListaDisp* lista) {
    int idDisp, idSensor, valor, prioridade;
    char descricao[100];

    // Coletar dados do evento
    printf("Digite o id do dispositivo: ");
    scanf("%d", &idDisp);
    getchar(); 
    
    printf("Digite o id do sensor: ");
    scanf("%d", &idSensor);
    getchar(); // limpa \n do buffer
    
    printf("Digite a descricao do evento: ");
    scanf(" %[^\n]", descricao);
    getchar(); // limpa \n do buffer
    
    printf("Digite o novo valor: ");
    scanf("%d", &valor);
    getchar(); // limpa \n do buffer
    
    printf("Digite a prioridade (1 para alta, 2 para media, 3 para baixa): ");
    scanf("%d", &prioridade);
    getchar(); // limpa \n do buffer
    

    // Buscar o dispositivo
    ListaDisp* disp = lista;
    while (disp && disp->id != idDisp) {
        disp = disp->prox;
    }
    if (!disp) {
        printf("Dispositivo %d não encontrado.\n", idDisp);
        return;
    }

    // Buscar o sensor dentro do dispositivo
    ListaSensores* sensor = disp->sensores;
    while (sensor && sensor->id != idSensor) {
        sensor = sensor->prox;
    }
    if (!sensor) {
        printf("Sensor %d não encontrado no dispositivo %d.\n", idSensor, idDisp);
        return;
    }

    // Alocar um novo evento
    Evento* novo = (Evento*) malloc(sizeof(Evento));
    if (!novo) {
        printf("Erro ao alocar memória para o evento.\n");
        return;
    }
    novo->dispositivo = disp;
    novo->sensor = sensor;
    novo->valor = valor;
    strcpy(novo->descricao, descricao);
    novo->prox = NULL;

    // Escolher a fila com base na prioridade
    Evento** filaDestino = NULL;
    if (prioridade == 1) {
        filaDestino = &fila->Alta;
    } else if (prioridade == 2) {
        filaDestino = &fila->Media;
    } else if (prioridade == 3) {
        filaDestino = &fila->Baixa;
    } else {
        printf("Prioridade inválida! Deve ser 1 (alta), 2 (média) ou 3 (baixa).\n");
        free(novo);
        return;
    }

    // Inserir o evento na fila de acordo com a prioridade
    if (*filaDestino == NULL) {
        *filaDestino = novo;
    } else {
        Evento* aux = *filaDestino;
        while (aux->prox) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    printf("Evento adicionado com sucesso!\n");
}


void listarEventos(FilaEventos* fila, ListaDisp* lista) {
    Evento* atual;

    printf("\n[FILA - ALTA PRIORIDADE]\n");
    atual = fila->Alta;
    while (atual) {
        printf(" - %s (Dispositivo: %d, Sensor: %d, Valor: %.1f)\n",
               atual->descricao, atual->dispositivo->id, atual->sensor->id, atual->valor);
        atual = atual->prox;
    }

    printf("\n[FILA - MÉDIA PRIORIDADE]\n");
    atual = fila->Media;
    while (atual) {
        printf(" - %s (Dispositivo: %d, Sensor: %d, Valor: %.1f)\n",
               atual->descricao, atual->dispositivo->id, atual->sensor->id, atual->valor);
        atual = atual->prox;
    }

    printf("\n[FILA - BAIXA PRIORIDADE]\n");
    atual = fila->Baixa;
    while (atual) {
        printf(" - %s (Dispositivo: %d, Sensor: %d, Valor: %.1f)\n",
               atual->descricao, atual->dispositivo->id, atual->sensor->id, atual->valor);
        atual = atual->prox;
    }
}
/*
void executarEvento(FilaEventos* fila) {
    Evento** filaAtual = NULL;

    if (fila->Alta) filaAtual = &fila->Alta;
    else if (fila->Media) filaAtual = &fila->Media;
    else if (fila->Baixa) filaAtual = &fila->Baixa;
    else {
        printf("Nenhum evento a executar.\n");
        return;
    }

    Evento* evento = *filaAtual;
    *filaAtual = evento->prox;

    printf("Executando: %s\n", evento->descricao);

    if (strcmp(evento->dispositivo->status, "Ligado") == 0)
        strcpy(evento->dispositivo->status, "Desligado");
    else
        strcpy(evento->dispositivo->status, "Ligado");

    printf("Novo status do dispositivo %d: %s\n", evento->dispositivo->id, evento->dispositivo->status);
    free(evento);
}
*/
