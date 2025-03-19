#!/bin/bash

# Inicia o servidor C (ajuste o caminho conforme necessário)
echo "Iniciando backend..."
npm run start &

# Navega até a pasta do frontend e inicia o React
cd ./smart-home
echo "Iniciando frontend..."
npm run start
