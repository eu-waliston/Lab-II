#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void enviarRespostaJSON(const char* json) {
    // Imprime somente o JSON, sem cabeçalhos HTTP
    printf("%s\n", json);
}

int main() {
    char *requestMethod = getenv("REQUEST_METHOD");

    // Se não estiver definido, assume GET
    if (requestMethod == NULL || strcmp(requestMethod, "GET") == 0) {
        // Retorne alguns dispositivos de exemplo em formato JSON
        enviarRespostaJSON("{\"dispositivos\": ["
                           "{\"id\": 1, \"descricao\": \"Luz da Sala\", \"tipo\": \"Lâmpada\", \"status\": \"Ligado\", \"sensores\": [\"Luminosidade\", \"Movimento\"]},"
                           "{\"id\": 2, \"descricao\": \"Câmera da Entrada\", \"tipo\": \"Câmera\", \"status\": \"Online\", \"sensores\": [\"Movimento\", \"Som\"]}"
                           "]}");
    } else if (strcmp(requestMethod, "POST") == 0) {
        // Aqui você pode tratar a inserção de dispositivos via POST
        // Por enquanto, apenas responde que o POST foi recebido.
        enviarRespostaJSON("{\"mensagem\": \"Dispositivo adicionado com sucesso!\"}");
    } else {
        enviarRespostaJSON("{\"mensagem\": \"Método não suportado.\"}");
    }

    return 0;
}
