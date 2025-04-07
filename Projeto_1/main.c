int main() {
    // Criar dispositivos
    Dispositivo* dispositivo1 = criarDispositivo(1, "Luz da sala", LAMPADE, DESLIGADO);
    Dispositivo* dispositivo2 = criarDispositivo(2, "Câmera do quintal", CAMERA, OFFLINE);

    // Criar sensores
    Sensor* sensor1 = criarSensor(1, TEMPERATURA, 22.5);
    Sensor* sensor2 = criarSensor(2, UMIDADE, 60.0);

    // Adicionar sensores aos dispositivos
    adicionarSensor(dispositivo1, sensor1);
    adicionarSensor(dispositivo2, sensor2);

    // Listar sensores de cada dispositivo
    listarSensores(dispositivo1);
    listarSensores(dispositivo2);

    // Atualizar status de dispositivos
    atualizarStatus(dispositivo1, LIGADO);
    atualizarDescricao(dispositivo2, "Câmera de segurança");

    // Listar dispositivos
    Dispositivo* dispositivos[] = {dispositivo1, dispositivo2};
    listarDispositivos(dispositivos, 2);

    // Remover um sensor
    removerSensor(dispositivo2, 2);

    // Listar novamente os sensores
    listarSensores(dispositivo2);

    // Liberar memória
    liberarDispositivo(dispositivo1);
    liberarDispositivo(dispositivo2);

    return 0;
}

