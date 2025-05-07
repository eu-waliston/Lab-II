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

void menuPrincipal(ListaDisp* dispositivos, FilaEventos* fila) {
    int opcao;
    do {
        limparTela(); 
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 Opcoes de dispositivo\n");
        printf("2 Opcoes de sensor acionador\n");
        printf("3 Opcoes de evento\n");
        printf("4 Importar os dispositivos\n");
        printf("5 Emportar os dispositivos\n");
        printf("0 Sair\n");
        printf("Escolha uma opcao ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                menuDispositivos(dispositivos, fila);
                break;
            case 2:
                menuSensorAcionador(dispositivos, fila);
                break;
            case 3:
                menuEventos(dispositivos, fila);
                break;
            case 4:
                //menuEventos(dispositivos, fila);
                break;
            case 5:
                //menuEventos(dispositivos, fila);
                break;
            case 0:
                liberarMemoria(dispositivos);
                printf("Saindo\n");
                exit(0);
                break;
            default:
                printf("Opcao invalida\n");
        }

        printf("\nPressione Enter para continuar");
        getchar(); 
        getchar(); 
    } while (opcao != 0);
}

void menuDispositivos(ListaDisp* dispositivos, FilaEventos* fila) {
    int opcao;
    do {
        limparTela(); 

        printf("\n===== MENU DISPOSITIVO =====\n");
        printf("1 Inserir dispositivo\n");
        printf("2 Remover dispositivo\n");
        printf("3 Atualizar dispositivo\n");
        printf("4 Buscar dispositivos a partir dos atributos\n");
        printf("5 Listar dispositivos\n");
        printf("0 Voltar\n");
        printf("Escolha uma opcao ");
        scanf("%d", &opcao);

        if (dispositivos == NULL && opcao  != 1) {
            printf("Nenhum dispositivo cadastrado.\n");
            opcao  = 1;
        }

        switch (opcao) {
            case 1:
                adicionarDispositivo(&dispositivos);
                break;
            case 2:
                removerDispositivo(&dispositivos);
                break;
            case 3:
                atualizarDispositivo(&dispositivos);
                break;
            case 4: {
                int valor, valorId;
                printf("Digite 1 para buscar por Id\n");
                printf("Digite 2 para buscar por descricao\n");
                scanf("%d", &valor);
                if(valor == 1) {
                    printf("Digite o ID ");
                    scanf("%d", &valorId);
                    buscarID(dispositivos, valorId);
                } else if (valor == 2) {
                    char descricaoBusca[50];
                    printf("Digite a descricao ");
                    scanf(" %[^\n]", descricaoBusca); 
                    buscarPorDescricao(dispositivos, descricaoBusca);
                }
                break;
            }
            case 5:
                listarDispositivos(dispositivos);
                break;
            case 0:
                menuPrincipal(dispositivos, fila);
                return; 
            default:
                printf("Opcao invalida\n");
        }

        printf("\nPressione Enter para continuar");
        getchar(); 
        getchar(); 
    } while (opcao != 0);
}

void menuSensorAcionador(ListaDisp* dispositivos, FilaEventos* fila) {
    int opcao;
    do {
        limparTela(); 

        printf("\n===== MENU SENSOR OU ACIONADOR =====\n");
        printf("1 Adicionar sensor ao dispositivo\n");
        printf("2 Listar sensores de um dispositivo\n");
        printf("3 Remover sensor de um dispositivo\n");
        printf("0 Voltar\n");
        printf("Escolha uma opcao ");
        scanf("%d", &opcao);

        if (dispositivos == NULL) {
            printf("Nenhum dispositivo cadastrado.\n");
            opcao  = 1;
        }

        switch (opcao) {
            case 1:
                if (verficarSeHaDisp(&dispositivos) == 0) {
                    adicionarDispositivo(&dispositivos);
                } else {
                    adicionarSensorNoDisp(&dispositivos);
                }
                break;
            case 2:
                listarSensores(dispositivos);
                break;
            case 3:
                removerSensor(dispositivos);
                break;
            case 0:
                menuPrincipal(dispositivos, fila);
                return; 
            default:
                printf("Opcao invalida\n");
        }

        printf("\nPressione Enter para continuar");
        getchar(); 
        getchar(); 
    } while (opcao != 0);
}

void menuEventos(ListaDisp* dispositivos, FilaEventos* fila) {
    int opcao;
    do {
        limparTela(); 

        printf("\n===== MENU EVENTO =====\n");
        printf("1 Adicionar evento\n");
        printf("2 Listar eventos agendados\n");
        printf("3 Executar proximo evento\n");
        printf("0 Voltar\n");
        printf("Escolha uma opcao ");
        scanf("%d", &opcao);

        if (dispositivos == NULL) {
            printf("Nenhum dispositivo cadastrado.\n\n\nPressione Enter para continuar");
            getchar();  getchar(); 
            opcao  = 0;
        }

        switch (opcao) {
            case 1:
                adicionarEvento(fila, dispositivos);
                break;
            case 2:
                listarEventos(fila);
                break;
            case 3:
                executarEvento(fila);
                break;
            case 0:
                menuPrincipal(dispositivos, fila);
                return; 
            default:
                printf("Opcao invalida\n");
        }

        printf("\nPressione Enter para continuar");
        getchar(); 
        getchar(); 
    } while (opcao != 0);
}
