#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

int idDispositivo = 1;
int idSensor = 1;

// ---------------------------
// SensorAcionador.c
// ---------------------------

void adicionarSensor(ListaSensores** lista, int n) {
    char tipoSensorAtuador[50], subTipoSensorAtuador[50];

    printf("Digite o tipo (Sensor ou Atuador) %d ", n);
    scanf(" %[^\n]", tipoSensorAtuador);

    printf("Digite o  subtipo do sensor (temperatura, umidade, movimento, etc.)");
    scanf(" %[^\n]", subTipoSensorAtuador);



    //adicionarSensor(&(novo->sensores), nomeSensor);

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


//void adicionarSensor(ListaSensores** lista, char nome[]) {
//    ListaSensores* novo = (ListaSensores*)malloc(sizeof(ListaSensores));
//    novo->id = idSensor++;
//    strcpy(novo->nome, nome);
//    novo->prox = *lista;
//    *lista = novo;
//}

/*
    printf("\n===== MENU SENSOR OU ACIONADOR =====\n");
    printf("1. Adicionar sensor ao dispositivo\n");
    printf("2. Listar sensores de um dispositivo\n");
    printf("3. Remover sensor de um dispositivo\n");
*/


//void adicionarSensor(ListaDisp* lista, int idDispositivo, int idSensor, const char* nome, const char* tipo, const char* subtipo) {
//    ListaDisp* atual = lista;
//    while (atual != NULL) {
//        if (atual->id == idDispositivo) {
//            ListaSensores* novo = (ListaSensores*) malloc(sizeof(ListaSensores));
//            novo->id = idSensor;
//            strcpy(novo->nome, nome);
//            strcpy(novo->tipo, tipo);
//            strcpy(novo->subtipo, subtipo);
//            novo->prox = atual->sensores;
//            atual->sensores = novo;
//            printf("Sensor adicionado ao dispositivo %d com sucesso!\n", idDispositivo);
//            return;
//        }
//        atual = atual->prox;
//    }
//    printf("Dispositivo com ID %d nao encontrado.\n", idDispositivo);
//}


