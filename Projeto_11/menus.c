#include <stdio.h>
#include <stdlib.h>
#include "estrutura.h"

#include "menus.h"

// Limpa a tela dependendo do sistema operacional
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void menuDispositivo(ListaDisp* dispositivos) {
    int opcao, id;
    char nome[MAX_NOME];

    do {
        limparTela();
        printf("\n===== MENU DISPOSITIVO =====\n");
        printf("1. Adicionar dispositivo\n");
        printf("2. Listar dispositivos\n");
        printf("3. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                printf("ID do dispositivo: ");
                scanf("%d", &id);
                getchar();
                printf("Nome do dispositivo: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;
                adicionar_dispositivo(dispositivos, criar_dispositivo(id, nome));
                break;
            case 2:
                listar_dispositivos(dispositivos);
                break;
        }
    } while(opcao != 3);
}

void menuSensor(Dispositivo* disp) {
    int opcao, id;
    int tipo, subtipo;

    do {
        limparTela();
        printf("\n===== MENU SENSOR/ACIONADOR =====\n");
        printf("1. Adicionar sensor/acionador\n");
        printf("2. Remover sensor/acionador\n");
        printf("3. Listar sensores/acionadores\n");
        printf("4. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("ID do sensor: ");
                scanf("%d", &id);
                printf("Tipo (0 - SENSOR, 1 - ATUADOR): ");
                scanf("%d", &tipo);
                printf("Subtipo (ex: 0 - temperatura, 1 - umidade, etc.): ");
                scanf("%d", &subtipo);
                adicionar_sensor(disp, criar_sensor(id, tipo, subtipo));
                break;
            case 2:
                printf("ID do sensor a remover: ");
                scanf("%d", &id);
                remover_sensor(disp, id);
                break;
            case 3:
                listar_sensores(disp);
                break;
        }
        printf("\nPressione Enter para continuar...");
        getchar(); getchar();
    } while(opcao != 4);
}

void menuEventos(FilaEvento *alta, FilaEvento *media, FilaEvento *baixa, ListaDisp *dispositivos) {
    int opcao;
    do {
        limparTela();
        printf("\n===== MENU EVENTOS =====\n");
        printf("1. Executar proximo evento\n");
        printf("2. Listar eventos\n");
        printf("3. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                executar_evento(alta, media, baixa);
                break;
            case 2:
                printf("--- Alta Prioridade ---\n");
                listar_eventos(alta);
                printf("--- Media Prioridade ---\n");
                listar_eventos(media);
                printf("--- Baixa Prioridade ---\n");
                listar_eventos(baixa);
                break;
        }
        printf("\nPressione Enter para continuar...");
        getchar(); getchar();
    } while(opcao != 3);
}
