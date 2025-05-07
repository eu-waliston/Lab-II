#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "estrutura.h"

// Funcao para adicionar um sensor ou atuador
void adicionarSensor(ListaDisp** lista) {
    ListaDisp* atual = *lista;
    ListaSensores* novoSensor = (ListaSensores*)malloc(sizeof(ListaSensores));
    novoSensor->id = idSensor++; 

    int idTipo;
    do {
        printf("Digite o tipo:\n1 - Sensor\n2 - Atuador\nEscolha: ");
        scanf("%d", &idTipo);

        if (idTipo == 1) {
            strcpy(novoSensor->tipo, "Sensor");
        } else if (idTipo == 2) {
            strcpy(novoSensor->tipo, "Atuador");
        } else {
            printf("Entrada invalida. Por favor, digite 1 para Sensor ou 2 para Atuador.\n");
        }
    } while (idTipo != 1 && idTipo != 2);

    printf("Digite o subtipo (temperatura, umidade, movimento, etc): ");
    scanf(" %[^\n]", novoSensor->subtipo);
    printf("Digite o valor: ");
    scanf("%f", &novoSensor->valor); 

    novoSensor->prox = atual->sensores;
    atual->sensores = novoSensor;

    printf("Sensor ou acionador adicionado com sucesso .\n");
}

// Funcao para adicionar um sensor ou atuador a um dispositivo existente
void adicionarSensorNoDisp(ListaDisp** lista) {
    ListaDisp* disp = obterDispositivoPorID(*lista);
    if (!disp) return;
    adicionarSensor(&disp);
}



// Funcao para listar sensores de um dispositivo especifico
void listarSensores(ListaDisp* lista) {
    ListaDisp* disp = obterDispositivoPorID(lista);
    if (!disp) return;

    ListaSensores* sensor = disp->sensores;
    if (!sensor) {
        printf("Nenhum sensor ou atuador encontrado para este dispositivo.\n");
        return;
    }

    printf("\nSensores ou Atuadores do Dispositivo ID %d:\n", disp->id);
    while (sensor) {
        printf("  ID: %d\n  Tipo: %s\n  Subtipo: %s\n  Valor: %.2f\n\n",
               sensor->id, sensor->tipo, sensor->subtipo, sensor->valor);
        sensor = sensor->prox;
    }
}

// Funcao para remover sensor por ID
void removerSensor(ListaDisp* lista) {
    ListaDisp* disp = obterDispositivoPorID(lista);
    if (!disp) return;

    ListaSensores* anterior = NULL;
    ListaSensores* sensor = obterSensorPorID(disp, &anterior);
    if (!sensor) return;

    if (anterior == NULL)
        disp->sensores = sensor->prox;
    else
        anterior->prox = sensor->prox;

    free(sensor);
    printf("Sensor ou atuador removido com sucesso do dispositivo ID %d.\n", disp->id);
}


// Verifica se ha pelo menos um dispositivo cadastrado
int verficarSeHaDisp(ListaDisp** lista) {
    return (*lista != NULL);
}
