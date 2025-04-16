#include <stdio.h>
#include "estrutura.h"
#include <stdlib.h> // Necessário para usar system("cls")

int main() {

    void limparTela() {
        #ifdef _WIN32
            system("cls"); // Comando para Windows
        #else
            system("clear"); // Comando para Linux/macOS
        #endif
    }



    ListaDisp* dispositivos = NULL;
    int opcao;

    do {

        limparTela(); // Limpa a tela antes de mostrar o menu

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
                    scanf(" %[^\n]", descricaoBusca); // Lendo a string corretamente
                    buscarPorDescricao(dispositivos, descricaoBusca);
                }

                    // TODO => listar de for crescente

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
        getchar(); // Captura o enter extra do scanf
        getchar(); // Aguarda o usuário pressionar enter

    } while (opcao != 6);

    return 0;
}

void adicionarEvento(FilaPrioridade* fila, int prioridade, Evento* evento) {
    Evento** lista;

    // Seleciona a fila com base na prioridade
    if (prioridade == 1) lista = &(fila->alta);
    else if (prioridade == 2) lista = &(fila->media);
    else lista = &(fila->baixa);

    // Insere o evento no início da lista (FIFO)
    evento->prox = *lista;
    *lista = evento;
}

























































