//
// Created by we on 16/04/25.
//

#ifndef MENUS_H
#define MENUS_H

// menus.h
#ifndef MENUS_H
#define MENUS_H

#include "estrutura.h"

void limparTela();
void menuDispositivo(ListaDisp* dispositivos);
void menuSensor(Dispositivo* disp);
void menuEventos(FilaEvento *alta, FilaEvento *media, FilaEvento *baixa, ListaDisp *dispositivos);

#endif


#endif //MENUS_H
