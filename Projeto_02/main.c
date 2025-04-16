#include <stdio.h>
#include "estrutura.h"

int main() {
    ListaDisp* dispositivos = NULL;
    int opcao;
    
    do {
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
                char atributo[50], valor[50];
                printf("Digite o atributo (descricao, tipo, status): ");
                scanf(" %[^\n]", atributo);
                printf("Digite o valor do atributo: ");
                scanf(" %[^\n]", valor);
                buscarDispositivos(dispositivos, atributo, valor);
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
    } while (opcao != 6);
    
    return 0;
}
