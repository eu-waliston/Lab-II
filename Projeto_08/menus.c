#include <stdio.h>

void exibirMenu(int opcao) {
  switch (opcao) {
    case 1:
      printf("\n===== MENU DISPOSITIVO =====\n");
      printf("1. Inserir dispositivo\n");
      printf("2. Remover dispositivo >\n");
      printf("3. Atualizar dispositivo \n");
      printf("4. Buscar dispositivos apartir dos atributos;\n");
      printf("5. Listar dispositivos\n");
      printf("0. Sair\n");
      printf("Escolha uma opcao: ");
      scanf("%d", &opcao);

    case 2:
      printf("\n===== MENU SENSOR OU ACIONADOR =====\n");
      printf("1. Adicionar sensor ao dispositivo\n");
      printf("2. Listar sensores de um dispositivo\n");
      printf("3. Remover sensor de um dispositivo\n");
      printf("0. Sair\n");
      printf("Escolha uma opcao: ");
      scanf("%d", &opcao);

    case 3:
      printf("\n===== MENU EVENTO =====\n");
      printf("1. Adicionar evento\n");
      printf("2. Listar eventos agendados\n");
      printf("3. Executar próximo evento\n");
      printf("0. Sair\n");
      printf("Escolha uma opcao: ");
      scanf("%d", &opcao);

    default:
      printf("Opção inválida. Tente novamente. \n");
      break;
  }
}