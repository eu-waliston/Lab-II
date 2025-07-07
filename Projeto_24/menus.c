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
        printf("4 Exportar valores (CSV)\n"); 
        printf("5 Arvore binaria\n"); 
          
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
                exportarValoresCSV(dispositivos, "dados.csv");
                break;
            case 5:
                menuArvore(dispositivos, fila);
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
        printf("1 Adicionar sensor/atuador ao dispositivo\n");
        printf("2 Listar sensores/Atuadores de um dispositivo\n");
        printf("3 Remover sensor/atuador de um dispositivo\n");
        printf("4 Incluir valor em sensor\n");
        printf("5 Listar valores de um sensor\n");
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
                listarSensores(dispositivos, 1);
                break;
            case 3:
                removerSensor(dispositivos);
                break;
            case 4:
                incluirValoresSensor(dispositivos);
                break;
            case 5:
                listarValoresSensor(dispositivos);
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

void menuArvore(ListaDisp* dispositivos, FilaEventos* fila) {
    int opcao;
    Arvore* raiz = NULL;
    
    do {
        limparTela();
        printf("\n===== MENU ARVORE BINARIA =====\n");
        printf("1 Criar arvore balanceada\n");
        printf("2 Buscar valor por timestamp\n");
        printf("3 Mostrar estrutura da arvore\n");
        printf("0 Voltar e Apagar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (raiz == NULL && (opcao == 2 || opcao == 3)) {
            printf("A arvore ainda nao foi criada\n\n\nPressione Enter para continuar");
            getchar();  getchar(); 
            opcao  = 1;
        }

        switch (opcao) {
            case 1:
                raiz = criarArvoreBalanceada(dispositivos);
                printf("Arvore criada com sucesso.\n");
                break;
            case 2:
                buscarTimestampMenu(raiz);
                break;
            case 3:
                printf("Estrutura da arvore (em ordem):\n");
                mostrarArvore(raiz);
                break;
            case 0:
                apagarArvore(raiz);
                printf("Arvore apagada com sucesso!!!\n");
                menuPrincipal(dispositivos, fila);
                break;
            default:
                printf("Opcao invalida\n");
        }

        printf("\nPressione Enter para continuar");
        getchar(); 
        getchar(); 
    } while (opcao != 0);
    
}