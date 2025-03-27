#include <stdio.h>
#include "estrutura.h"
#include <stdlib.h> 

int main() {

    void limparTela() {
        #ifdef _WIN32
            system("cls"); 
        #else
            system("clear"); 
        #endif
    }



    ListaDisp* dispositivos = NULL;
    int opcao;

    do {

        limparTela(); 

        printf("\n1. Inserir dispositivo\n");
        printf("2. Remover dispositivo \n");
        printf("3. Atualizar dispositivo \n");
        printf("4. Buscar dispositivos apartir dos atributos;\n");
        printf("5. Listar dispositivos\n");
        printf("6. Sair\n");
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
            case 6:
                liberarMemoria(dispositivos);
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }


        printf("\nPressione Enter para continuar...");
        getchar(); 
        getchar(); 
        
    } while (opcao != 6);

    return 0;
}
