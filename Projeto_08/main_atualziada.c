#include <stdio.h>
#include "estrutura.h"
#include <stdlib.h>

// Prototipando a função que está em outro arquivo
void exibirMenu(int opcao);
void limparTela();

int main() {
    ListaDisp* dispositivos = NULL;
    int opcao;

    do
    {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Opcoes de dispositivo\n");
        printf("2. Opcoes de sensor/acionador\n");
        printf("3. Opcoes de evento\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);


        if(opcao == 1) {
            exibirMenu(opcao);
            switch(opcao) {
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
                    liberarMemoria(dispositivos);
                    printf("Saindo...\n");
                    break;
                default:
                    printf("Opcao invalida!\n");
                    break;
            }
        } else if (opcao == 2) {
            exibirMenu(opcao);
        } else if (opcao == 3) {
            exibirMenu(opcao);
        }

        printf("\nPressione Enter para continuar...");
        getchar(); 
        getchar(); 

    } while (opcao != 3);
    

    return 0;
}