#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "estrutura.h"


void adicionarSensor(ListaDisp** lista) {
    if (*lista == NULL) {
        printf("Nenhum dispositivo cadastrado. Adicione um dispositivo primeiro.\n");
        return;
    }
    
    int idDispositivo;
    printf("Digite o ID do dispositivo para adicionar o sensor/acionador: ");
    scanf("%d", &idDispositivo);
    
    ListaDisp* atual = *lista;
    while (atual != NULL && atual->id != idDispositivo) {
        atual = atual->prox;
    }
    
    if (atual == NULL) {
        printf("Dispositivo com ID %d não encontrado.\n", idDispositivo);
        return;
    }
    
    ListaSensores* novoSensor = (ListaSensores*)malloc(sizeof(ListaSensores));
    novoSensor->id = idSensor++;
    printf("Digite o tipo (Sensor ou Atuador): ");
    scanf(" %[^\n]", novoSensor->tipo);
    printf("Digite o subtipo (temperatura, umidade, movimento, etc.): ");
    scanf(" %[^\n]", novoSensor->subtipo);
    novoSensor->prox = atual->sensores;
    atual->sensores = novoSensor;
    
    printf("Sensor/acionador adicionado com sucesso ao dispositivo ID %d.\n", idDispositivo);
    }
    
    void listarSensores(ListaDisp* lista) {
    if (lista == NULL) {
        printf("Nenhum dispositivo cadastrado.\n");
        return;
    }
    
    int idDispositivo;
    printf("Digite o ID do dispositivo para listar os sensores/acionadores: ");
    scanf("%d", &idDispositivo);
    
    ListaDisp* atual = lista;
    while (atual != NULL && atual->id != idDispositivo) {
        atual = atual->prox;
    }
    
    if (atual == NULL) {
        printf("Dispositivo com ID %d não encontrado.\n", idDispositivo);
        return;
    }
    
    ListaSensores* sensor = atual->sensores;
    if (sensor == NULL) {
        printf("Nenhum sensor/acionador encontrado para o dispositivo ID %d.\n", idDispositivo);
    } else {
        printf("\nSensores/Acionadores do Dispositivo ID %d:\n", idDispositivo);
        while (sensor != NULL) {
            printf("  ID: %d\n  Tipo: %s\n  Subtipo: %s\n", sensor->id, sensor->tipo, sensor->subtipo);
            sensor = sensor->prox;
        }
    }
    }
    
    void removerSensor(ListaDisp* lista) {
    if (lista == NULL) {
        printf("Nenhum dispositivo cadastrado.\n");
        return;
    }
    
    int idDispositivo, idSensorRemover;
    printf("Digite o ID do dispositivo: ");
    scanf("%d", &idDispositivo);
    printf("Digite o ID do sensor/acionador a remover: ");
    scanf("%d", &idSensorRemover);
    
    ListaDisp* atual = lista;
    while (atual != NULL && atual->id != idDispositivo) {
        atual = atual->prox;
    }
    
    if (atual == NULL) {
        printf("Dispositivo com ID %d não encontrado.\n", idDispositivo);
        return;
    }
    
    ListaSensores* sensor = atual->sensores;
    ListaSensores* anterior = NULL;
    
    while (sensor != NULL && sensor->id != idSensorRemover) {
        anterior = sensor;
        sensor = sensor->prox;
    }
    
    if (sensor == NULL) {
        printf("Sensor com ID %d não encontrado no dispositivo %d.\n", idSensorRemover, idDispositivo);
        return;
    }
    
    if (anterior == NULL) {
        atual->sensores = sensor->prox;
    } else {
        anterior->prox = sensor->prox;
    }
    
    free(sensor);
    printf("Sensor/acionador removido com sucesso.\n");
    }
    
    // Opcional: verificar se há dispositivos cadastrados
    int verficarSeHaDisp(ListaDisp** lista) {
    return (*lista != NULL);
    }
    
    
    
