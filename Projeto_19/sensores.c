#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "estrutura.h"


void adicionarSensor(ListaDisp* lista) {
    ListaSensores* novoSensor = (ListaSensores*)malloc(sizeof(ListaSensores));
    novoSensor->id = ++(lista->contadorSensores);
    novoSensor->valores = NULL;
    novoSensor->prox = NULL;

    int idTipo;
    do {
        printf("Digite o tipo:\n1 - Sensor\n2 - Atuador\nEscolha: ");
        scanf("%d", &idTipo);

        if (idTipo == 1 || idTipo == 2) {
            printf("Digite o subtipo (temperatura, umidade, movimento, etc): ");
            scanf(" %[^\n]", novoSensor->subtipo);

            if (idTipo == 1) {
                strcpy(novoSensor->tipo, "Sensor");
                valorAtual(novoSensor);
            } else {
                strcpy(novoSensor->tipo, "Atuador");
            }

            novoSensor->prox = lista->sensores;
            lista->sensores = novoSensor;

            printf("Sensor ou atuador adicionado com sucesso.\n");

        } else {
            printf("Entrada invalida. Por favor, digite 1 para Sensor ou 2 para Atuador.\n");
        }
    } while (idTipo != 1 && idTipo != 2);
}


// Funcao para adicionar um sensor ou atuador a um dispositivo existente
void adicionarSensorNoDisp(ListaDisp** lista) {
    ListaDisp* disp = obterDispositivoPorID(*lista);
    if (!disp) return;
    adicionarSensor(disp);
}

// Função para listar sensores de um dispositivo
void listarSensores(ListaDisp* lista, int num) {
    ListaDisp* disp = lista;
    
        ListaSensores* sensor = disp->sensores;
        if (!sensor) {
            printf("Nenhum sensor ou atuador encontrado.\n");
            return;
        }

        printf("\nSensores ou Atuadores do Dispositivo ID %d:\n", disp->id);
        while (sensor != NULL){
            printf("    ID: %d\n  Tipo: %s\n  Subtipo: %s\n", sensor->id, sensor->tipo, sensor->subtipo);
            Valor* val = sensor->valores;
            while (val) {
                printf("    Valor: %.2f - Timestamp: %s\n", val->valor, val->timestamp);
                val = val->prox;
            }
            sensor = sensor->prox;
        }
}


// Função para remover sensor por ID
void removerSensor(ListaDisp* lista) {
    ListaDisp* disp = obterDispositivoPorID(lista);
    if (!disp) return;

    ListaSensores* anterior = NULL;
    ListaSensores* sensor = obterSensorPorID(disp, &anterior);
    if (!sensor) return;

    // Liberar lista de valores
    Valor* val = sensor->valores;
    while (val) {
        Valor* temp = val;
        val = val->prox;
        free(temp);
    }

    if (anterior == NULL)
        disp->sensores = sensor->prox;
    else
        anterior->prox = sensor->prox;

    free(sensor);
    printf("Sensor ou atuador removido com sucesso do dispositivo ID %d.\n", disp->id);
}

// Verifica se há pelo menos um dispositivo cadastrado
int verficarSeHaDisp(ListaDisp** lista) {
    return (*lista != NULL);
}

// Incluir valores em um determinado sensor
void incluirValoresSensor(ListaDisp* lista) {
    float valor;
    char timestamp[30];
    
    // Coletar dados do evento do usuario
    ListaDisp* disp = obterDispositivoPorID(lista);
    if (!disp) return;

    ListaSensores* anterior = NULL;
    ListaSensores* sensor = obterSensorPorID(disp, &anterior);
    if (!sensor) return;
    if (strcmp(sensor->tipo, "Atuador") == 0) {
        printf("Nao e permitido inserir valores em um atuador.\n");
        return;
    }

    printf("Digite o valor: ");
    scanf("%f", &valor);
    
    obterTimestampAtual(timestamp, sizeof(timestamp));

    // Verificar duplicatas
    Valor* atual = sensor->valores;
    while (atual != NULL) {
        if (strcmp(atual->timestamp, timestamp) == 0 && atual->valor == valor) {
            printf("Valor já registrado\n");
            return;
        }
        atual = atual->prox;
    }

    // Criar novo valor
    Valor* novo = (Valor*)malloc(sizeof(Valor));
    strcpy(novo->timestamp, timestamp);
    novo->valor = valor;
    novo->prox = NULL;

    novo->prox = sensor->valores;
    sensor->valores = novo;
    printf("Valor incluido com sucesso.\n");
}

