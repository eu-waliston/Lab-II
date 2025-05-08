//
// Created by we on 08/05/25.
//

#include <time.h>
#include <sys/time.h>

// Gera timestamp no formato "YYYY-MM-DD HH:MM:SS.mmm"
void gerarTimestamp(char* buffer, size_t size) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    struct tm* tm_info = localtime(&tv.tv_sec);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
    int millis = tv.tv_usec / 1000;
    snprintf(buffer + strlen(buffer), size - strlen(buffer), ".%03d", millis);
}

// Insere um valor em um sensor
void inserirValorSensor(ListaDisp* lista, int idDispositivo, int idSensor, float valor) {
    ListaDisp* disp = lista;
    while (disp && disp->id != idDispositivo) disp = disp->prox;
    if (!disp) {
        printf("Dispositivo com ID %d não encontrado.\n", idDispositivo);
        return;
    }

    ListaSensores* sensor = disp->sensores;
    while (sensor && sensor->id != idSensor) sensor = sensor->prox;
    if (!sensor) {
        printf("Sensor com ID %d não encontrado no dispositivo %d.\n", idSensor, idDispositivo);
        return;
    }

    // Gerar timestamp atual
    char timestamp[30];
    gerarTimestamp(timestamp, sizeof(timestamp));

    // Verificar se já existe esse timestamp no sensor (evitar duplicação)
    ListaValores* atual = sensor->valores;
    while (atual) {
        if (strcmp(atual->timestamp, timestamp) == 0) {
            printf("Valor com timestamp %s já existe. Ignorando inserção.\n", timestamp);
            return;
        }
        atual = atual->prox;
    }

    ListaValores* novo = (ListaValores*) malloc(sizeof(ListaValores));
    strcpy(novo->timestamp, timestamp);
    novo->valor = valor;
    novo->prox = sensor->valores;
    sensor->valores = novo;

    printf("Valor %.2f adicionado ao sensor %d no dispositivo %d em %s\n", valor, idSensor, idDispositivo, timestamp);
}


