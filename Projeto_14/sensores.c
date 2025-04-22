#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "estrutura.h"

// Funcao para adicionar um sensor ou atuador a um dispositivo
void adicionarSensor(ListaDisp** lista) {
    if (*lista == NULL) {
        printf("Nenhum dispositivo cadastrado. Adicione um dispositivo primeiro.\n");
        return;
    }

    int idDispositivo;
    printf("Digite o ID do dispositivo para adicionar o sensor ou acionador: ");
    scanf("%d", &idDispositivo);

    ListaDisp* atual = *lista;
    while (atual != NULL && atual->id != idDispositivo) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Dispositivo com ID %d nao encontrado.\n", idDispositivo);
        return;
    }

    ListaSensores* novoSensor = (ListaSensores*)malloc(sizeof(ListaSensores));
    novoSensor->id = idSensor++;  // Assumindo que idSensor e uma variavel global

    printf("Digite o tipo (Sensor ou Atuador): ");
    scanf(" %[^\n]", novoSensor->tipo);

    printf("Digite o subtipo (temperatura, umidade, movimento, etc): ");
    scanf(" %[^\n]", novoSensor->subtipo);

    printf("Digite o valor: ");
    scanf("%f", &novoSensor->valor);  // CORRIGIDO: antes lia string em campo int

    novoSensor->prox = atual->sensores;
    atual->sensores = novoSensor;

    printf("Sensor ou acionador adicionado com sucesso ao dispositivo ID %d.\n", idDispositivo);
}

// Funcao para listar sensores de um dispositivo especifico
void listarSensores(ListaDisp* lista) {
    if (lista == NULL) {
        printf("Nenhum dispositivo cadastrado.\n");
        return;
    }

    int idDispositivo;
    printf("Digite o ID do dispositivo para listar os sensores ou acionadores: ");
    scanf("%d", &idDispositivo);

    ListaDisp* atual = lista;
    while (atual != NULL && atual->id != idDispositivo) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Dispositivo com ID %d nao encontrado.\n", idDispositivo);
        return;
    }

    ListaSensores* sensor = atual->sensores;
    if (sensor == NULL) {
        printf("Nenhum sensor ou acionador encontrado para o dispositivo ID %d.\n", idDispositivo);
    } else {
        printf("\nSensores ou Acionadores do Dispositivo ID %d:\n", idDispositivo);
        while (sensor != NULL) {
            printf("  ID: %d\n", sensor->id);
            printf("  Tipo: %s\n", sensor->tipo);
            printf("  Subtipo: %s\n", sensor->subtipo);
            printf("  Valor: %f\n\n", sensor->valor);
            sensor = sensor->prox;
        }
    }
}

// Funcao para remover sensor por ID
void removerSensor(ListaDisp* lista) {
    if (lista == NULL) {
        printf("Nenhum dispositivo cadastrado.\n");
        return;
    }

    int idDispositivo, idSensorRemover;
    printf("Digite o ID do dispositivo: ");
    scanf("%d", &idDispositivo);
    printf("Digite o ID do sensor ou acionador a remover: ");
    scanf("%d", &idSensorRemover);

    ListaDisp* atual = lista;
    while (atual != NULL && atual->id != idDispositivo) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Dispositivo com ID %d nao encontrado.\n", idDispositivo);
        return;
    }

    ListaSensores* sensor = atual->sensores;
    ListaSensores* anterior = NULL;

    while (sensor != NULL && sensor->id != idSensorRemover) {
        anterior = sensor;
        sensor = sensor->prox;
    }

    if (sensor == NULL) {
        printf("Sensor com ID %d nao encontrado no dispositivo %d.\n", idSensorRemover, idDispositivo);
        return;
    }

    if (anterior == NULL) {
        atual->sensores = sensor->prox;
    } else {
        anterior->prox = sensor->prox;
    }

    free(sensor);
    printf("Sensor ou acionador removido com sucesso.\n");
}

// Verifica se ha pelo menos um dispositivo cadastrado
int verficarSeHaDisp(ListaDisp** lista) {
    return (*lista != NULL);
}
