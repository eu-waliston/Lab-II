//O arquivo utils.c reúne funções auxiliares que oferecem suporte ao funcionamento geral do sistema.
// Ele contém implementações reutilizáveis, como validações, manipulação de strings, operações matemáticas básicas
// e outras rotinas utilitárias que não pertencem diretamente à lógica principal, mas são essenciais para o bom
// desempenho e organização do código.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "estrutura.h"

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

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