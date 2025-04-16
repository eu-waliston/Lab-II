#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

int main() {
    ListaDisp* lista = NULL;
    FilaEventos fila;
    inicializarFilas(&fila);

    int opcao;
    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Adicionar dispositivo\n");
        printf("2. Listar dispositivos\n");
        printf("3. Remover dispositivo\n");
        printf("4. Adicionar sensor ao dispositivo\n");
        printf("5. Listar sensores de um dispositivo\n");
        printf("6. Remover sensor de um dispositivo\n");
        printf("7. Adicionar evento\n");
        printf("8. Listar eventos agendados\n");
        printf("9. Executar próximo evento\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();  // Limpar buffer

        int idDisp, idSensor;
        char nome[50], tipo[20], subtipo[30];
        char descricao[100], prioridade;

        switch (opcao) {
            case 1:
                printf("ID do dispositivo: ");
                scanf("%d", &idDisp);
                getchar();
                printf("Nome do dispositivo: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                lista = adicionarDispositivo(lista, idDisp, nome);
                break;

            case 2:
                listarDispositivos(lista);
                break;

            case 3:
                printf("ID do dispositivo para remover: ");
                scanf("%d", &idDisp);
                lista = removerDispositivo(lista, idDisp);
                break;

            case 4:
                printf("ID do dispositivo: ");
                scanf("%d", &idDisp);
                printf("ID do sensor: ");
                scanf("%d", &idSensor);
                getchar();
                printf("Nome do sensor: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                printf("Tipo (Sensor/Atuador): ");
                fgets(tipo, sizeof(tipo), stdin);
                tipo[strcspn(tipo, "\n")] = 0;
                printf("Subtipo (Temperatura, Movimento...): ");
                fgets(subtipo, sizeof(subtipo), stdin);
                subtipo[strcspn(subtipo, "\n")] = 0;
                adicionarSensor(lista, idDisp, idSensor, nome, tipo, subtipo);
                break;

            case 5:
                printf("ID do dispositivo: ");
                scanf("%d", &idDisp);
                listarSensores(lista, idDisp);
                break;

            case 6:
                printf("ID do dispositivo: ");
                scanf("%d", &idDisp);
                printf("ID do sensor: ");
                scanf("%d", &idSensor);
                removerSensor(lista, idDisp, idSensor);
                break;

            case 7:
                printf("ID do dispositivo: ");
                scanf("%d", &idDisp);
                printf("ID do sensor: ");
                scanf("%d", &idSensor);
                getchar();
                printf("Descricao do evento: ");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = 0;
                printf("Prioridade (A - Alta, M - Media, B - Baixa): ");
                scanf(" %c", &prioridade);
                adicionarEvento(&fila, lista, idDisp, idSensor, descricao, prioridade);
                break;

            case 8:
                listarEventos(&fila);
                break;

            case 9:
                executarEvento(&fila);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }

    } while (opcao != 0);

    liberarListaDispositivos(lista);
    return 0;
}
