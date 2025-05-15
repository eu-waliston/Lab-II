#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "estrutura.h"

// Libera memoria Dispositivo/ Sensores
void liberarMemoria(ListaDisp* lista) {
    while (lista != NULL) {
        ListaSensores* sensor = lista->sensores;
        while (sensor != NULL) {
            ListaSensores* tempSensor = sensor;
            sensor = sensor->prox;
            free(tempSensor);
        }
        ListaDisp* tempDisp = lista;
        lista = lista->prox;
        free(tempDisp);
    }
}
// Libera memoria fila/ Eventos
void liberarEventos(Evento* evento) {
    while (evento != NULL) {
        Evento* temp = evento;
        evento = evento->prox;
        free(temp);
    }
}
void liberarFilaEventos(FilaEventos* fila) {
    if (fila == NULL) 
        return;
    liberarEventos(fila->Alta);
    liberarEventos(fila->Media);
    liberarEventos(fila->Baixa);
    free(fila);
}


void mostrarInformacao(ListaDisp* lista){
    ListaDisp* atual = lista;
    printf("\nDispositivo ID: %d\n", atual->id);
    printf("Descricao: %s\n", atual->descricao);
    printf("Tipo: %s\n", atual->tipo);
    printf("Status: %s\n", atual->status);

    ListaSensores* sensor = atual->sensores;
    if (sensor == NULL) {
        printf("Nenhum sensor cadastrado para este dispositivo.\n");
    } else {
        printf("\nSensores:\n");
        while (sensor != NULL) {
            printf("  ID do Sensor: %d\n", sensor->id);
            printf("  Tipo: %s\n", sensor->tipo);
            printf("  Subtipo: %s\n\n", sensor->subtipo);
            sensor = sensor->prox;
        }
    }
}


ListaDisp* obterDispositivoPorID(ListaDisp* lista) {
    int idDispositivo;
    printf("Digite o ID do dispositivo: ");
    scanf("%d", &idDispositivo); 

    while (lista && lista->id != idDispositivo)
        lista = lista->prox;

    if (lista == NULL)
        printf("Dispositivo com ID %d nao encontrado.\n", idDispositivo);

    return lista;
}


ListaSensores* obterSensorPorID(ListaDisp* lista, ListaSensores** anterior) {
    int idSensor;
    printf("Digite o ID do sensor ou atuador: ");
    scanf("%d", &idSensor);

    ListaSensores* atual = lista->sensores;
    *anterior = NULL;

    while (atual && atual->id != idSensor) {
        *anterior = atual;
        atual = atual->prox;
    }

    if (!atual) {
        printf("Sensor com ID %d nao encontrado no dispositivo ID %d.\n", idSensor, lista->id);
    }
    return atual;
}