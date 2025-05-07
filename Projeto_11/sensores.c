#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

int idDispositivo = 1;
int idSensor = 1;

void adicionarSensor(ListaSensores** lista, int n) {
    char tipoSensorAtuador[50], subTipoSensorAtuador[50];

    printf("Digite o tipo (Sensor ou Atuador) %d ", n);
    scanf(" %[^\n]", tipoSensorAtuador);

    printf("Digite o  subtipo do sensor (temperatura, umidade, movimento, etc.)");
    scanf(" %[^\n]", subTipoSensorAtuador);

    ListaSensores* novo = (ListaSensores*)malloc(sizeof(ListaSensores));
    novo->id = idSensor++;
    strcpy(novo->subtipo, subTipoSensorAtuador);
    novo->prox = *lista;
    *lista = novo;
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


