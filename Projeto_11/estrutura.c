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


