#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definir o tipo de status do dispositivo
typedef enum {LIGADO, DESLIGADO, OFFLINE, COM_ERRO} Status;

// Definir os tipos de dispositivos
typedef enum {LAMPADE, CAMERA, TOMADA} TipoDispositivo;

// Definir o tipo de sensor
typedef enum {TEMPERATURA, UMIDADE, MOVIMENTO} TipoSensor;

// Definir a estrutura Sensor
typedef struct {
    int id; // Identificador único para o sensor
    TipoSensor tipo;
    float valor; // Valor do sensor (temperatura, umidade, etc.)
} Sensor;

// Definir a estrutura Dispositivo
typedef struct {
    int id; // Identificador único para o dispositivo
    char descricao[100];
    TipoDispositivo tipo;
    Status status;
    Sensor** sensores; // Lista dinâmica de sensores
    int numSensores;   // Número de sensores no dispositivo
} Dispositivo;

// Função para criar um novo dispositivo
Dispositivo* criarDispositivo(int id, const char* descricao, TipoDispositivo tipo, Status status) {
    Dispositivo* dispositivo = (Dispositivo*)malloc(sizeof(Dispositivo));
    if (!dispositivo) {
        printf("Erro ao alocar memória para o dispositivo\n");
        return NULL;
    }
    dispositivo->id = id;
    strcpy(dispositivo->descricao, descricao);
    dispositivo->tipo = tipo;
    dispositivo->status = status;
    dispositivo->sensores = NULL;
    dispositivo->numSensores = 0;
    return dispositivo;
}

// Função para liberar memória de um dispositivo
void liberarDispositivo(Dispositivo* dispositivo) {
    if (dispositivo) {
        for (int i = 0; i < dispositivo->numSensores; i++) {
            free(dispositivo->sensores[i]);
        }
        free(dispositivo->sensores);
        free(dispositivo);
    }
}

// Função para criar um novo sensor
Sensor* criarSensor(int id, TipoSensor tipo, float valor) {
    Sensor* sensor = (Sensor*)malloc(sizeof(Sensor));
    if (!sensor) {
        printf("Erro ao alocar memória para o sensor\n");
        return NULL;
    }
    sensor->id = id;
    sensor->tipo = tipo;
    sensor->valor = valor;
    return sensor;
}

// Função para liberar memória de um sensor
void liberarSensor(Sensor* sensor) {
    if (sensor) {
        free(sensor);
    }
}
