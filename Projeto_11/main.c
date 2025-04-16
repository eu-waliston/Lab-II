// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"
#include "menus.h"

void liberar_memoria(ListaDisp *dispositivos, FilaEvento *alta, FilaEvento *media, FilaEvento *baixa) {
    while (dispositivos) {
        Dispositivo *tempDisp = dispositivos;
        dispositivos = dispositivos->prox;

        Sensor *sensor = tempDisp->sensores;
        while (sensor) {
            Sensor *tempSensor = sensor;
            sensor = sensor->prox;
            free(tempSensor);
        }
        free(tempDisp);
    }

    FilaEvento *filas[3] = { alta, media, baixa };
    for (int i = 0; i < 3; i++) {
        Evento *evento = filas[i]->inicio;
        while (evento) {
            Evento *tempEv = evento;
            evento = evento->prox;
            free(tempEv);
        }
    }
}

int main() {
    ListaDisp *dispositivos = NULL;
    FilaEvento filaAlta, filaMedia, filaBaixa;
    inicializar_filas(&filaAlta, &filaMedia, &filaBaixa);

    int opcao;

    do {
        limparTela();
        printf("===== SISTEMA DE CASA INTELIGENTE =====\n");
        printf("1. Menu Dispositivos\n");
        printf("2. Menu Sensores (requer ID do dispositivo)\n");
        printf("3. Menu Eventos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuDispositivo(&dispositivos);
                break;
            case 2: {
                int idBusca;
                printf("Digite o ID do dispositivo: ");
                scanf("%d", &idBusca);
                Dispositivo *disp = buscar_dispositivo(dispositivos, idBusca);
                if (disp) {
                    menuSensor(disp);
                } else {
                    printf("Dispositivo nao encontrado!\n");
                    printf("Pressione Enter para continuar...");
                    getchar(); getchar();
                }
                break;
            }
            case 3:
                menuEventos(&filaAlta, &filaMedia, &filaBaixa, &dispositivos);
                break;
        }
    } while(opcao != 0);

    liberar_memoria(dispositivos, &filaAlta, &filaMedia, &filaBaixa);
    return 0;
}
