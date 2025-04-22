#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "estrutura.h"

void menuPrincipal(ListaDisp* dispositivos) {

    int opcao;

    FilaEventos filaEventos;  // Declara a fila de eventos

    // Inicializa as filas de eventos (se necessário)
    inicializarFilas(&filaEventos);
    do {
        limparTela(); 
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Opcoes de dispositivo\n");
        printf("2. Opcoes de sensor/acionador\n");
        printf("3. Opcoes de evento\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                menuDispositivos(dispositivos);
                break;
            case 2:
                menuSensorAcionador(dispositivos);
                break;
            case 3:
//                menuEventos(dispositivos);
					menuEventos(dispositivos, &filaEventos);

                break;
            case 0:
                liberarMemoria(dispositivos);
                printf("Saindo...\n");
                exit(0);
                break;
            default:
                printf("Opcao invalida!\n");
        }

        printf("\nPressione Enter para continuar...");
        getchar(); 
        getchar(); 
        
    } while (opcao != 3);

}

void menuDispositivos(ListaDisp* dispositivos) {
    int opcao;
    do {
        limparTela(); 

        printf("\n===== MENU DISPOSITIVO =====\n");
        printf("1. Inserir dispositivo\n");
        printf("2. Remover dispositivo >\n");
        printf("3. Atualizar dispositivo \n");
        printf("4. Buscar dispositivos apartir dos atributos;\n");
        printf("5. Listar dispositivos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

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
            case 4:
                int valor, valorId;
                printf("Digite 1 para buscar por Id: \n");
                printf("Digite 2 para buscar por descricao: \n");
                scanf(" %d", &valor);
                if(valor == 1){
                    printf("Digite o ID: ");
                    scanf(" %d", &valorId);
                    buscarID(dispositivos, valorId);
                }

                else if (valor == 2) {
                    char descricaoBusca[50];
                    printf("Digite a descrição: ");
                    scanf(" %[^\n]", descricaoBusca); 
                    buscarPorDescricao(dispositivos, descricaoBusca);
                }

                break;
            case 5:
                listarDispositivos(dispositivos);
                break;
            case 0:
                menuPrincipal(dispositivos);
                break;
            default:
                printf("Opcao invalida!\n");
        }


        printf("\nPressione Enter para continuar..."); getchar(); getchar(); 
      
    } while (opcao != 6);
}

void menuSensorAcionador(ListaDisp* dispositivos) {
    int opcao;
    do {
      limparTela(); 

      printf("\n===== MENU SENSOR OU ACIONADOR =====\n");
      printf("1. Adicionar sensor ao dispositivo\n");
      printf("2. Listar sensores de um dispositivo\n");
      printf("3. Remover sensor de um dispositivo\n");
      printf("0. Sair\n");
      printf("Escolha uma opcao: ");
      scanf("%d", &opcao);

      switch (opcao) {
            case 1:
              // adicionaei um comentario aqui pra fazer tudo funcionar <3
//               adicionarSensor(ListaSensores, 0);
                break;
            case 2:
                removerDispositivo(&dispositivos);
                break;
            case 3:
                atualizarDispositivo(&dispositivos);
                break;
            case 0:
                menuPrincipal(dispositivos);
                break;
            default:
                printf("Opcao invalida!\n");
        }

        printf("\nPressione Enter para continuar..."); getchar(); getchar(); 
        
    } while (opcao != 6);
}


//void menuEventos(ListaDisp* dispositivos) {
//    int opcao;
//    do {
//        limparTela();
//
//        printf("\n===== MENU EVENTO =====\n");
//        printf("1. Adicionar evento\n");
//        printf("2. Listar eventos agendados\n");
//        printf("3. Executar próximo evento\n");
//        printf("0. Sair\n");
//        printf("Escolha uma opcao: ");
//        scanf("%d", &opcao);
//
//        switch (opcao) {
//            case 1:
//              	adicionarEvento(&dispositivos);
//                //adicionarDispositivo();
//            break;
//            case 2:
//              	listarEventos(&dispositivos);
//                //removerDispositivo();
//            break;
//            case 3:
//              	executarEvento(&dispositivos);
//                //atualizarDispositivo
//            break;
//            case 0:
//                menuPrincipal(dispositivos);
//            break;
//            default:
//                printf("Opcao invalida!\n");
//        }
//
//        printf("\nPressione Enter para continuar..."); getchar(); getchar();
//
//    } while (opcao != 6);
//}

void menuEventos(ListaDisp* dispositivos, FilaEventos* fila) {
    int opcao;
    do {
        limparTela();

        printf("\n===== MENU EVENTO =====\n");
        printf("1. Adicionar evento\n");
        printf("2. Listar eventos agendados\n");
        printf("3. Executar próximo evento\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int idDisp, idSensor;
                char descricao[100];
                char prioridade;

                printf("ID do dispositivo: ");
                scanf("%d", &idDisp);
                printf("ID do sensor: ");
                scanf("%d", &idSensor);
                printf("Descricao do evento: ");
                scanf(" %[^\n]", descricao);
                printf("Prioridade (A/M/B): ");
                scanf(" %c", &prioridade);

                adicionarEvento(fila, dispositivos, idDisp, idSensor, descricao, prioridade);
                break;
            }
            case 2:
                listarEventos(fila);
                break;
            case 3:
                executarEvento(fila);
                break;
            case 0:
                return; // volta ao menu anterior
            default:
                printf("Opcao invalida!\n");
        }

        printf("\nPressione Enter para continuar...");
        getchar(); getchar();

    } while (opcao != 0);
}
